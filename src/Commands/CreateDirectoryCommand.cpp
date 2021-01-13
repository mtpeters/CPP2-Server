#include "CreateDirectoryCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::CreateDirectoryCommand::CreateDirectoryCommand(const std::string root) : BaseCommand{root}
{
}

void Server::Commands::CreateDirectoryCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "please enter the parent dir (Empty for root)" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	path = _root + path;

	if (!std::filesystem::exists(path)) {
		stream << "Error: no such file or directory" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "Error: no permission" << crlf;
		return;
	}

	stream << "Please enter the dir name" << crlf;
	std::string name;
	getline(stream, name);
	name.erase(name.end() - 1);

	std::filesystem::create_directory(path + "/" + name, path);

	stream << "OK" << crlf;
}