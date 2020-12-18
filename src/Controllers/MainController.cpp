#include "MainController.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>

using namespace Server;

Controllers::MainController::MainController() {}

void Controllers::MainController::processCommand(const std::string& command, const std::string& path)
{
	if (command == "info") {
		_factory.get_command(Enums::CommandEnum::GET_SERVER_INFO)->execute(_client);
	} else if (command == "dir") {
		_factory.get_command(Enums::CommandEnum::GET_DIRECTORY_LISTING)->execute(_client, path);
	}
    else if (command == "disconnect") {
        _factory.get_command(Enums::CommandEnum::DISCONNECT)->execute(_client);
    }
}

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

            
            processCommand(request.substr(0, request.find(" ")), request.substr(3, request.length()));

            if (request == "disconnect") {
                break;
            }
        }
    }
}
