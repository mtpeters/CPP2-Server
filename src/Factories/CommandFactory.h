#pragma once
#include <memory>
#include <map>
#include "../Enums/CommandEnum.h"
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Factories {
		class CommandFactory {
		private:
			std::map<Enums::CommandEnum, std::unique_ptr<Commands::BaseCommand>> _commands;

		public:
			CommandFactory(const std::string&);

			const std::unique_ptr<Commands::BaseCommand>& get_command(Enums::CommandEnum) const;
		};
	}
}