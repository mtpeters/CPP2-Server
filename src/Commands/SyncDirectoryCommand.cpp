#include "SyncDirectoryCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::SyncDirectoryCommand::SyncDirectoryCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::SyncDirectoryCommand::execute(asio::ip::tcp::iostream& stream)
{
	std::string path;
	getline(stream, path);

}
