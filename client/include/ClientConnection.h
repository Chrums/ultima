#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "Connection.h"
#include <boost/asio.hpp>

class ClientConnection : public Connection<ClientConnection> {
friend class Connection;
protected:
    void process(char* buffer, size_t bytes_transferred);
    void connected();
    void disconnected();
private:
    ClientConnection(boost::asio::io_service& io_service);
};

#endif