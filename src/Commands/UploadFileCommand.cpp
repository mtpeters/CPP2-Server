#include "UploadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::UploadFileCommand::UploadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::UploadFileCommand::execute(asio::ip::tcp::iostream& stream)
{
	std::string path;
	std::string bytes;
	std::string buffer;
    stream << "ACK" << crlf;

    getline(stream, path);

    std::ofstream out("D:/server/" + std::filesystem::path(path).filename().string(), std::ofstream::binary);
    getline(stream, bytes);
    bytes.erase(bytes.end() - 1);
    getline(stream, buffer);    
    buffer.erase(buffer.end() - 1);

    out.write(buffer.c_str(), std::stoi(bytes));

    out.close();
}
