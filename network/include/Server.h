#ifndef SERVER_H
#define SERVER_H

#include "Singleton.h"
#include <memory>
#include <thread>
#include <utility>
#include <functional>
#include <vector>
#include <boost/asio.hpp>

template <class Derived, class Connection>
class Server : public Singleton<Derived> {
public:
    ~Server();
    void run(int port);
protected:
    Server() = default;
    virtual void client_connected(std::shared_ptr<Connection> connection) = 0;
    virtual void client_disconnected(std::shared_ptr<Connection> connection) = 0;
private:
    void listen();
    boost::asio::io_service io_service_;
    std::thread* thread_;
    boost::asio::ip::tcp::acceptor* acceptor_;
    std::vector<std::shared_ptr<Connection>> connections_;
};

#include "Server.inl"

#endif