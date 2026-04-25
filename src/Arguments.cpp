#include "Arguments.hpp"
#include "Header.hpp"

Cartridge::HeaderArgument::HeaderArgument() :
    _parser("header", "0", argparse::default_arguments::help),
    _checkSubcommand("check", "0", argparse::default_arguments::none)
{
    _checkSubcommand.add_argument("gba").help("GBA file to parse header");
    _parser.add_subparser(_checkSubcommand);
}

bool Cartridge::HeaderArgument::execute()
{
    if (_parser.is_subcommand_used("check")) {
        std::string gba = _checkSubcommand.get<std::string>("gba");
        Cartridge::Header header;

        header.readFromFile(gba);

        std::cout << gba << std::endl;

        return header.verify(true);
    }
    return false;
}

Cartridge::Arguments::Arguments() :
    _globalParser("cartridge"),
    _headerArgument()
{
    _globalParser.add_subparser(_headerArgument._parser);
}

void Cartridge::Arguments::parse(int &argc, char **argv)
{
    try {
        _globalParser.parse_args(argc, argv);
    } catch (std::exception &e) {
        std::cerr << _globalParser;
    }
}

bool Cartridge::Arguments::execute()
{
    if (_globalParser.is_subcommand_used("header")) {
        return _headerArgument.execute();
    }
    return false;
}
