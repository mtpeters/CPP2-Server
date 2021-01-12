#include "CreateDirectoryCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::CreateDirectoryCommand::CreateDirectoryCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{main}
{
}

void Server::Commands::CreateDirectoryCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "please enter the parent dir" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);

	if (!std::filesystem::exists(path)) {
		stream << "Error: no such file or directory" << "\r\n";
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "Error: no permission" << crlf;
		return;
	}

	stream << "please enter the dir name" << crlf;
	std::string name;
	getline(stream, name);
	name.erase(name.end() - 1);

	std::filesystem::create_directory(path + "/" + name, path);

	stream << "OK" << "\r\n";
}