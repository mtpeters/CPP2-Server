#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class GetDirectoryListingCommand : public BaseCommand {
		public:
			GetDirectoryListingCommand(std::shared_ptr<Controllers::MainController>);

			void execute();
		};
	}
}