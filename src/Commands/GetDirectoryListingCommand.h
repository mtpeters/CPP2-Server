#pragma once
#include "../Commands/BaseCommand.h"
#include <chrono>
#include <ctime>

namespace Server {
	namespace Commands {
		class GetDirectoryListingCommand : public BaseCommand {
		public:
			GetDirectoryListingCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		private:

			template <typename TP>
			std::time_t to_time_t(TP tp)
			{
				using namespace std::chrono;
				auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
					+ system_clock::now());
				return system_clock::to_time_t(sctp);
			}
		};
	}
}