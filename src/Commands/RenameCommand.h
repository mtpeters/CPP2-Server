#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class RenameCommand : public BaseCommand {
		public:
			RenameCommand(const std::string root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}