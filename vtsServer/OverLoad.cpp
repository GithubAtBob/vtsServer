#include "StdAfx.h"
#include "OverLoad.h"
#include "message/PointMes.pb.h"
#include "message/channel.pb.h"
#include "message/userhabit.pb.h"

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<PointMes> &point)
{
    for (int i=0;i<point.size();i++)
    {
        out << point.Get(i).lat() << point.Get(i).lon();
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<PointMes> &point) {
    double lat;
    double lon;
    for (int i=0;;i++)
    {
        if (in.atEnd())
        {
            break;
        }
        in >> lat >> lon;
        PointMes* l_point = point.Add();
        l_point->set_lat(lat);
        l_point->set_lon(lon);
    }
    return in;
}

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedField<google::protobuf::int32> &ID)
{
    for (int i=0;i<ID.size();i++)
    {
        out << ID.Get(i);
    }
    return out;
}

QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedField<google::protobuf::int32> &ID) {
    google::protobuf::int32 l_ID;
    for (int i=0;;i++)
    {
        if (in.atEnd())
        {
            break;
        }
        in >> l_ID;
        ID.Add(l_ID);
    }
    return in;
}

QDataStream & operator<<(QDataStream &out,google::protobuf::RepeatedPtrField<ChannelWay> &channel)
{
    for (int  i = 0; i < channel.size(); i++)
    {
        ChannelWay l_way = channel.Get(i);
        auto l_points = l_way.point();
        for ( int j = 0; j < l_points.size(); j++)
        {
            PointMes l_mes = l_points.Get(j);
            out << l_mes.lat() << l_mes.lon();
        }
    }
    return out;
}

QDataStream & operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<ChannelWay> &channel)
{
    double lat;
    double lon;
    int count = 0;
    ChannelWay* l_way;
    for (int i=0;;i++)
    {
        if (in.atEnd())
        {
            break;
        }
        in >> lat >> lon;
        count++;
        if (count == 1)
        {
            l_way = channel.Add();
        }
        PointMes* l_point = l_way->add_point();
        l_point->set_lat(lat);
        l_point->set_lon(lon);
        if (count == 10)
        {
            count = 0;
        }
    }
    return in;
}

QDataStream & operator<<(QDataStream &out,google::protobuf::RepeatedPtrField<std::string> &ID)
{
    for (int i=0;i<ID.size();i++)
    {
        out << QString::fromStdString(ID.Get(i).c_str());
    }
    return out;
}

QDataStream & operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<std::string> &ID)
{
    QString l_ID;
//     for (int i=0;;i++)
//     {
//         if (in.atEnd())
//         {
//             break;
//         }
    while (!in.atEnd())
    {
        in >> l_ID;
        std::string* l_str = ID.Add();
        l_str->append(l_ID.toStdString());

    }
/*    }*/
    return in;
}

QDataStream & operator<<(QDataStream &out,google::protobuf::RepeatedPtrField<QuickData> &Quick)
{
    for (int i = 0; i < Quick.size(); i++)
    {
        out << QString::fromStdString(Quick.Get(i).name().c_str()) << Quick.Get(i).lat() << Quick.Get(i).lon();
    }
    return out;
}

QDataStream & operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<QuickData> &Quick)
{
    QString name;
    double lat,lon;
    while (!in.atEnd())
    {
        in >> name >> lat >> lon;
        QuickData* l_data = Quick.Add();
        l_data->set_name(name.toStdString());
        l_data->set_lat(lat);
        l_data->set_lon(lon);
    }
    return in;
}

QDataStream & operator<<(QDataStream &out,google::protobuf::RepeatedPtrField<TargetInfoData> &tar)
{
    for (int i = 0; i < tar.size(); i++)
    {
        out << tar.Get(i).index() << tar.Get(i).checked();
    }
    return out;
}

QDataStream & operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<TargetInfoData> &tar)
{
    int l_index;
    bool l_checked;
    while (!in.atEnd())
    {
        in >> l_index >> l_checked;
        auto l_data = tar.Add();
        l_data->set_index(l_index);
        l_data->set_checked(l_checked);
    }
    return in;

}