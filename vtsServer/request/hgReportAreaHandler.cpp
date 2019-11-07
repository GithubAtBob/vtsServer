
#include "StdAfx.h"
#include "hgReportAreaHandler.h"

#include "message/hgReportArea.pb.h"
#include "db/DBReportAreaHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgReportAreaTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

hgReportAreaHandler::hgReportAreaHandler()
{

}

hgReportAreaHandler::~hgReportAreaHandler(void)
{
}

vtsRequestHandler::WorkMode hgReportAreaHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgReportAreaHandler::handle(boost::asio::const_buffer& data)
{
    hgReportArea msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("ReportArea",WarningReportArea,this);


    DBReportAreaHandler *dbHandler = new DBReportAreaHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_ReportArea = msg.reportarea();
    dbHandler->b_Pattern = msg.pattern();

    google::protobuf::RepeatedPtrField<hgAreaData> l_AreaData = msg.areadata();
    for (int i = 0; i < l_AreaData.size(); i++)
    {
        AreaData areaData;
        areaData.ID = l_AreaData.Get(i).id().c_str();
        areaData.type = l_AreaData.Get(i).type();
        dbHandler->mapAreaData.insert(areaData.ID,areaData);
    }

    dbHandler->EarilestTime = msg.earlisttime();
    dbHandler->LatestTime = msg.latesttime();



    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsReportArea);
    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsReportTime);

    postToDB(dbHandler, boost::bind(&hgReportAreaHandler::afterDb, this, dbHandler));
    
}

void hgReportAreaHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgReportAreaHandler::afterDb(DBReportAreaHandler* db)
{
    ReportArea l_ReportArea;
    l_ReportArea.TargetID = db->MMSI;
    l_ReportArea.b_ReportArea = db->b_ReportArea;
    l_ReportArea.b_Pattern = db->b_Pattern;
    l_ReportArea.mapAreaData = db->mapAreaData;
    l_ReportArea.EarilestTime = db->EarilestTime;
    l_ReportArea.LatestTime = db->LatestTime;
    hgAlarmManager::m_WarningSetManager.SaveReportArea(l_ReportArea); 

    hgReportArea result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_reportarea(db->b_ReportArea);
    result.set_pattern(db->b_Pattern);

    QMap<QString,AreaData>::iterator it = l_ReportArea.mapAreaData.begin();
    for (it; it != l_ReportArea.mapAreaData.end(); ++it)
    {
        hgAreaData* l_AreaData = result.add_areadata();
        l_AreaData->set_id(it->ID.toStdString());
        l_AreaData->set_type(it->type);
    }

    result.set_earlisttime(db->EarilestTime);
    result.set_latesttime(db->LatestTime);
    hgSendManager::SendClientMessageUOwn("ReportArea",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("ReportArea",result);
//             }
//     });
        

    delete db;
    delete this;
}


