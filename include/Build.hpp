#pragma once

#include <string>
namespace Cartridge {
    class Build {
        public:
            Build() = delete;
            Build(std::string path);
            ~Build();
            void build();
        private:
            std::string _path;
    };
}
