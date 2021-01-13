#include "RenameCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::RenameCommand::RenameCommand(const std::string root) : BaseCommand{ root }
{
}

void Server::Commands::RenameCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "Please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	path = _root + path;
	
	if (!std::filesystem::exists(path)) {
		stream << "ERROR: no such file or directory" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "ERROR: no permission" << crlf;
		return;
	}

	stream << "Please enter the new name" << crlf;
	std::string name;
	getline(stream, name);
	name.erase(name.end() - 1);

	std::filesystem::rename(path, std::filesystem::path(path).parent_path().append(name));

	stream << "OK" << crlf;
}
