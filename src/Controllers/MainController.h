#pragma once
#include <string>
#include "../Factories/CommandFactory.h"
#include <memory>
namespace Server {
	namespace Controllers {
		class MainController : public std::enable_shared_from_this<MainController> {
		public:
			MainController();

			const std::string& processCommand(const std::string&);
		private:
			Factories::CommandFactory _factory;

		};
	}
}