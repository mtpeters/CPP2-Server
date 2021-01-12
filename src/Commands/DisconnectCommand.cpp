#include "DisconnectCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::DisconnectCommand::DisconnectCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DisconnectCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "Bye." << crlf;
	std::cerr << "will disconnect from client " << stream.socket().local_endpoint() << crlf;
	stream.socket().close();
}
