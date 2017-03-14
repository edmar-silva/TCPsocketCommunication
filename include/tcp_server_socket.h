#ifndef TCP_SERVER_SOCKET_H
#define TCP_SERVER_SOCKET_H

#include "socket_connection.h"
#include <iostream>
#include <boost/asio.hpp>
#include <fstream>


using namespace std;

class tcp_server_socket
{

public:
    explicit tcp_server_socket(const string& doc_rootr);
    void run();
private:
    string file_size = "";
    string port = "";
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;
    void accept_connections();
    void request_handler(const string& doc_root, string& file_size, string& port);
    void handle_accept(socket_connection::pointer new_connection, const boost::system::error_code& error);
};

#endif // TCP_SERVER_SOCKET_H
