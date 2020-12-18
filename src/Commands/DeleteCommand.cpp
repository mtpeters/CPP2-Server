#include "DeleteCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::DeleteCommand::DeleteCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DeleteCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
