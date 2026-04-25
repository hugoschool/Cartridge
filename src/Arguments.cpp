#include "Arguments.hpp"
#include "Header.hpp"

Cartridge::HeaderArgument::HeaderArgument() :
    _parser("header", "0", argparse::default_arguments::help),
    _checkSubcommand("check", "0", argparse::default_arguments::help),
    _generateSubcommand("generate", "0", argparse::default_arguments::help),
    _dumpSubcommand("dump", "0", argparse::default_arguments::help)
{
    _dumpSubcommand.add_argument("file").required().help("File to dump");
    _parser.add_subparser(_dumpSubcommand);

    _generateSubcommand.add_argument("-b", "--binary").required().help("input binary file");
    _generateSubcommand.add_argument("-o", "--output").required().help("output binary file");
    _generateSubcommand.add_argument("-n", "--name").help("Game name").default_value("NO NAME");
    _parser.add_subparser(_generateSubcommand);

    _checkSubcommand.add_argument("gba").required().help("GBA file to parse header");
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
    if (_parser.is_subcommand_used("generate")) {
        std::string inputFile = _generateSubcommand.get<std::string>("-b");
        std::string outputFile = _generateSubcommand.get<std::string>("-o");
        std::string gameName = _generateSubcommand.get<std::string>("-n");

        Header::generate(inputFile, outputFile, gameName);

        return true;
    }
    if (_parser.is_subcommand_used("dump")) {
        std::string file = _dumpSubcommand.get<std::string>("file");

        Header header;
        header.readFromFile(file);
        header.dump();

        return true;
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
