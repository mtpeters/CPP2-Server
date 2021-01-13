#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DeleteCommand : public BaseCommand {
		public:
			DeleteCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}