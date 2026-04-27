#pragma once

#include "argparse.hpp"

namespace Cartridge {
    class IArgument {
        public:
            virtual ~IArgument() = default;

            virtual bool execute() = 0;
            virtual argparse::ArgumentParser &getParser() = 0;
    };

    class AArgument : public IArgument {
        public:
            AArgument(const std::string name, argparse::default_arguments args = argparse::default_arguments::none);
            ~AArgument() = default;

            argparse::ArgumentParser &getParser() override;

        protected:
            argparse::ArgumentParser _parser;
    };

    class HeaderArgument : public AArgument {
        public:
            HeaderArgument();
            ~HeaderArgument() = default;

            bool execute() override;

            argparse::ArgumentParser _checkSubcommand;
            argparse::ArgumentParser _generateSubcommand;
            argparse::ArgumentParser _dumpSubcommand;
    };

    class BuildArgument : public AArgument {
        public:
            BuildArgument();
            ~BuildArgument();

            bool execute() override;
    };

    class Arguments : public AArgument {
        public:
            Arguments();
            ~Arguments() = default;

            void parse(int &argc, char **argv);
            bool execute() override;

        private:
            Cartridge::HeaderArgument _headerArgument;
            Cartridge::BuildArgument _buildArgument;
    };
}
