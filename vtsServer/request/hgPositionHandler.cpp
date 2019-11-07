
#include "StdAfx.h"
#include "hgPositionHandler.h"

#include "message/hgPositionPrediction.pb.h"
#include "hgAisDecoder.h"
#include "hgutils/PointLL.h"
#include "hgutils/NavUtil.h"

hgPositionHandler::hgPositionHandler()
{

}

hgPositionHandler::~hgPositionHandler(void)
{
}

vtsRequestHandler::WorkMode hgPositionHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgPositionHandler::handle(boost::asio::const_buffer& data)
{
    hgPositionRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));

    hg::utils::PointLL l_startPointLL;
    l_startPointLL.setLat(msg.lat());
    l_startPointLL.setLon(msg.lon());
    hg::utils::PointLL l_PredictPointLL;
    l_PredictPointLL = hg::utils::navutil::getPoint(l_startPointLL, msg.sog()*msg.time()/60, msg.cog());

    hgPositionRepsone l_PositionRepsone;
    l_PositionRepsone.set_mmsi(msg.mmsi());
    l_PositionRepsone.set_lat(l_PredictPointLL.lat());
    l_PositionRepsone.set_lon(l_PredictPointLL.lon());
    response(l_PositionRepsone, boost::bind(&hgPositionHandler::afterResponse, this, boost::asio::placeholders::error));
 
}


void hgPositionHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
