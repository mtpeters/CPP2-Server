#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class UploadFileCommand : public BaseCommand {
		public:
			UploadFileCommand(const std::string& root);

			void execute(asio::ip::tcp::iostream&);
		};
	}
}