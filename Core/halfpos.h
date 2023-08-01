#pragma once
#include "algorithm.h"
#include "objects.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <numeric>
#include <string>

class HalfPos
{
    std::array<uint8_t, 26> m{0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}; // play direction: <--
public:
    static constexpr int heaven = 0;
    static constexpr int bar = 25;

    constexpr HalfPos() noexcept = default;
    explicit constexpr HalfPos(std::array<uint8_t, 26> m) noexcept : m(std::move(m)) {}

    [[nodiscard]] static constexpr HalfPos Start() noexcept { return HalfPos({0, 0,0,0,0,0,5, 0,3,0,0,0,0 ,5,0,0,0,0,0 ,0,0,0,0,0,2, 0}); }

    void Play(const Move& move) noexcept { m[move.from]--; m[move.to]++; }
    void Play(const Ply& ply) noexcept { for (const auto& move : ply) Play(move); }
    void Hit(std::size_t index) noexcept { assert(m[index] < 2); m[bar] += m[index]; m[index] = 0; }

    [[nodiscard]] int Checkers() const noexcept { return std::accumulate(m.begin() + 1, m.end(), 0); }
    [[nodiscard]] int Pips() const noexcept;
    [[nodiscard]] bool CanBearOff() const noexcept { return std::none_of(m.begin() + 7, m.end(), std::identity()); }
    [[nodiscard]] bool IsGameOver() const noexcept { return std::none_of(m.begin() + 1, m.end(), std::identity()); }
    [[nodiscard]] std::size_t HighestChecker() const noexcept;

    [[nodiscard]] auto begin() noexcept { return m.begin(); }
    [[nodiscard]] auto end() noexcept { return m.end(); }
    [[nodiscard]] auto begin() const noexcept { return m.begin(); }
    [[nodiscard]] auto end() const noexcept { return m.end(); }
    [[nodiscard]] auto cbegin() const noexcept { return m.cbegin(); }
    [[nodiscard]] auto cend() const noexcept { return m.cend(); }
    [[nodiscard]] auto rbegin() noexcept { return m.rbegin(); }
    [[nodiscard]] auto rend() noexcept { return m.rend(); }
    [[nodiscard]] auto rbegin() const noexcept { return m.rbegin(); }
    [[nodiscard]] auto rend() const noexcept { return m.rend(); }
    [[nodiscard]] auto crbegin() const noexcept { return m.crbegin(); }
    [[nodiscard]] auto crend() const noexcept { return m.crend(); }

    [[nodiscard]] bool operator==(const HalfPos& o) const noexcept { return std::equal(m.begin() + 1, m.end(), o.m.begin() + 1); }
    [[nodiscard]] bool operator!=(const HalfPos& o) const noexcept { return !(*this == o); }
    [[nodiscard]] bool operator<(const HalfPos& o) const noexcept { return m < o.m; }
    [[nodiscard]] bool operator>(const HalfPos& o) const noexcept { return m > o.m; }
    [[nodiscard]] bool operator<=(const HalfPos& o) const noexcept { return m <= o.m; }
    [[nodiscard]] bool operator>=(const HalfPos& o) const noexcept { return m >= o.m; }

    [[nodiscard]]       uint8_t& operator[](std::size_t index)       noexcept { return m[index]; }
    [[nodiscard]] const uint8_t& operator[](std::size_t index) const noexcept { return m[index]; }
    [[nodiscard]]       uint8_t& Bar()       noexcept { return m.back(); }
    [[nodiscard]] const uint8_t& Bar() const noexcept { return m.back(); }

    [[nodiscard]] std::size_t hash() const {
        return std::hash<uint64_t>()(
            static_cast<uint64_t>(m[1]) + (static_cast<uint64_t>(m[2]) << 4) +
            (static_cast<uint64_t>(m[3]) << 8) + (static_cast<uint64_t>(m[4]) << 12) +
            (static_cast<uint64_t>(m[5]) << 16) + (static_cast<uint64_t>(m[6]) << 20) +
            (static_cast<uint64_t>(m[7]) << 24) + (static_cast<uint64_t>(m[8]) << 28) +
            (static_cast<uint64_t>(m[9]) << 32) + (static_cast<uint64_t>(m[10]) << 36) +
            (static_cast<uint64_t>(m[11]) << 40) + (static_cast<uint64_t>(m[12]) << 44) +
            (static_cast<uint64_t>(m[13]) << 48) + (static_cast<uint64_t>(m[14]) << 52) +
            (static_cast<uint64_t>(m[15]) << 56) + (static_cast<uint64_t>(m[16]) << 60));
    }
};

template <>
struct std::hash<HalfPos>
{
    [[nodiscard]] std::size_t operator()(const HalfPos& pos) const { return pos.hash(); }
};

[[nodiscard]]
std::string to_string(const HalfPos&);

[[nodiscard]]
HalfPos Play(HalfPos, const Move&);

[[nodiscard]]
HalfPos Play(HalfPos, const Ply&);


// [[nodiscard]]
// std::vector<HalfPos> PossibleNextPos(const HalfPos&, int pips);

// [[nodiscard]]
// std::vector<HalfPos> PossibleNextPos(const HalfPos&, const Dice&);

// std::vector<std::pair<Dice, std::vector<HalfPos>>> PossibleNextPos(const HalfPos&);


class HalfPosGenerator
{
    class Iterator
    {
        const int num_fields = 0;
        std::vector<HalfPos> stack{};
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = HalfPos;
        using reference = HalfPos&;
        using pointer = HalfPos*;
        using iterator_category = std::input_iterator_tag;

        Iterator() noexcept = default;
        Iterator(int num_fields) : num_fields(num_fields)
        {
            while (stack.size() < num_fields)
                stack.push_back(HalfPos());
        }

        [[nodiscard]] bool operator==(const Iterator& o) const noexcept
        {
            return stack.size() == o.stack.size()
                && std::equal(stack.begin(), stack.end(), o.stack.begin());
        }
        [[nodiscard]] bool operator!=(const Iterator& o) const noexcept { return !(*this == o); }

        Iterator& operator++()
        {
            stack.back()[stack.size()]++;
            while (!stack.empty())
            {
                if (stack.back().Checkers() <= 15)
                {
                    if (stack.size() == num_fields)
                        break;
                    else
                        stack.push_back(stack.back());
                }
                else
                {
                    stack.pop_back();
                    if (stack.empty())
                        break;
                    stack.back()[stack.size()]++;
                }
            }            
            return *this;
        }
        [[nodiscard]]       HalfPos& operator*()       { return stack.back(); }
        [[nodiscard]] const HalfPos& operator*() const { return stack.back(); }
    };

    const int num_fields;
public:
    HalfPosGenerator(int num_fields) noexcept : num_fields(num_fields) {}

    [[nodiscard]] Iterator begin() const { return {num_fields}; }
    [[nodiscard]] Iterator cbegin() const { return {num_fields}; }
    [[nodiscard]] static Iterator end() { return {}; }
    [[nodiscard]] static Iterator cend() { return {}; }
};