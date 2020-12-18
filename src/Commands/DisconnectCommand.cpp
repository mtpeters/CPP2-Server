#include "DisconnectCommand.h"

Server::Commands::DisconnectCommand::DisconnectCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DisconnectCommand::execute()
{
}
