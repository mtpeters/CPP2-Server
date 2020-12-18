#include "RenameCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::RenameCommand::RenameCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::RenameCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
