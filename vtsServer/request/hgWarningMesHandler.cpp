
#include "StdAfx.h"
#include "hgWarningMesHandler.h"

#include "message/hgWarningMes.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgWarningSetManager.h"
#include "Managers/hgAlarmManager.h"
#include "db/DBWarnHistoryHandler.h"

#include "Managers/hgSendManager.h"
extern const char* hgWaringTypeGuid[];

hgWarningMesHandler::hgWarningMesHandler()
{

}

hgWarningMesHandler::~hgWarningMesHandler(void)
{
}

vtsRequestHandler::WorkMode hgWarningMesHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgWarningMesHandler::handle(boost::asio::const_buffer& data)
{
    hgWarningMes msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    if (msg.warningid() != hgWaringTypeGuid[HISTORY])
    {

        hgSendManager::SendClientMessageUOwn("hgWarningMes",msg,this->connection());
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 if (p != this->connection())//自己不要发送
//                 {
//                     p->write("hgWarningMes",msg);
//                 }
//         });
        QSqlDatabase database = this->connection()->server().openDBConnection();
        hgSqlOperator l_sqlOperator(database);
        {
            hgAlarmManager::SaveWarnData(l_sqlOperator,msg);
        }
        this->connection()->server().closeDBConnection(database);
        delete this;
        return ;
    }
    else
    {
        DBWarnHistoryHandler *dbHandler = new DBWarnHistoryHandler();
        dbHandler->m_MMSI = QString::fromStdString(msg.mmsi());


        postToDB(dbHandler, boost::bind(&hgWarningMesHandler::afterDb, this, dbHandler));
    }
}

void hgWarningMesHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgWarningMesHandler::afterDb(DBWarnHistoryHandler* db)
{
    for (int i = 0; i < db->m_WarnVec.size(); i++)
    {
        hgSendManager::SendClientMessage("hgWarningMes",db->m_WarnVec[i],this->connection());
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 //if (p != this->connection())//自己不要发送
//                 {
//                     p->write("hgWarningMes",db->m_WarnVec[i]);
//                 }
//         });
    }

    delete db;
    delete this;

}

void hgWarningMesHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}