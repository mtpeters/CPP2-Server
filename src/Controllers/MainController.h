#pragma once
#include <string>
#include <memory>
#include "../Factories/CommandFactory.h"

namespace Server {
	namespace Controllers {
		class MainController {
		public:
			MainController();

			void processCommand(const std::string&);
			void run();
		private:
			const int server_port{ 12345 };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream _client;
			Factories::CommandFactory _factory;
		};
	}
}