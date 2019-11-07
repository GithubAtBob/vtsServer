
#include "StdAfx.h"
#include "DBRadarImageHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBRadarImageHandler::DBRadarImageHandler(void)
{
}


DBRadarImageHandler::~DBRadarImageHandler(void)
{
}

void DBRadarImageHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    Savehandle(s, sqlOperator);
}

void DBRadarImageHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("radar_image_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("lat",RadarImage.view_center_y());
    l_data.insert("lon",RadarImage.view_center_x());
    //l_data.insert("image",QByteArray::fromStdString(RadarImage.image()));
    l_data.insert("image",URL);
    l_data.insert("utc",RadarImage.utc());
    l_data.insert("view_scale",RadarImage.view_scale());
    l_data.insert("clientname",RadarImage.clientname().c_str());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(radar_image_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }  

//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;//¶ÁÈ¡Í¼Æ¬
//     l_pSqlSelectCmd->SetTableName("radar_image_table");
// #include <QImage>
//     //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(Name));
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
//     QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
//     QSqlRecord l_record = l_pSqlRecord->at(0);
//     QImage l_t;
//     auto l_byte = l_record.value("image").toByteArray();
//     l_t.loadFromData(l_byte );
//     bool a = l_t.save("test111.png");
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
}