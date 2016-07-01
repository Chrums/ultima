#include <iostream>

template <class Derived>
std::shared_ptr<Derived> Connection<Derived>::create(boost::asio::io_service& io_service) {
    return std::shared_ptr<Derived>(new Derived(io_service));
}

template <class Derived>
void Connection<Derived>::execute() {
    this->connected();
    this->receive();
}

template <class Derived>
void Connection<Derived>::send(Message& message) {
    message.decode_header();
    std::cout << Message::HEADER_LENGTH + message.length() << std::endl;
    boost::asio::async_write(this->socket_, boost::asio::buffer(message.data(), Message::HEADER_LENGTH + message.length()), [this, &message] (const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) { std::cout << bytes_transferred << std::endl; }
        else std::cout << error << std::endl;
    });
}

template <class Derived>
boost::asio::ip::tcp::socket& Connection<Derived>::socket() {
    return this->socket_;
}

template <class Derived>
Connection<Derived>::Connection(boost::asio::io_service& io_service) :
    socket_(boost::asio::ip::tcp::socket(io_service)) { }

template <class Derived>
void Connection<Derived>::receive() {
    Message message;
    boost::asio::async_read(this->socket_, boost::asio::buffer(message.data(), Message::HEADER_LENGTH), [this, &message] (const boost::system::error_code& error, size_t bytes_transferred) {
        if (!error) {
            message.decode_header();
            //std::cout << bytes_transferred << std::endl;
            //std::cout << message.length() << std::endl;
            /*
            boost::asio::async_read(this->socket_, boost::asio::buffer(message.body(), message.length()), [this, &message] (const boost::system::error_code& error, size_t bytes_transferred) {
                if (!error) {
                    std::cout.write(message.body(), message.length());
                    std::cout << std::endl;
                    this->receive();
                } else std::cerr << error << std::endl;
            });
            */
        } else {
            if (error == boost::asio::error::eof) this->disconnected();
            else std::cerr << error << std::endl;
        }
    });
}