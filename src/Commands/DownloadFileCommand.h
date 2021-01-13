#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DownloadFileCommand : public BaseCommand {
		public:
			DownloadFileCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);

		};
	}
}