#include "UploadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::UploadFileCommand::UploadFileCommand(const std::string& root) : BaseCommand{ root }
{
}

void Server::Commands::UploadFileCommand::execute(asio::ip::tcp::iostream& stream)
{
    // get path
	std::string path;
    getline(stream, path);
    path = _root + path;
    std::cerr << "client says: " << path << lf;

    // get bytes
    std::string val;
    getline(stream, val);
    std::cerr << "client says: " << val << lf;

    // get buffer
    int bytes = std::stoi(val);
    std::unique_ptr<char> buffer(new char[bytes]);
    
    if (std::filesystem::space(_root).available - bytes < 0) {
        stream << "ERROR: not enough space" << crlf;
        return;
    }

    if (stream.read(buffer.get(), bytes)) {
        std::ofstream out(path, std::ofstream::binary);
        out.write(buffer.get(), bytes);
        out.close();

        stream << "OK" << crlf;
        return;
    }
    else {
        stream << "ERROR: Could not upload file" << crlf;
    }
}
