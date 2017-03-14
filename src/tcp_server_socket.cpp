#include "tcp_server_socket.h"

tcp_server_socket::tcp_server_socket(const string& doc_root)
    : io_service(), acceptor(io_service)
{
    request_handler(doc_root, file_size, port);
    int b = atoi(port.c_str());
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), b);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen();
    accept_connections();
}

void tcp_server_socket::run()
{
    io_service.run();
}
void tcp_server_socket::accept_connections()
{
    socket_connection::pointer new_connection = socket_connection::create(acceptor.get_io_service(), file_size);
    acceptor.async_accept(new_connection->get_socket(), boost::bind(&tcp_server_socket::handle_accept,
                                                                    this, new_connection,
                                                                    boost::asio::placeholders::error));
}
void tcp_server_socket::handle_accept(socket_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_connection->start();
    }

    accept_connections();
  }
void tcp_server_socket::request_handler(const string& doc_root, string& file_size, string& port)
{
    const int MAX=10;
    char buff[MAX];
    std::ifstream fin(doc_root);
    fin.getline(buff, MAX);
    port = buff;
    fin.getline(buff, MAX);
    file_size = buff;
    fin.close();
}
