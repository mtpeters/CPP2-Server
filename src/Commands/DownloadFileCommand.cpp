#include "DownloadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::DownloadFileCommand::DownloadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DownloadFileCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	
	if (!std::filesystem::exists(path) || std::filesystem::is_directory(path)) {
		stream << "Error: no such file" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "Error: no permission" << crlf;
		return;
	}

	auto bytes = std::filesystem::file_size(path);
	stream << bytes << crlf;
	
	std::ifstream input(path, std::ios::binary);
	stream << input.rdbuf() << crlf;

	return;
}
