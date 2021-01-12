#include "MainController.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>

using namespace Server;

Controllers::MainController::MainController() {}

void Server::Controllers::MainController::run()
{
    _factory = { shared_from_this() };
    const int server_port{ 12345 };
    const char* lf{ "\n" };
    const char* crlf{ "\r\n" };

    asio::io_context io_context;
    asio::ip::tcp::acceptor server{ io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), server_port) };

    for (;;) {
        std::cerr << "waiting for client to connect\n";

        server.accept(_client.socket());
        std::cerr << "client connected from " << _client.socket().local_endpoint() << lf;
        _client << "Welcome to Macksly's server 1.0" << crlf;
        for (;;) {
            std::string request;
            getline(_client, request);
            request.erase(request.end() - 1); // remove '\r'
            std::cerr << "client says: " << request << lf;

            processCommand(request);
            
            if (request == "QUIT") { 
                break;
            }
        }
    }
}

void Controllers::MainController::processCommand(const std::string& command)
{
    if (command == "INFO") {
        _factory.get_command(Enums::CommandEnum::GET_SERVER_INFO)->execute(_client);
    }
    else if (command == "DIR") {
        _factory.get_command(Enums::CommandEnum::GET_DIRECTORY_LISTING)->execute(_client);
    }
    else if (command == "QUIT") {
        _factory.get_command(Enums::CommandEnum::DISCONNECT)->execute(_client);
    }
    else if (command == "GET") {
        _factory.get_command(Enums::CommandEnum::DOWNLOAD_FILE)->execute(_client);
    }
    else if (command == "PUT") {
        _factory.get_command(Enums::CommandEnum::UPLOAD_FILE)->execute(_client);
    }
    else if (command == "REN") {
        _factory.get_command(Enums::CommandEnum::RENAME)->execute(_client);
    }
    else if (command == "DEL") {
        _factory.get_command(Enums::CommandEnum::DELETE_ITEM)->execute(_client);
    }
    else if (command == "MKDIR") {
        _factory.get_command(Enums::CommandEnum::CREATE_DIRECTORY)->execute(_client);
    }
    else {
        _client << "Invalid Command" << "\r\n";
    }
}