#include <iostream>

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
    //boost::asio::async_write(this->socket_, boost::asio::buffer())
}

template <class Derived>
boost::asio::ip::tcp::socket& Connection<Derived>::socket() {
    return this->socket_;
}

template <class Derived>
Connection<Derived>::Connection(boost::asio::io_service& io_service) :
    socket_(boost::asio::ip::tcp::socket(io_service)) { }

template <class Derived>
void Connection<Derived>::listen() {
    Message* message = new Message();
    boost::asio::async_read(this->socket_, boost::asio::buffer(message->data(), Message::HEADER_LENGTH), [this, message] (const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            message->decode_header();
            boost::asio::async_read(this->socket_, boost::asio::buffer(message->body(), message->length()), [this, message] (const boost::system::error_code& error, size_t bytes_transferred) {
                if (!error) {
                    std::cout.write(message->body(), message->length());
                    std::cout << std::endl;
                    delete message;
                    this->listen();
                }
            });
        }
    });
}