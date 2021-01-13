#include "DownloadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::DownloadFileCommand::DownloadFileCommand(const std::string root) : BaseCommand{ root }
{
}

void Server::Commands::DownloadFileCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "Please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	path = _root + path;

	if (!std::filesystem::exists(path) || std::filesystem::is_directory(path)) {
		stream << "ERROR: no such file" << crlf;
		return;
	}

	if (std::filesystem::status(path).permissions() != std::filesystem::perms::all) {
		stream << "ERROR: no permission" << crlf;
		return;
	}

	std::ifstream input(path, std::ifstream::binary | std::ios::in);

	if (input) {
		int length = std::filesystem::file_size(path);

		std::unique_ptr<char> buffer(new char[length]);

		input.read(buffer.get(), length);
		input.close();

		stream << length << "\n";

		stream.write(buffer.get(), length);

		stream << "OK" << crlf;
	}
	else {
		stream << "ERROR: Cannot download file" << crlf;
	}
}