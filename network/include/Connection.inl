#include <iostream>

#define BUFFER_SIZE 1024

template <class Derived>
std::shared_ptr<Derived> Connection<Derived>::create(boost::asio::io_service& io_service) {
    return std::shared_ptr<Derived>(new Derived(io_service));
}

template <class Derived>
Connection<Derived>::~Connection() {
    
}

template <class Derived>
void Connection<Derived>::execute() {
    this->connected();
    this->listen();
}

template <class Derived>
void Connection<Derived>::send() {
    boost::asio::async_write(this->socket_, boost::asio::buffer(bytes_, BUFFER_SIZE), std::bind(&Connection<Derived>::send_handler, this, std::placeholders::_1));
}

template <class Derived>
boost::asio::ip::tcp::socket& Connection<Derived>::socket() {
    return this->socket_;
}

template <class Derived>
Connection<Derived>::Connection(boost::asio::io_service& io_service) :
    socket_(boost::asio::ip::tcp::socket(io_service)) { }

template <class Derived>
void Connection<Derived>::send_handler(const boost::system::error_code& error) {
    
}

template <class Derived>
void Connection<Derived>::listen() {
    this->socket_.async_read_some(boost::asio::buffer(this->bytes_, BUFFER_SIZE), std::bind(&Connection<Derived>::listen_handler, this, std::placeholders::_1, std::placeholders::_2));
}

template <class Derived>
void Connection<Derived>::listen_handler(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) this->process(this->bytes_, bytes_transferred);
    else std::cout << "Error: " << error << std::endl;
    this->listen();
}