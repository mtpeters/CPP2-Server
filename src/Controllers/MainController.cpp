#include "MainController.h"

using namespace Server;

Controllers::MainController::MainController() : _factory{ shared_from_this() } {}

const std::string& Controllers::MainController::processCommand(const std::string& command)
{
	if (command == "info") {

	}
}
