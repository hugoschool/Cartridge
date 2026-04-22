#pragma once

#include <cstdint>

namespace Cartridge {
    // https://problemkaputt.de/gbatek.htm#gbacartridgeheader
    struct Header {
        // 000h    4     ROM Entry Point  (32bit ARM branch opcode, eg. "B rom_start")
        std::uint8_t rom[4];

        // 004h    156   Nintendo Logo    (compressed bitmap, required!)
        std::uint8_t nintendo[156];

        // 0A0h    12    Game Title       (uppercase ascii, max 12 characters)
        std::uint8_t gameTitle[12];

        // 0ACh    4     Game Code        (uppercase ascii, 4 characters)
        std::uint8_t gameCode[4];

        // 0B0h    2     Maker Code       (uppercase ascii, 2 characters)
        std::uint8_t makerCode[2];

        // 0B2h    1     Fixed value      (must be 96h, required!)
        std::uint8_t fixed;

        // 0B3h    1     Main unit code   (00h for current GBA models)
        std::uint8_t mainUnitCode;

        // 0B4h    1     Device type      (usually 00h) (bit7=DACS/debug related)
        std::uint8_t deviceType;

        // 0B5h    7     Reserved Area    (should be zero filled)
        std::uint8_t reserved_1[7];

        // 0BCh    1     Software version (usually 00h)
        std::uint8_t softwareVersion;

        // 0BDh    1     Complement check (header checksum, required!)
        std::uint8_t complementCheck;

        // 0BEh    2     Reserved Area    (should be zero filled)
        std::uint8_t reserved_2[2];
    };
}
