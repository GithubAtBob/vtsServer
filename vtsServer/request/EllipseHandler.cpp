
#include "StdAfx.h"
#include "EllipseHandler.h"

#include "message/Ellipse.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBEllipseHandler.h"
#include "timer/hgEllipseTimerHandler.h"


#include "Managers/hgSendManager.h"
EllipseHandler::EllipseHandler()
{

}

EllipseHandler::~EllipseHandler(void)
{
}

vtsRequestHandler::WorkMode EllipseHandler::workMode()
{
	return Work_Delete_Manual;
}

void EllipseHandler::handle(boost::asio::const_buffer& data)
{
    EllipseRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    if (msg.type() == DBEllipseHandlerType::Waring)
    {
        hgEllipseTimerHandler* l_timer = new hgEllipseTimerHandler(msg.id());
        l_timer->setDuration(1.0);
        this->setTimer(l_timer);
        //         delete this;
        return ;
    }

    DBEllipseHandler *dbHandler = new DBEllipseHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Lat = msg.lat();
    dbHandler->Lon = msg.lon();
    dbHandler->ShortAxis = msg.shortaxis();
    dbHandler->LongAxis = msg.longaxis();
    dbHandler->LineStyle = msg.linestyle();
    dbHandler->FullStyle = msg.fullstyle();
    dbHandler->LineWidth = msg.linewidth();
    dbHandler->WaringID = msg.waringid();
    dbHandler->WaringType = msg.waringtype().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    dbHandler->LineColor = msg.linecolor().c_str();
    dbHandler->FullColor = msg.fullcolor().c_str();
    postToDB(dbHandler, boost::bind(&EllipseHandler::afterDb, this, dbHandler));
    
}

void EllipseHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void EllipseHandler::afterDb(DBEllipseHandler* db)
{
    EllipseRepsone result;
    result = db->Respon;
    result.set_type(db->Type);
    response(result, boost::bind(&EllipseHandler::afterResponse, this, boost::asio::placeholders::error));
    //添加成功发广播
    if (db->Type == DBEllipseHandlerType::Add && db->Result == "OK")
    {
        AddUserLay l_userlay;
        l_userlay.set_id(db->ID.toStdString());
        l_userlay.set_pic("Ellipse");
        l_userlay.set_drawman(db->DrawMan.toStdString());
        hgSendManager::SendClientMessageUOwn("adduserlay",l_userlay,this->connection());
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 if (p != this->connection())//自己不要发送
//                 {
//                     p->write("adduserlay",l_userlay);
//                 }
//         });
    }
    delete db;
}

void EllipseHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
