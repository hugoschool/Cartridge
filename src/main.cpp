#include "Arguments.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    Cartridge::Arguments arguments;

    try {
        arguments.parse(argc, argv);

        return !(arguments.execute() == true);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}
