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
			const std::string crlf{ "\r\n" };
			const std::string lf{ "\n" };
			const std::string _root;
		public:
			BaseCommand(const std::string root) : _root{ root } {};

			virtual void execute(asio::ip::tcp::iostream&) = 0;
		};
	}
}