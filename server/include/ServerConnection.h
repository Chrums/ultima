#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "Connection.h"
#include <boost/asio.hpp>

class ServerConnection : public Connection<ServerConnection> {
friend class Connection;
public:
    void process(char* buffer, size_t bytes_transferred);
    void connected();
    void disconnected();
private:
    ServerConnection(boost::asio::io_service& io_service);
};

#endif