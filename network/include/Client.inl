#include <iostream>

template <class Derived, class Connection>
Client<Derived, Connection>::~Client() {
    
}

template <class Derived, class Connection>
std::shared_ptr<Connection> Client<Derived, Connection>::connect(std::string host, int port) {
    boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
    boost::asio::ip::tcp::resolver::iterator iterator = resolver_.resolve(query);
    std::shared_ptr<Connection> connection = Connection::create(this->io_service_);
    this->resolve(connection, iterator);
    return connection;
}

template <class Derived, class Connection>
Client<Derived, Connection>::Client() :
    resolver_(this->io_service_) { }

template <class Derived, class Connection>
void Client<Derived, Connection>::resolve(std::shared_ptr<Connection> connection, boost::asio::ip::tcp::resolver::iterator iterator) {
    connection->socket().async_connect(*iterator, std::bind(&Client::resolve_handler, this, std::placeholders::_1, connection, iterator));
}

template <class Derived, class Connection>
void Client<Derived, Connection>::resolve_handler(const boost::system::error_code& error, std::shared_ptr<Connection> connection, boost::asio::ip::tcp::resolver::iterator iterator) {
    if (error) {
        if (iterator == boost::asio::ip::tcp::resolver::iterator()) std::cout << "Failed to connect." << std::endl;
        else resolve(connection, ++iterator);
    } else connection->execute();
}