#pragma once
#include <array>
#include <string>
#include <vector>

struct Move
{
    int from{0}, to{0};
    [[nodiscard]] auto operator<=>(const Move&) const noexcept = default;
};

using Moves = std::vector<Move>;

class Ply
{
    std::array<Move, 4> m;
public:
    Ply(Move move1 = {}, Move move2 = {}, Move move3 = {}, Move move4 = {}) noexcept : m({move1, move2, move3, move4}) {}

    [[nodiscard]] auto operator<=>(const Ply&) const noexcept = default;
    [[nodiscard]] auto empty() const noexcept { return m.empty(); }

    [[nodiscard]] auto begin() noexcept { return m.begin(); }
    [[nodiscard]] auto begin() const noexcept { return m.begin(); }
    [[nodiscard]] auto cbegin() const noexcept { return m.cbegin(); }
    [[nodiscard]] auto rbegin() noexcept { return std::find(m.begin(), m.end(), Move{}); }
    [[nodiscard]] auto rbegin() const noexcept { return std::find(m.begin(), m.end(), Move{}); }
    [[nodiscard]] auto crbegin() const noexcept { return std::find(m.cbegin(), m.cend(), Move{}); }
    [[nodiscard]] auto end() noexcept { return std::find(m.begin(), m.end(), Move{}); }
    [[nodiscard]] auto end() const noexcept { return std::find(m.begin(), m.end(), Move{}); }
    [[nodiscard]] auto cend() const noexcept { return std::find(m.cbegin(), m.cend(), Move{}); }
    [[nodiscard]] auto rend() noexcept { return m.rend(); }
    [[nodiscard]] auto rend() const noexcept { return m.rend(); }
    [[nodiscard]] auto crend() const noexcept { return m.crend(); }
};

//using Ply = std::vector<Move>;
using Plies = std::vector<Ply>;

struct Dice
{
    int first, second;

    [[nodiscard]] static std::array<Dice, 21> All() noexcept;

    [[nodiscard]] bool IsPair() const noexcept { return first == second; }
};

[[nodiscard]] inline bool IsPair(const Dice& roll) noexcept { return roll.IsPair(); }
[[nodiscard]] inline Dice Reverse(const Dice& roll) noexcept { return { roll.second, roll.first }; }

[[nodiscard]] std::string to_string(const Dice&);
[[nodiscard]] std::string to_string(const Move&);
[[nodiscard]] std::string to_string(const Moves&);
[[nodiscard]] std::string to_string(const Ply&);
[[nodiscard]] std::string to_string(const Plies&);
// [[nodiscard]] std::string to_string(const std::vector<std::pair<Dice, Plies>>&);