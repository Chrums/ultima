#include <iostream>

template <class Derived, class Connection>
Client<Derived, Connection>::~Client() {
    delete this->thread_;
}

template <class Derived, class Connection>
std::shared_ptr<Connection> Client<Derived, Connection>::connect(std::string host, int port) {
    boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
    boost::asio::ip::tcp::resolver::iterator iterator = resolver_.resolve(query);
    std::shared_ptr<Connection> connection = Connection::create(this->io_service_);
    this->resolve(connection, iterator);
    this->thread_ = new std::thread([this] () {
        this->io_service_.run();
    });
    return connection;
}

template <class Derived, class Connection>
Client<Derived, Connection>::Client() :
    resolver_(this->io_service_) {
    
}

template <class Derived, class Connection>
void Client<Derived, Connection>::resolve(std::shared_ptr<Connection> connection, const boost::asio::ip::tcp::resolver::iterator iterator) {
    boost::asio::async_connect(connection->socket(), iterator, [this, connection] (const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iterator) {
        if (!error) {
            connection->execute();
            this->connections_.push_back(connection);
        } else {
            if (iterator == boost::asio::ip::tcp::resolver::iterator()) std::cerr << error << std::endl;
            else this->resolve(connection, ++iterator);
        }
    });
}