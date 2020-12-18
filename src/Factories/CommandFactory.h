#pragma once
#include <memory>
#include <map>
#include "../Enums/CommandEnum.h"

namespace Server {
	namespace Controllers {
		class MainController;
	}

	namespace Commands {
		class BaseCommand;
	}

	namespace Factories {
		class CommandFactory {
		private:
			std::map<Enums::CommandEnum, std::unique_ptr<Commands::BaseCommand>> _commands;

		public:
			CommandFactory(const std::shared_ptr<Controllers::MainController>);

			const std::unique_ptr<Commands::BaseCommand>& get_command(Enums::CommandEnum) const;
		};
	}
}