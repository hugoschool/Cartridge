#include "Arguments.hpp"
#include "Build.hpp"
#include "Header.hpp"
#include "argparse.hpp"
#include <exception>
#include <iostream>
#include <ostream>

Cartridge::HeaderArgument::HeaderArgument() :
    AArgument("header", argparse::default_arguments::help),
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

Cartridge::BuildArgument::BuildArgument() : AArgument("build")
{
    _parser.add_argument("path").default_value(".");
}

Cartridge::BuildArgument::~BuildArgument()
{
}

bool Cartridge::BuildArgument::execute()
{
    try {
        std::string file = _parser.get("path");
        Build build(file);
        build.build();
        return true;
    } catch (std::exception &e) {
        return false;
    }
    return false;
}

Cartridge::AArgument::AArgument(const std::string name, argparse::default_arguments args) :
    _parser(name, "0", args)
{
}

argparse::ArgumentParser &Cartridge::AArgument::getParser()
{
    return _parser;
}

Cartridge::Arguments::Arguments() :
    AArgument("cartridge", argparse::default_arguments::help),
    _headerArgument(),
    _buildArgument()
{
    _parser.add_subparser(_headerArgument.getParser());
    _parser.add_subparser(_buildArgument.getParser());
}

void Cartridge::Arguments::parse(int &argc, char **argv)
{
    try {
        _parser.parse_args(argc, argv);
    } catch (std::exception &e) {
        std::cerr << _parser;
    }
}

bool Cartridge::Arguments::execute()
{
    if (_parser.is_subcommand_used("header")) {
        return _headerArgument.execute();
    } else if (_parser.is_subcommand_used("build")) {
        return _buildArgument.execute();
    }
    return false;
}
