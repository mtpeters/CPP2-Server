#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DisconnectCommand : public BaseCommand {
		public:
			DisconnectCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}