#include "tcp_server_socket.h"

tcp_server_socket::tcp_server_socket(const string& doc_root)
    : io_service(), acceptor(io_service), socket(io_service)
{



    request_handler(doc_root, file_size, port);

    int b = atoi(port.c_str());

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), b);
    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen();
    accept_connections();
}

tcp_server_socket::~tcp_server_socket()
{

}

void tcp_server_socket::run()
{
    io_service.run();
}

void tcp_server_socket::accept_connections()
{
    acceptor.accept(socket);

    receive_data(file_size);
}

void  tcp_server_socket::request_handler(const string& doc_root, string& file_size, string& port)
{
    const int MAX=10;
    char buff[MAX];

    ifstream fin(doc_root);

    fin.getline(buff, MAX);
    port = buff;
    fin.getline(buff, MAX);
    file_size = buff;


}

void  tcp_server_socket::receive_data(string file_size)
{
    std::function<void(const boost::system::error_code&, std::size_t)> f = [&]
    (const boost::system::error_code& error, std::size_t bytes_transferred) {};

    const int size_ = atoi(file_size.c_str());
    string msg;
    boost::system::error_code error;

    ofstream outFile("stream.txt");
    if(!outFile )   // Abertura falhou ...
    {
        cerr << " stream.txt file cannot be opened\n";
        exit(-1);
    }

    while(true)
    {
        size_t len = socket.read_some(boost::asio::buffer(bytes), error);

        msg = bytes.data();
        if (msg.compare("exit")==0) break;

        for(int i=0; i < msg.size(); i++)
        {
            outFile.put(msg[i]);
            cout <<  msg[i];
        }
    }
    outFile.close();
}
