#include "DownloadFileCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::DownloadFileCommand::DownloadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DownloadFileCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
