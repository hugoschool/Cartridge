#pragma once

#include "argparse.hpp"

namespace Cartridge {
    class IArgument {
        public:
            virtual ~IArgument() = default;

            virtual bool execute() = 0;
    };

    class HeaderArgument : public IArgument {
        public:
            HeaderArgument();
            ~HeaderArgument() = default;

            bool execute() override;

            argparse::ArgumentParser _parser;
            argparse::ArgumentParser _checkSubcommand;
            argparse::ArgumentParser _generateSubcommand;
    };

    class Arguments : public IArgument {
        public:
            Arguments();
            ~Arguments() = default;

            void parse(int &argc, char **argv);
            bool execute() override;

        private:
            argparse::ArgumentParser _globalParser;

            // Could be simplified, map of command and IArgument
            Cartridge::HeaderArgument _headerArgument;
    };
}
