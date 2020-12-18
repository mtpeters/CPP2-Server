#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <asio.hpp>

namespace Server {
	namespace Controllers {
		class MainController;
	}

	namespace Commands {
		class BaseCommand {
		protected:
			std::shared_ptr<Controllers::MainController> _main;
		public:
			BaseCommand(std::shared_ptr<Controllers::MainController> main) : _main{ main } {};

			virtual void execute(asio::ip::tcp::iostream&, const std::string& = "") = 0;
		};
	}
}