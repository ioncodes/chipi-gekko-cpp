#pragma once

#include <compare>
#include <cstdint>
#include <format>

struct Gpr {
    std::uint8_t value;

    Gpr() = default;
    constexpr Gpr(std::uint8_t v) : value(v) {}
    explicit operator std::uint8_t() const { return value; }
    bool operator==(const Gpr&) const = default;
    bool operator==(int other) const { return value == other; }
    bool operator<(int other) const { return value < other; }
};

struct Fpr {
    std::uint8_t value;

    Fpr() = default;
    constexpr Fpr(std::uint8_t v) : value(v) {}
    explicit operator std::uint8_t() const { return value; }
};

template <> struct std::formatter<Gpr> : std::formatter<std::string> {
    auto format(Gpr g, auto& ctx) const {
        return std::formatter<std::string>::format(
            std::format("r{}", g.value), ctx);
    }
};

template <> struct std::formatter<Fpr> : std::formatter<std::string> {
    auto format(Fpr f, auto& ctx) const {
        return std::formatter<std::string>::format(
            std::format("f{}", f.value), ctx);
    }
};
