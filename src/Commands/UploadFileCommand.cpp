#include "UploadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::UploadFileCommand::UploadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::UploadFileCommand::execute(asio::ip::tcp::iostream& stream)
{
    // get path
	std::string path;
    getline(stream, path);
    std::cerr << "client - path: " << path << '\n';

    // get bytes
    std::string bytes;
    getline(stream, bytes);
    std::cerr << "client - bytes: " << bytes << '\n';

    // get buffer
    std::string buffer;
    getline(stream, buffer);    
    buffer.erase(buffer.end() - 1);
    std::cerr << "client - data: " << buffer << '\n';

    std::ofstream out("D:/server/" + std::filesystem::path(path).filename().string(), std::ofstream::binary);
    out.write(buffer.c_str(), std::stoi(bytes));

    out.close();

    stream << "OK" << crlf;
}
