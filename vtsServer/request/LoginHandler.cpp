
#include "StdAfx.h"
#include "LoginHandler.h"

#include "message/login.pb.h"
#include "db/DBLoginHandler.h"
#include "Managers/hgDataManager.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"

LoginHandler::LoginHandler()
{

}

LoginHandler::~LoginHandler(void)
{
}

vtsRequestHandler::WorkMode LoginHandler::workMode()
{
    return Work_Delete_Manual;
}

void LoginHandler::handle(boost::asio::const_buffer& data)
{
    t1 = clock();
    LoginRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBLoginHandler *dbHandler = new DBLoginHandler();
    dbHandler->UserName = msg.username().c_str();
    dbHandler->Password = msg.password().c_str();
	//  [7/12/2017 ChengHaoNan]
    /*int l_Veclen = hgDataManager::m_restServer.size();
    int l_sure = false;
    vector<string>::iterator l_it = find(hgDataManager::m_restServer.begin(),
    hgDataManager::m_restServer.end(),"c_" + dbHandler->UserName.toStdString());
    if (l_it != hgDataManager::m_restServer.end())
    {
    l_sure = true;
    }*/
    //判断如果原来的连接已存在，则登录失败
    bool l_sure = false;
    std::string name = "c_"+ msg.username();
    this->connection()->server().connectionManager().for_each
        ([&](ConnectionPtr p){
            if (p->channel() == name)//
            {
                l_sure = true;
            }
    });

    if (l_sure)
    {
        LoginRepsone result;
        result.set_result("The user has logged in");
        //vtsInfo << clock();
        response(result, boost::bind(&LoginHandler::afterResponse, this, boost::asio::placeholders::error));
    }
    else
    {
        //vtsInfo << clock();
        postToDB(dbHandler, boost::bind(&LoginHandler::afterDb, this, dbHandler));
    }
	//  [7/12/2017 ChengHaoNan]
	

    /*
    callLater(1.0, boost::bind(&LoginHandler::timeout, this, time(NULL)));

    LoginRepsone result;
    result.set_result("hello world!");
    responseAsync(result, boost::bind(&LoginHandler::afterResponse, this, boost::asio::placeholders::error));
    */
    /*
    boost::system::error_code ec;
    response(result, ec);
    if (ec)
    {
        std::cout << "error: " << ec.message();
    }
    */
}

void LoginHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void LoginHandler::afterDb(DBLoginHandler* db)
{
    LoginRepsone result;
    result.set_result(db->Result.toStdString());
    result.set_loginrole(db->LoginRole.toStdString());
    result.set_allgroup(db->GroupRecord.toStdString());
    result.set_alluser(db->UserRecord.toStdString());
    result.set_allnotes(/*db->NotesRecord.toStdString()*/"1");
    result.set_allfixedobject(/*db->FixedObjRecord.toStdString()*/"1");
    result.set_allaidsail(/*db->AidSailRecord.toStdString()*/"1");
    result.set_grouptype(db->GroupType);
//     if (db->Result == "OK")
//     {
//         DBGroupHandler* l_dbhandler = new DBGroupHandler();
//         l_dbhandler->Type = DBGroupHandlerType::AllGroup;
//         postToDB(l_dbhandler, boost::bind(&GroupHandler::afterDb, this, l_dbhandler));
    //     }
    //vtsInfo << clock();
    response(result, boost::bind(&LoginHandler::afterResponse, this, boost::asio::placeholders::error));
    
    delete db;
}

void LoginHandler::afterResponse(const boost::system::error_code& e)
{
    t2 = clock();
    vtsInfo << "Send Login Result, HandlerTime : " << t2-t1;
    delete this;
}
