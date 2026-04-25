#include "Header.hpp"
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>

void Cartridge::Header::readFromFile(std::string fileName)
{
    std::ifstream fs(fileName, std::ios_base::binary);

    if (!fs.is_open()) {
        std::cerr << "Couldn't open " << fileName << std::endl;
        return;
    }
    fs.read((char *)&_content, sizeof(Cartridge::HeaderContent));
}

std::uint8_t Cartridge::Header::calculateComplementCheck() const
{
    std::uint8_t complementCheck = 0;

    for (std::uint8_t i = 0xA0; i <= 0xBC; i++) {
        const std::uint8_t *byte = &_content.rom[i];
        complementCheck -= *byte;
    }
    complementCheck -= 0x19;
    complementCheck &= 0xFF;
    return complementCheck;
}

std::uint32_t Cartridge::Header::littleToBigEndian(std::uint32_t little) const
{
    std::uint32_t bits[4];

    bits[0] = (little & 0x000000ff) << 24;
    bits[1] = (little & 0x0000ff00) << 8;
    bits[2] = (little & 0x00ff0000) >> 8;
    bits[3] = (little & 0xff000000) >> 24;
    return bits[0] | bits[1] | bits[2] | bits[3];
}

std::uint32_t Cartridge::Header::getFullRom(std::uint8_t rom[HeaderValues::romBytes]) const
{
    std::uint32_t fullRom = 0;

    std::size_t i = 0;
    for (; i < HeaderValues::romBytes - 1; i++) {
        fullRom += rom[i];
        fullRom = fullRom << 8;
    }
    fullRom += rom[i];
    fullRom = littleToBigEndian(fullRom);
    return fullRom;
}

bool Cartridge::Header::verifyNintendoLogo(std::uint8_t nintendo[HeaderValues::nintendoBytes]) const
{
    bool nintendoLogo = true;

    for (std::size_t i = 0; i < HeaderValues::nintendoBytes; i++) {
        if (nintendo[i] != HeaderValues::nintendoHeader[i]) {
            nintendoLogo = false;
            break;
        }
    }
    return nintendoLogo;
}

bool Cartridge::Header::verifyEmptyArea(std::uint8_t *reserved, std::size_t size) const
{
    bool verified = true;

    for (std::size_t i = 0; i < size; i++) {
        if (reserved[i] != 0x00) {
            verified = false;
            break;
        }
    }
    return verified;
}

bool Cartridge::Header::verify(bool print)
{
    if (print == false)
        std::cout.rdbuf(std::ifstream("/dev/null").rdbuf());

    std::cout << "ROM: 0x" << std::hex << getFullRom(_content.rom) << std::endl;

    const bool nintendoLogo = verifyNintendoLogo(_content.nintendo);
    std::cout << "Nintendo Logo: " << std::boolalpha << nintendoLogo << std::endl;
    if (!nintendoLogo)
        return false;

    std::cout << "Game title: " << RestrictedString(HeaderValues::gameTitleBytes, _content.gameTitle).getString() << std::endl;
    std::cout << "Game code: " << RestrictedString(HeaderValues::gameCodeBytes, _content.gameCode).getString() << std::endl;
    std::cout << "Maker code: " << RestrictedString(HeaderValues::makerCodeBytes, _content.makerCode).getString() << std::endl;

    const bool fixedValue = _content.fixed == HeaderValues::fixedValue;
    std::cout << "Fixed value: " << std::boolalpha << fixedValue << std::endl;
    std::cout << "Main unit code: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(_content.mainUnitCode) << std::endl;
    std::cout << "Device type: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(_content.deviceType) << std::endl;

    if (!fixedValue)
        return false;

    const bool empty1 = verifyEmptyArea(_content.reserved_1, HeaderValues::reserved_1_bytes);
    std::cout << "Reserved 1: " << std::boolalpha << empty1 << std::endl;

    if (!empty1)
        return false;

    std::cout << "Software version number: " << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(_content.softwareVersion) << std::endl;

    const std::uint8_t ownComplementCheck = calculateComplementCheck();
    const bool complementCheck = _content.complementCheck == ownComplementCheck;

    std::cout << "Complement check: " << std::boolalpha << complementCheck << std::endl;
    std::cout << std::setfill(' ') << std::setw(8) << " " << "Given: " << "0x" << std::hex << static_cast<int>(_content.complementCheck) << std::endl;
    std::cout << std::setfill(' ') << std::setw(8) << " " << "Calculated: " << "0x" << std::hex << static_cast<int>(ownComplementCheck) << std::endl;

    if (!complementCheck)
        return false;

    const bool empty2 = verifyEmptyArea(_content.reserved_2, HeaderValues::reserved_2_bytes);
    std::cout << "Reserved 2: " << std::boolalpha << empty1 << std::endl;
    return empty2;
}

Cartridge::Header::RestrictedString::RestrictedString(std::size_t size, std::uint8_t bytes[]) : _size(size)
{
    _string.reserve(_size);

    for (std::size_t i = 0; i < _size; i++) {
        _string += static_cast<char>(bytes[i]);
    }
}

std::string &Cartridge::Header::RestrictedString::getString()
{
    return _string;
}
