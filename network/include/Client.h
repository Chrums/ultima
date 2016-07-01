#ifndef CLIENT_H
#define CLIENT_H

#include "Singleton.h"
#include <string>
#include <memory>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

template <class Derived, class Connection>
class Client : public Singleton<Derived> {
public:
    ~Client();
    std::shared_ptr<Connection> connect(std::string host, int port);
protected:
    Client();
    virtual void client_connected(std::shared_ptr<Connection> connection) = 0;
    virtual void client_disconnected(std::shared_ptr<Connection> connection) = 0;
private:
    void resolve(std::shared_ptr<Connection> connection, boost::asio::ip::tcp::resolver::iterator iterator);
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::resolver resolver_;
    std::thread* thread_;
    std::vector<std::shared_ptr<Connection>> connections_;
};

#include "Client.inl"

#endif