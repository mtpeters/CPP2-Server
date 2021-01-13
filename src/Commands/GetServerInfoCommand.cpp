#include "GetServerInfoCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::GetServerInfoCommand::GetServerInfoCommand(const std::string& root) : BaseCommand{ root }
{
}

void Server::Commands::GetServerInfoCommand::execute(asio::ip::tcp::iostream& client)
{
	client << "Macksly's server 1.0, copyright (c) 2020 Max Peters" << "\r\n";
}
