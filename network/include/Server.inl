#include <iostream>

template <class Derived, class Connection>
Server<Derived, Connection>::~Server() {
    this->io_service_.stop();
    if (this->acceptor_->is_open()) this->acceptor_->close();
    delete this->acceptor_;
    delete this->thread_;
}

template <class Derived, class Connection>
void Server<Derived, Connection>::run(int port) {
    this->acceptor_ = new boost::asio::ip::tcp::acceptor(this->io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    this->listen();
    this->thread_ = new std::thread([this] () {
        this->io_service_.run();
    });
}

template <class Derived, class Connection>
void Server<Derived, Connection>::listen() {
    std::shared_ptr<Connection> connection = Connection::create(this->io_service_);
    this->acceptor_->async_accept(connection->socket(), [this, &connection] (const boost::system::error_code& error) {
        if (!error) {
            this->client_connected(connection);
            connection->execute();
            this->connections_.push_back(connection);
        } else std::cerr << error << std::endl;
        this->listen();
    });
}