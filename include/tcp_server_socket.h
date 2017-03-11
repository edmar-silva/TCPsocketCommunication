#ifndef TCP_SERVER_SOCKET_H
#define TCP_SERVER_SOCKET_H

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <boost/array.hpp>

using namespace std;

class tcp_server_socket
{
public:
    /** Default constructor */
    explicit tcp_server_socket(const string& doc_rootr);

    /** Default destructor */
    virtual ~tcp_server_socket();

    void run();


private:

    std::string file_size = "";
    std::string port = "";
    std::array<char, 4096> bytes;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;

    ///accept new connections
    void accept_connections();

    /// Extracts configuration data
    void request_handler(const string& doc_root, string& file_size, string& port);

    void receive_data( string file_size);
};

#endif // TCP_SERVER_SOCKET_H
