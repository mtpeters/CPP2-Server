#include "GetDirectoryListingCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <time.h>


Server::Commands::GetDirectoryListingCommand::GetDirectoryListingCommand(const std::string root) : BaseCommand{ root }
{
}

void Server::Commands::GetDirectoryListingCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "Please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);
	path = _root + path;
	std::cerr << "client says: " << path << lf;

	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		stream << "ERROR: no such directory" << crlf;
		return;
	}

	int counter = 0;
	std::string type;
	std::ostringstream oss;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_directory()) {
			type = "D";
		}
		else if (entry.is_regular_file()) {
			type = "F";
		}
		else {
			type = "*";
		}

		std::time_t last_time = to_time_t<decltype(entry.last_write_time())>(entry.last_write_time());

		std::stringstream ss;
		ss << std::put_time(std::localtime(&last_time), "%Y-%m-%d %H:%M:%S");

		auto size = entry.file_size();
		std::string name = entry.path().filename().string();

		oss << type << "|" << name << "|" << ss.str() << "|" << size << crlf;
		counter++;
	}

	stream << counter << crlf;
	stream << oss.str();
	stream << "OK" << crlf;
}