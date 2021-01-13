#include "MainController.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>

using namespace Server;

Controllers::MainController::MainController() : _factory{"d:/server/"} {}

void Server::Controllers::MainController::run()
{
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

            try {
                processCommand(request);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << crlf;
                _client << e.what() << crlf;
            }

            
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
        _client << "ERROR: Invalid Command" << "\r\n";
    }
}