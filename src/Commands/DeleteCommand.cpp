#include "DeleteCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::DeleteCommand::DeleteCommand(const std::string& root) : BaseCommand{ root }
{
}

void Server::Commands::DeleteCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "Please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	path = _root + path;
	std::cerr << "client says: " << path << lf;

	if (!std::filesystem::exists(path)) {
		stream << "ERROR: no such file" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "ERROR: no permission" << crlf;
		return;
	}

	std::filesystem::remove_all(path);

	stream << "OK" << crlf;
}
