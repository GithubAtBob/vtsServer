
#include "StdAfx.h"
#include "DBChannelHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBChannelHandler::DBChannelHandler(void)
{
}


DBChannelHandler::~DBChannelHandler(void)
{
}

void DBChannelHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case DBChannelHandlerType::Add:
        Addhandle(s, sqlOperator);
        break;
    case DBChannelHandlerType::Update:
        Updatehandle(s, sqlOperator);
        break;
    case DBChannelHandlerType::Remove:
        Removehandle(s, sqlOperator);
        break;
    default:
        break;
    }
}

void DBChannelHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("channel_table");
    QMap<QString, QVariant> l_data;
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << Channel;
    l_data.insert("point",QVariant(mes));
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("annotation",Annotation);
    l_data.insert("channeltype",ChannelType);
    l_data.insert("width",Width);
    //l_data.insert("point",Point);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("linecolor",LineColor);
    l_data.insert("waringID",WaringID);
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(channel_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

void DBChannelHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("channel_table");
    QMap<QString, QVariant> l_data;
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << Channel;
    l_data.insert("point",QVariant(mes));
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("annotation",Annotation);
    l_data.insert("channeltype",ChannelType);
    l_data.insert("width",Width);
    //l_data.insert("point",Point);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("linecolor",LineColor);
    l_data.insert("waringID",WaringID);
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    if (Info.size() > 0)
    {
        ChannelWarInfo l_info = Info.Get(0);
        l_data.insert("depth",l_info.depth());
        l_data.insert("minborder",l_info.minborder());
        l_data.insert("maxborder",l_info.maxborder());
        l_data.insert("minangle",l_info.minangle());
        l_data.insert("maxangle",l_info.maxangle());
        l_data.insert("maxlong",l_info.maxlong());
        l_data.insert("entertype",l_info.entertype().c_str());
        l_data.insert("fcourse",l_info.fcourse().c_str());
        l_data.insert("fangle",l_info.fangle());
        l_data.insert("fminspeed",l_info.fminspeed());
        l_data.insert("fmaxspeed",l_info.fmaxspeed());
        l_data.insert("fminspeedtime",l_info.fminspeedtime());
        l_data.insert("fmaxspeedtime",l_info.fmaxspeedtime());
        l_data.insert("fendist",l_info.fendist());
        l_data.insert("fdisendist",l_info.fdisendist());
        l_data.insert("fsailendist",l_info.fsailendist());
        l_data.insert("bcourse",l_info.bcourse().c_str());
        l_data.insert("bangle",l_info.bangle());
        l_data.insert("bminspeed",l_info.bminspeed());
        l_data.insert("bmaxspeed",l_info.bmaxspeed());
        l_data.insert("bminspeedtime",l_info.bminspeedtime());
        l_data.insert("bmaxspeedtime",l_info.bmaxspeedtime());
        l_data.insert("bendist",l_info.bendist());
        l_data.insert("bdisendist",l_info.bdisendist());
        l_data.insert("bsailendist",l_info.bsailendist());
    }
//    l_data.insert("isshare",IsShare);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(channel_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void DBChannelHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("channel_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(channel_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}

// void DBChannelHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
// {
//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
//     l_pSqlSelectCmd->SetTableName("channel_table");
// 
//     //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1'"/* or isshare = '1'"*/).arg(Name));
//     if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
//     {
//         std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
//         if (l_pSqlSelectCmd)
//         {
//             delete l_pSqlSelectCmd;
//             l_pSqlSelectCmd = NULL;
//         }
//         return;
//     }
//     Respon.set_type(Type); 
//     QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
//     Respon.clear_channels();
//     for (int i = 0; i < l_pSqlRecord->count(); i++)
//     {
//         QSqlRecord l_record = l_pSqlRecord->at(i);
//         ChannelRequest* l_requst = Respon.add_channels();
//         std::string l_ID = l_record.value("ID").toString().toStdString();
//         std::string l_name = l_record.value("name").toString().toStdString();
//         std::string l_annotation = l_record.value("annotation").toString().toStdString();
//         int l_channeltype = l_record.value("channeltype").toInt();
//         double l_width = l_record.value("width").toDouble();
//         QByteArray l_points = l_record.value("point").toByteArray();
//         int l_linestyle = l_record.value("linestyle").toInt();
//         std::string l_linecolor = l_record.value("linecolor").toString().toStdString();
//         std::string l_waringID = l_record.value("waringID").toString().toStdString();
//         std::string l_waringtype = l_record.value("waringtype").toString().toStdString();
//         std::string l_drawman = l_record.value("drawman").toString().toStdString();
//         bool l_isshare = l_record.value("isshare").toBool();
//         double depth = l_record.value("depth").toDouble();
//         double minborder = l_record.value("minborder").toDouble();
//         double maxborder = l_record.value("maxborder").toDouble();
//         double minangle = l_record.value("minangle").toDouble();
//         double maxangle = l_record.value("maxangle").toDouble();
//         double maxlong = l_record.value("maxlong").toDouble();
//         QString entertype = l_record.value("entertype").toString();
//         QString fcourse = l_record.value("fcourse").toString();
//         double fangle = l_record.value("fangle").toDouble();
//         double fminspeed = l_record.value("fminspeed").toDouble();
//         double fmaxspeed = l_record.value("fmaxspeed").toDouble();
//         double fminspeedtime = l_record.value("fminspeedtime").toDouble();
//         double fmaxspeedtime = l_record.value("fmaxspeedtime").toDouble();
//         double fendist = l_record.value("fendist").toDouble();
//         double fdisendist = l_record.value("fdisendist").toDouble();
//         double fsailendist = l_record.value("fsailendist").toDouble();
//         QString bcourse = l_record.value("bcourse").toString();
//         double bangle = l_record.value("bangle").toDouble();
//         double bminspeed = l_record.value("bminspeed").toDouble();
//         double bmaxspeed = l_record.value("bmaxspeed").toDouble();
//         double bminspeedtime = l_record.value("bminspeedtime").toDouble();
//         double bmaxspeedtime = l_record.value("bmaxspeedtime").toDouble();
//         double bendist = l_record.value("bendist").toDouble();
//         double bdisendist = l_record.value("bdisendist").toDouble();
//         double bsailendist = l_record.value("bsailendist").toDouble();
//         l_requst->set_type(Type);
//         l_requst->set_id(l_ID);
//         l_requst->set_name(l_name);
//         l_requst->set_annotation(l_annotation);
//         l_requst->set_channeltype(l_channeltype);
//         l_requst->set_width(l_width);
//         google::protobuf::RepeatedPtrField<ChannelWay> l_Point;
//         QDataStream in(&l_points,QIODevice::ReadOnly);
//         in.setVersion(QDataStream::Qt_5_2);
//         in >> l_Point;
//         for (int i = 0; i < l_Point.size(); i++)
//         {
//             ChannelWay* l_addChannel = l_requst->add_channel();
//             ChannelWay l_Channel = l_Point.Get(i);
//             auto l_ChannelPoints = l_Channel.point();
//             for ( int j = 0; j < l_ChannelPoints.size(); j++ )
//             {
//                 PointMes* l_Mes = l_addChannel->add_point();
//                 l_Mes->set_lat(l_ChannelPoints.Get(j).lat());
//                 l_Mes->set_lon(l_ChannelPoints.Get(j).lon());
//             }
//         }
//         l_requst->set_linestyle(l_linestyle);
//         l_requst->set_linecolor(l_linecolor);
//         l_requst->set_waringid(l_waringID);
//         l_requst->set_waringtype(l_waringtype);
//         l_requst->set_drawman(l_drawman);
//         l_requst->set_isshare(l_isshare);
//         
//         ChannelWarInfo* l_info = l_requst->add_info();
//         l_info->set_depth(depth);
//         l_info->set_minborder(minborder);
//         l_info->set_maxborder(maxborder);
//         l_info->set_minangle(minangle);
//         l_info->set_maxangle(maxangle);
//         l_info->set_maxlong(maxlong);
//         l_info->set_entertype(entertype.toStdString());
//         l_info->set_fcourse(fcourse.toStdString());
//         l_info->set_fangle(fangle);
//         l_info->set_fminspeed(fminspeed);
//         l_info->set_fmaxspeed(fmaxspeed);
//         l_info->set_fminspeedtime(fminspeedtime);
//         l_info->set_fmaxspeedtime(fmaxspeedtime);
//         l_info->set_fendist(fendist);
//         l_info->set_fdisendist(fdisendist);
//         l_info->set_fsailendist(fsailendist);
//         l_info->set_bcourse(bcourse.toStdString());
//         l_info->set_bangle(bangle);
//         l_info->set_bminspeed(bminspeed);
//         l_info->set_bmaxspeed(bmaxspeed);
//         l_info->set_bminspeedtime(bminspeedtime);
//         l_info->set_bmaxspeedtime(bmaxspeedtime);
//         l_info->set_bendist(bendist);
//         l_info->set_bdisendist(bdisendist);
//         l_info->set_bsailendist(bsailendist);
//     }
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
// }
