#pragma once
#include <QVariant>
class PointMes;
class ChannelWay;
class QuickData;
class TargetInfoData;
QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<PointMes> &point);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<PointMes> &point);

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedField<google::protobuf::int32> &ID);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedField<google::protobuf::int32> &ID);

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<ChannelWay> &channel);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<ChannelWay> &channel);

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<std::string> &ID);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<std::string> &ID);

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<QuickData> &Quick);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<QuickData> &Quick);

QDataStream &operator << (QDataStream &out,google::protobuf::RepeatedPtrField<TargetInfoData> &tar);
QDataStream &operator>>(QDataStream &in, google::protobuf::RepeatedPtrField<TargetInfoData> &tar);
struct AIS
{
    double lat;
    double lon;
    QString AISID;
    QDate timeAIS;
};