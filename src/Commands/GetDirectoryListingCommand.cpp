#include "GetDirectoryListingCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <time.h>


Server::Commands::GetDirectoryListingCommand::GetDirectoryListingCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::GetDirectoryListingCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	std::filesystem::path p(path.substr(1, path.length()));
	std::string type;

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
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

		int year = (last_time / 31556926);
		int rest = last_time - (year * 31556926);
		int month = (rest / 2629743);
		rest = rest - (month * 2629743);
		int day = rest / 86400;
		rest = rest - (day * 86400);
		int hour = rest / 3600;
		rest = rest - (hour * 3600);
		int min = rest / 60;
		rest = rest - (min * 60);
		int sec = rest;

		
		auto size = entry.file_size();
		std::string name = entry.path().filename().string();
		std::string time = std::to_string(day + 1) + "-" + std::to_string(month + 1) + "-" + std::to_string(year + 1970) +  + " " + std::to_string(hour) + "-" + std::to_string(min) + "-" + std::to_string(sec);

		stream << type << "|" << name << "|" << time << "|" << size << " ";
	}

	stream << "\r\n";
}

