#include "Arguments.hpp"
#include "Build.hpp"
#include "Convert.hpp"
#include "Header.hpp"
#include "argparse.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

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

Cartridge::EmuArgument::EmuArgument() : AArgument("emu", argparse::default_arguments::help)
{
    _parser.add_argument("--path").default_value(getEmulatorConfigPath());
    _parser.add_argument("--rom").required();
}

bool Cartridge::EmuArgument::execute()
{
    try {
        std::string emulatorPath = _parser.get("--path");
        std::string rom = _parser.get("--rom");
        if (emulatorPath.empty()) {
            std::cerr << "No valid emulator path" << std::endl;
            return false;
        }
        const std::string systemCommand(emulatorPath + " --rom " + rom.c_str());
        std::system(systemCommand.c_str());
        return true;
    } catch (std::exception &e) {
        return false;
    }
    return false;
}

std::string Cartridge::EmuArgument::getEmulatorConfigPath() const
{
    const char *xdg_value = getenv("XDG_CONFIG_HOME");
    const char *home = getpwuid(getuid())->pw_dir;
    const std::string defaultPath = std::string(home) + "/.config";
    std::string fullPath;

    if (xdg_value == NULL) {
        fullPath += defaultPath;
    } else {
        fullPath += xdg_value;
    }
    const std::filesystem::path currentPath = std::filesystem::current_path();

    std::filesystem::current_path(fullPath);
    fullPath += "/cartridge";
    try {
        std::filesystem::create_directory(fullPath);
    } catch (const std::exception &e) {
        std::cerr << "Impossible to create " << fullPath << std::endl;
        std::filesystem::current_path(currentPath);
        return std::string();
    }
    std::filesystem::current_path(currentPath);
    fullPath += "/emulator_path";
    if (std::filesystem::exists(fullPath)) {
        std::ifstream stream(fullPath);
        std::string content;

        stream >> content;
        return content;
    }
    return std::string();
}

Cartridge::ConvArgument::ConvArgument() : AArgument("conv", argparse::default_arguments::help)
{
    _parser.add_argument("-p", "--path").help("path to the font asset").required();
    _parser.add_argument("-o", "--output").help("generated C file").required();
    _parser.add_argument("-w", "--width").help("width size of char in pixel").required();
    _parser.add_argument("-h", "--height").help("height size of char in pixel").required();
    _parser.add_argument("-m", "--margin").help("margin between char in pixel").required();
    _parser.add_argument("-l", "--line-height").help("virtual alignement line height in pixel").required();
}

bool Cartridge::ConvArgument::execute()
{
    try {
        std::string assetPath = _parser.get("--path");
        std::string assetFilename = std::filesystem::path(assetPath).filename().replace_extension("");

        // Requires imagemagick
        if (assetPath.ends_with(".xcf")) {
            const std::string command("convert " + assetPath + " /tmp/" + assetFilename + ".png");
            std::system(command.c_str());
            // Get only the second layer, don't care about the rest
            assetPath = "/tmp/" + assetFilename + "-2" + ".png";
        }
        if (assetPath.ends_with(".png")) {
            const std::string command("convert " + assetPath + " /tmp/" + assetFilename + ".ppm");
            std::system(command.c_str());
            assetPath = "/tmp/" + assetFilename + ".ppm";
        }

        if (!assetPath.ends_with(".ppm"))
            return false;

        long width = std::stol(_parser.get("--width"));
        long height = std::stol(_parser.get("--height"));
        long margin = std::stol(_parser.get("--margin"));
        long lineHeight = std::stol(_parser.get("--line-height"));

        Convert convert(assetPath, width, height, margin, lineHeight);

        convert.exportAsPPM();
        return true;
    } catch (std::exception &e) {
        return false;
    }
    return true;
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
    _buildArgument(),
    _emuArgument(),
    _convArgument()
{
    _parser.add_subparser(_headerArgument.getParser());
    _parser.add_subparser(_buildArgument.getParser());
    _parser.add_subparser(_emuArgument.getParser());
    _parser.add_subparser(_convArgument.getParser());
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
    } else if (_parser.is_subcommand_used("emu")) {
        return _emuArgument.execute();
    } else if (_parser.is_subcommand_used("conv")) {
        return _convArgument.execute();
    }
    std::cerr << "No subcommand found" << std::endl;
    return false;
}
