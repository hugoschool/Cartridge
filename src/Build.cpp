#include "Build.hpp"
#include <cstdlib>
#include <filesystem>

Cartridge::Build::Build(std::string path) : _path(path)
{
    std::filesystem::current_path("./" + path);
}

Cartridge::Build::~Build()
{}

void Cartridge::Build::build()
{
    std::system("make");
}
