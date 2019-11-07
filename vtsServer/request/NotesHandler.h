#pragma once

#include "frame/vtsRequestHandler.h"

class DBNotesHandler;
class NotesRequest;
class NotesHandler :
    public vtsRequestHandler
{
public:
    NotesHandler();
    ~NotesHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBNotesHandler* db);

    void UpdateFunction(NotesRequest msg);

    void RemoveFunction(NotesRequest msg);

    void AllFunction(NotesRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("notes", NotesHandler);