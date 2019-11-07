
#include "StdAfx.h"
#include "hgDomainHandler.h"

#include "message/hgDomain.pb.h"
#include "db/DBDomainHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgDomainTimerHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgDomainHandler::hgDomainHandler()
{

}

hgDomainHandler::~hgDomainHandler(void)
{
}

vtsRequestHandler::WorkMode hgDomainHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgDomainHandler::handle(boost::asio::const_buffer& data)
{
    hgDomain msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("Domain",WarningDomainWatch,this);


    DBDomainHandler *dbHandler = new DBDomainHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->DomainWatch = msg.domainwatch();
    dbHandler->DomainRadius = msg.domainradius();
    dbHandler->DomainColorR = msg.domaincolorr();
    dbHandler->DomainColorG = msg.domaincolorg();
    dbHandler->DomainColorB = msg.domaincolorb();
    dbHandler->DomainShow = msg.domainshow();


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,OtherType);

    postToDB(dbHandler, boost::bind(&hgDomainHandler::afterDb, this, dbHandler));
    
}


void hgDomainHandler::afterDb(DBDomainHandler* db)
{
    Domain l_Domain;
    l_Domain.TargetID = db->MMSI;
    l_Domain.DomainWatch = db->DomainWatch;
    l_Domain.DomainRadius = db->DomainRadius;
    l_Domain.DomainColorR = db->DomainColorR;
    l_Domain.DomainColorG = db->DomainColorG;
    l_Domain.DomainColorB = db->DomainColorB;
    l_Domain.DomainShow = db->DomainShow;
    hgAlarmManager::m_WarningSetManager.SaveDomain(l_Domain);

    hgDomain result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_domainwatch(db->DomainWatch);
    result.set_domainradius(db->DomainRadius);
    result.set_domaincolorr(db->DomainColorR);
    result.set_domaincolorg(db->DomainColorG);
    result.set_domaincolorb(db->DomainColorB);
    result.set_domainshow(db->DomainShow);
    //hgSendManager::SendClientMessageUOwn("Domain",result,this->connection());
    hgSendManager::SendExceptShipMessage("Domain",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("Domain",result);
//             }
//     });

    delete db;
    delete this;
}
