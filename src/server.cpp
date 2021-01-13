#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include "Controllers/MainController.h"

int main() {
    try {
        Server::Controllers::MainController _main;
        _main.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "Unknown Error" << '\n';
    }

    _CrtDumpMemoryLeaks();
    return EXIT_FAILURE;
}
