#pragma once
#include <memory>
#include "../Controllers/MainController.h"

namespace Server {
	namespace Commands {
		class BaseCommand {
		protected:
			std::shared_ptr<Controllers::MainController> _main;
		public:
			BaseCommand(std::shared_ptr<Controllers::MainController> main) : _main{ main } {};

			virtual void execute() = 0;
		};
	}
}