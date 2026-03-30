#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>

#include "gekko.hpp"

static constexpr std::size_t INSTRUCTION_SIZE = 4;

int main(int argc, char* argv[]) {
    const std::string_view path{argv[1]};
    std::ifstream file{path.data(), std::ios::binary};
    const std::vector<std::uint8_t> buffer(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    std::size_t offset = 0x100;
    while (offset + INSTRUCTION_SIZE <= buffer.size()) {
        auto result = gekko::decode(buffer.data() + offset, buffer.size() - offset);
        if (result) {
            std::cout << std::format("{:08x}  {}\n", offset, gekko::format(*result));
            offset += result->size;
        } else {
            std::cout << std::format("{:08x}  ???\n", offset);
            offset += INSTRUCTION_SIZE;
        }
    }

    return 0;
}
