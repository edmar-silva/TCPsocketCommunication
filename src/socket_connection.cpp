#include "socket_connection.h"

socket_connection::socket_connection(boost::asio::io_service& io_service, std::string f_size) : socket(io_service)
{
    file_size = f_size;
}

boost::asio::ip::tcp::socket& socket_connection::get_socket()
{
    return socket;
}

void socket_connection::start()
{
    std::cout << "Connection started!" << std::endl;
    msg = "Hello client!";
    boost::asio::async_write(socket, boost::asio::buffer(msg),
                             boost::bind(&socket_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error));
}

void socket_connection::handle_write(const boost::system::error_code& ec)
{
    memset (&data_, 0, sizeof (data_) );
    if (!ec)
    {
        socket.async_read_some(boost::asio::buffer(data_, max_length),
                               boost::bind(&socket_connection::handle_read, shared_from_this(),
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        throw boost::system::system_error(ec);
    }
}

void socket_connection::handle_read(const boost::system::error_code& ec, std::size_t size)
{
    receive_data();
    memset (&data_, 0, sizeof (data_) );
    if (!ec)
    {
        socket.async_read_some(boost::asio::buffer(data_, max_length),
                               boost::bind(&socket_connection::handle_read, shared_from_this(),
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        throw boost::system::system_error(ec);
    }
}

void socket_connection::receive_data()
{
    std::fstream file;
    check_size(file);
    for(int i=0; i < std::strlen(data_); i++)
    {
        file.put(data_[i]);
    }
    file.put('\n');
    file.close();
}
int socket_connection::get_file_size(std::string outFile)
{
    std::fstream file(outFile, std::ios_base::in | std::ios_base :: app);
    int cnt = 0;
    char ch;
    file.seekg(0);
    while(file.get(ch))
    {
        cnt++;
    }
    file.close();
    std::cout << cnt << std::endl;
    return cnt;
}

void socket_connection::check_size(std::fstream& file)
{
    if (get_file_size(file_name) <= atoi(file_size.c_str()))
    {
        file.open(file_name, std::ios_base::out | std::ios_base :: app);
    }
    else
    {
        std::cout << "entrou no else" << std::endl;
        file.close();
        file_name.append(boost::lexical_cast<std::string>(i));
        file.open(file_name, std::ios_base::out | std::ios_base :: app);
        if(!file)
        {
            std::cerr << " stream file cannot be opened\n";
            exit(-1);
        }
        i++;
    }
}
