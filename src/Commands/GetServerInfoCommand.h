#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class GetServerInfoCommand : public BaseCommand {
		public:
			GetServerInfoCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}