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

	std::ifstream input(path, std::ifstream::binary | std::ios::in);

	if (input) {
		input.seekg(0, input.end);
		int length = input.tellg();
		input.seekg(0, input.beg);

		char* buffer = new char[length];

		input.read(buffer, length);
		input.close();

		stream << length << "\n";

		stream.write(buffer, length);

		stream << "OK" << crlf;
	}
	else {
		stream << "ERROR: Cannot download file" << crlf;
	}
}