#include "GetDirectoryListingCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <time.h>


Server::Commands::GetDirectoryListingCommand::GetDirectoryListingCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::GetDirectoryListingCommand::execute(asio::ip::tcp::iostream& stream)
{
	stream << "please enter the path" << crlf;
	std::string path;
	getline(stream, path);
	path.erase(path.end() - 1);

	if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
		stream << "Error: no such directory" << crlf;
		return;
	}
	
	int counter = 0;
	std::string type;
	std::ostringstream oss;
	try {
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
			std::tm* tmObj{ std::localtime(&last_time) };

			std::string time = std::to_string(tmObj->tm_mday) + "-" + std::to_string(tmObj->tm_mon) + "-" + std::to_string(tmObj->tm_year + 1900) + +" " + std::to_string(tmObj->tm_hour) + "-" + std::to_string(tmObj->tm_min) + "-" + std::to_string(tmObj->tm_sec);

			auto size = entry.file_size();
			std::string name = entry.path().filename().string();

			oss << type << "|" << name << "|" << time << "|" << size << crlf;
			counter++;
		}

		stream << counter << crlf;
		stream << oss.str();

	}
	catch (...) {
		stream << "Error: something went wrong while reading the files" << crlf;
	}
}