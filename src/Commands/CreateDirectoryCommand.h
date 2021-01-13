#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class CreateDirectoryCommand : public BaseCommand {
		public:
			CreateDirectoryCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}