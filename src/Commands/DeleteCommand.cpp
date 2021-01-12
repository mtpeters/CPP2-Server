#include "DeleteCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::DeleteCommand::DeleteCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DeleteCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);

	if (!std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
		stream << "Error: no such file" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "Error: no permission" << crlf;
		return;
	}

	std::filesystem::remove(path);

	stream << "OK" << "\r\n";
}
