#pragma once

#include "frame/vtsRequestHandler.h"

class hgGPSComHandler :
	public vtsRequestHandler
{
public:
	hgGPSComHandler();
	~hgGPSComHandler(void);

	WorkMode workMode();

	void handle(boost::asio::const_buffer& data);

protected:
	void afterResponse(const boost::system::error_code& e);
};
