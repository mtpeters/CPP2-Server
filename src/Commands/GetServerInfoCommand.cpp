#include "GetServerInfoCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::GetServerInfoCommand::GetServerInfoCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::GetServerInfoCommand::execute(asio::ip::tcp::iostream& client, const std::string&)
{
	client << "Macksly's server 1.0, copyright (c) 2020 Max Peters" << "\r\n";
}
