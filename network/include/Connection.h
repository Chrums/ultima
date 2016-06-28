#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include <thread>
#include <boost/asio.hpp>

template <class Derived>
class Connection : public std::enable_shared_from_this<Derived> {
public:
    static std::shared_ptr<Derived> create(boost::asio::io_service& io_service);
    ~Connection();
    void execute();
    void send();
    boost::asio::ip::tcp::socket& socket();
    virtual void process(char* buffer, size_t bytes_transferred) = 0;
    virtual void connected() = 0;
    virtual void disconnected() = 0;
protected:
    Connection(boost::asio::io_service& io_service);
private:
    void send_handler(const boost::system::error_code& error);
    void listen();
    void listen_handler(const boost::system::error_code& error, size_t bytes_transferred);
    boost::asio::ip::tcp::socket socket_;
    char bytes_[1024];
};

#include "Connection.inl"

#endif