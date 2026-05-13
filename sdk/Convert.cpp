#include "Convert.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Cartridge::Convert::Convert(
    const std::string filePath,
    std::size_t width,
    std::size_t height,
    std::size_t margin,
    std::size_t lineHeight
) : _filePath(filePath), _width(width), _height(height), _margin(margin), _lineHeight(lineHeight),
    _characters()
{
    storeAllCharacters();
}

void Cartridge::Convert::storeAllCharacters()
{
    std::ifstream fileStream(_filePath);
    std::string token;

    std::getline(fileStream, token);

    std::getline(fileStream, token);
    std::stringstream ss(token);
    std::string ssToken;

    std::size_t ppmWidth;
    std::size_t ppmHeight;

    std::getline(ss, ssToken, ' ');
    std::stringstream(ssToken) >> ppmWidth;
    std::getline(ss, ssToken, ' ');
    std::stringstream(ssToken) >> ppmHeight;

    // Ignore 255 line
    std::getline(fileStream, token);

    std::getline(fileStream, token);

    std::vector<Color> pixels;

    for (std::size_t i = 0; i < token.length(); i += 3) {
        pixels.push_back({
            .r = static_cast<uint8_t>(token[i + 0]),
            .g = static_cast<uint8_t>(token[i + 1]),
            .b = static_cast<uint8_t>(token[i + 2]),
        });
    }

    // X & Y are refered in rows / cols
    for (std::size_t fontStartY = _margin; fontStartY < ppmHeight; fontStartY += _height + _margin) {
        for (std::size_t fontStartX = _margin; fontStartX < ppmWidth; fontStartX += _width + _margin) {
            std::vector<Color> chars;

            for (std::size_t y = 0; y < _height; y++) {
                for (std::size_t x = 0; x < _width; x++) {
                    chars.push_back(pixels.at(ppmWidth * (fontStartY + y) + (fontStartX + x)));
                }
            }

            _characters.push_back(chars);
        }
    }
}

void Cartridge::Convert::exportAsPPM()
{
    std::size_t i = 0;
    std::string path = std::filesystem::path(_filePath).remove_filename();

    for (auto &vec : _characters) {
        std::string fileName = path + "/font_" + std::to_string(i) + ".ppm";
        std::ofstream stream(fileName);
        stream << "P3" << std::endl;
        stream << _width << " " << _height << std::endl;
        stream << "255" << std::endl;

        for (auto &color : vec) {
            stream  << static_cast<int>(color.r) << " "
                    << static_cast<int>(color.g) << " "
                    << static_cast<int>(color.b) << std::endl;
        }
        i++;
    }
}

std::ostream& operator<<(std::ostream& os, const Cartridge::Color& obj)
{
    os << "r: " << obj.r << ", g: " << obj.g << ", b: " << obj.b;
    return os;
}
