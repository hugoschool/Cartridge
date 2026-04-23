#include "argparse.hpp"
#include "Header.hpp"
#include <iostream>

// TODO: not very good argument parsing
int main(int argc, char **argv)
{
    argparse::ArgumentParser program("cartridge");

    auto headerParser = argparse::ArgumentParser("header", "0", argparse::default_arguments::help);
    auto headerCheckSubcommand = argparse::ArgumentParser("check", "0", argparse::default_arguments::none);

    headerCheckSubcommand.add_argument("gba").help("GBA file to parse header");
    headerParser.add_subparser(headerCheckSubcommand);

    program.add_subparser(headerParser);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    if (program.is_subcommand_used("header") &&
            headerParser.is_subcommand_used("check")) {
        std::string gba = headerCheckSubcommand.get<std::string>("gba");
        Cartridge::Header header;

        header.readFromFile(gba);

        std::cout << gba << std::endl;
        header.verifyPrint();

        return 0;
    }
    return 1;
}
