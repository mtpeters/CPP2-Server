#include "CreateDirectoryCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::CreateDirectoryCommand::CreateDirectoryCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{main}
{
}

void Server::Commands::CreateDirectoryCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
