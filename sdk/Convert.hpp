#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Cartridge {
    struct Color {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
    };
    class Convert {
        public:
            Convert() = delete;
            Convert(const std::string filePath, std::size_t width, std::size_t height, std::size_t margin, std::size_t lineHeight);
            ~Convert() = default;

            void exportAsPPM();
            void exportAsCMonospaced(std::string);

        private:
            const std::string _filePath;
            std::size_t _width;
            std::size_t _height;
            std::size_t _margin;
            std::size_t _lineHeight;

            std::vector<std::vector<Color>> _characters;

            void storeAllCharacters();
    };
}

std::ostream& operator<<(std::ostream& os, const Cartridge::Color& obj);
