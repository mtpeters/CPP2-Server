#include "CommandFactory.h"
#include "../Controllers/MainController.h"
#include "../Commands/BaseCommand.h"
#include "../Commands/CreateDirectoryCommand.h"
#include "../Commands/DeleteCommand.h"
#include "../Commands/DisconnectCommand.h"
#include "../Commands/DownloadFileCommand.h"
#include "../Commands/GetDirectoryListingCommand.h"
#include "../Commands/GetServerInfoCommand.h"
#include "../Commands/RenameCommand.h"
#include "../Commands/UploadFileCommand.h"

using namespace Server;

Factories::CommandFactory::CommandFactory(const std::string& root)
{
	_commands.insert(std::make_pair(Enums::CommandEnum::CREATE_DIRECTORY, std::make_unique<Commands::CreateDirectoryCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DELETE_ITEM, std::make_unique<Commands::DeleteCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DISCONNECT, std::make_unique<Commands::DisconnectCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::DOWNLOAD_FILE, std::make_unique<Commands::DownloadFileCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_DIRECTORY_LISTING, std::make_unique<Commands::GetDirectoryListingCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::GET_SERVER_INFO, std::make_unique<Commands::GetServerInfoCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::RENAME, std::make_unique<Commands::RenameCommand>(root)));
	_commands.insert(std::make_pair(Enums::CommandEnum::UPLOAD_FILE, std::make_unique<Commands::UploadFileCommand>(root)));
}

const std::unique_ptr<Commands::BaseCommand>& Factories::CommandFactory::get_command(Enums::CommandEnum command) const
{
	if (_commands.find(command) != _commands.end()) {
		return _commands.at(command);
	}

	return nullptr;
}
