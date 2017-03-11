#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <functional>
#include "tcp_server_socket.h"

void ThreadFunction()
{
    cout << "Running the Thread" << endl;
    cout << "Waiting connections..." << endl;

    //boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    tcp_server_socket server("input.txt");
    server.run();

}

int main()
{


    boost::thread t{ThreadFunction};

    //t.interrupt();
    //t.join();
    cout << "Enter the message stream" << endl;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::connect(socket, resolver.resolve({"127.0.0.1", "3000"}));
    io_service.run();

    std::size_t _size = 1024;
    std::string msg;
    cout << "Enter the message stream" << endl;
    cin >> msg;

    std::function<void(const boost::system::error_code&, std::size_t)> f = [&]
    (const boost::system::error_code& error, std::size_t bytes_transferred) {};

    while(true) {
        boost::asio::async_write(socket, boost::asio::buffer(msg, _size), f);
        cout << "Enter the message stream" << endl;
        cin >> msg;
    }
    return 0;
}
