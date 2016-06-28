#ifndef SERVER_H
#define SERVER_H

#include "Singleton.h"
#include <memory>
#include <thread>
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
    void execute();
    void listen();
    void listen_handler(const boost::system::error_code& error, std::shared_ptr<Connection> connection);
    boost::asio::io_service io_service_;
    std::thread* thread_;
    boost::asio::ip::tcp::acceptor* acceptor_;
};

#include "Server.inl"

#endif