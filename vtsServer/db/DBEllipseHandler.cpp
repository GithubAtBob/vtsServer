
#include "StdAfx.h"
#include "DBEllipseHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"


DBEllipseHandler::DBEllipseHandler(void)
{
}


DBEllipseHandler::~DBEllipseHandler(void)
{
}

void DBEllipseHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case /*DBEllipseHandlerType::*/Add:
        Addhandle(s, sqlOperator);
        break;
    case /*DBEllipseHandlerType::*/Update:
        Updatehandle(s, sqlOperator);
        break;
    case /*DBEllipseHandlerType::*/Remove:
        Removehandle(s, sqlOperator);
    case /*DBEllipseHandlerType::*/All:
        Allhandle(s, sqlOperator);
        break;
    case /*DBEllipseHandlerType::*/CIsShare:
        Sharehandle(s, sqlOperator);
        break;
    default:
        break;
    }
}

void DBEllipseHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("ellipse_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("shortaxis",ShortAxis);
    l_data.insert("longaxis",LongAxis);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    QByteArray mesID;
    QDataStream outID(&mesID,QIODevice::WriteOnly);
    outID.setVersion(QDataStream::Qt_5_2);
    outID << WaringID;
    l_data.insert("waringID",QVariant(mesID));
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(ellipse_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBEllipseHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("ellipse_table");
    QMap<QString, QVariant> l_data;
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("shortaxis",ShortAxis);
    l_data.insert("longaxis",LongAxis);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    QByteArray mesID;
    QDataStream outID(&mesID,QIODevice::WriteOnly);
    outID.setVersion(QDataStream::Qt_5_2);
    outID << WaringID;
    l_data.insert("waringID",QVariant(mesID));
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    //l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));

//     l_pSqlUpdateCmd->SetData("lon",10);          ///更新具体某项
//     l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(ellipse_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void DBEllipseHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("ellipse_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(ellipse_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Remove true";
    std::cout << Result.toStdString();
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}

void DBEllipseHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("ellipse_table");

    //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(Name));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(ellipse_table all):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    Respon.set_type(Type); 
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Respon.clear_ellipses();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        EllipseRequest* l_requst = Respon.add_ellipses();
        std::string l_ID = l_record.value("ID").toString().toStdString();
        std::string l_name = l_record.value("name").toString().toStdString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        double l_longaxis = l_record.value("longaxis").toDouble();
        double l_shortaxis = l_record.value("shortaxis").toDouble();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        std::string l_waringtype = l_record.value("waringtype").toString().toStdString();
        std::string l_drawman = l_record.value("drawman").toString().toStdString();
        bool l_isshare = l_record.value("isshare").toBool();
        std::string l_linecolor = l_record.value("linecolor").toString().toStdString();
        std::string l_fullcolor = l_record.value("fullcolor").toString().toStdString();
        l_requst->set_type(Type);
        l_requst->set_id(l_ID);
        l_requst->set_name(l_name);
        l_requst->set_lat(l_lat);
        l_requst->set_lon(l_lon);
        l_requst->set_longaxis(l_longaxis);
        l_requst->set_shortaxis(l_shortaxis);
        l_requst->set_linestyle(l_linestyle);
        l_requst->set_fullstyle(l_fullstyle);
        l_requst->set_linewidth(l_linewidth);
        google::protobuf::RepeatedField<google::protobuf::int32> l_proID;
        QDataStream inID(&l_waringID,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_proID;
        for (int i = 0; i < l_proID.size(); i++)
        {
            l_requst->add_waringid(l_proID.Get(i));
        }
        l_requst->set_waringtype(l_waringtype);
        l_requst->set_drawman(l_drawman);
        l_requst->set_isshare(l_isshare);
        l_requst->set_linecolor(l_linecolor);
        l_requst->set_fullcolor(l_fullcolor);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBEllipseHandler::Sharehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("ellipse_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("isshare",IsShare);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("drawman = '%1'").arg(DrawMan));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(ellipse_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}
