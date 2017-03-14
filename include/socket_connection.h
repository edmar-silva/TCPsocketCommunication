#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>


class socket_connection : public boost::enable_shared_from_this<socket_connection>
{
public:
    typedef boost::shared_ptr<socket_connection> pointer;
    socket_connection(boost::asio::io_service& io_service, std::string f_size);
    boost::asio::ip::tcp::socket& get_socket();
    void start();
    void set_file_size(std::string f_size);
    static socket_connection::pointer create(boost::asio::io_service& io_service, std::string f_size)
    {
        return socket_connection::pointer(new socket_connection(io_service, f_size));
    }

private:
    boost::asio::ip::tcp::socket socket;
    std::string msg;
    void handle_write(const boost::system::error_code& error);
    void receive_data();
    std::string file_size = "100";
    void handle_read(const boost::system::error_code& ec, std::size_t size);
    enum { max_length = 512 };
    char data_[max_length];
    int i = 1;
    int get_file_size(std::string outFile);
    std::string file_name = "stream";
    void check_size(std::fstream& file);
};

#endif // SOCKET_CONNECTION_H
