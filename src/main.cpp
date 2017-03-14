#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <functional>
#include "tcp_server_socket.h"

void ThreadFunction()
{
    int counter = 0;

    //starts server
    try
    {
        std::cout << "Server started..." << std::endl;
        tcp_server_socket server("input.txt");
        server.run();
        std::cout << "Server started..." << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}


int main()
{
    boost::thread t(&ThreadFunction);


    //starts client
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::connect(socket, resolver.resolve({"127.0.0.1", "3000"}));
    std::cout << "Client started..." << std::endl;

    std::cout << "Client started..." << std::endl;
    std::size_t _size = 1024;
    char msg[_size];
    std::cout << "writes your message" << std::endl;
    while(true)
    {
        std::cin.getline(msg, _size);
        size_t msg_length = std::strlen(msg);
        std::cout << "msg: " << msg << " size:" << msg_length << std::endl;
        boost::asio::write(socket, boost::asio::buffer(msg, msg_length));
    }

    return 0;
}
