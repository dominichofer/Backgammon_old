#pragma once
#include "halfpos.h"

class Position
{
    HalfPos p{}, o{};
public:
    Position() noexcept = default;
    static constexpr Position Start() noexcept { return {HalfPos::Start(), HalfPos::Start()}; }
    constexpr Position(HalfPos p, HalfPos o) noexcept : p(std::move(p)), o(std::move(o)) {}

    [[nodiscard]] bool operator==(const Position& other) const noexcept { return std::tie(p, o) == std::tie(other.p, other.o); }
    [[nodiscard]] bool operator!=(const Position& other) const noexcept { return std::tie(p, o) != std::tie(other.p, other.o); }
    [[nodiscard]] bool operator<(const Position& other) const noexcept { return std::tie(p, o) < std::tie(other.p, other.o); }
    [[nodiscard]] bool operator>(const Position& other) const noexcept { return std::tie(p, o) > std::tie(other.p, other.o); }
    [[nodiscard]] bool operator<=(const Position& other) const noexcept { return std::tie(p, o) <= std::tie(other.p, other.o); }
    [[nodiscard]] bool operator>=(const Position& other) const noexcept { return std::tie(p, o) >= std::tie(other.p, other.o); }

    [[nodiscard]] const HalfPos& P() const noexcept { return p; }
    [[nodiscard]] const HalfPos& O() const noexcept { return o; }
    [[nodiscard]] const uint8_t& P(std::size_t index) const noexcept { return p[index]; }
    [[nodiscard]] const uint8_t& O(std::size_t index) const noexcept { return o[HalfPos::bar - index]; }
    [[nodiscard]] const uint8_t& P_Bar() const noexcept { return p.Bar(); }
    [[nodiscard]] const uint8_t& O_Bar() const noexcept { return o.Bar(); }
    [[nodiscard]] int P_Checkers() const noexcept { return p.Checkers(); }
    [[nodiscard]] int O_Checkers() const noexcept { return o.Checkers(); }
    [[nodiscard]] int P_Pips() const noexcept { return p.Pips(); }
    [[nodiscard]] int O_Pips() const noexcept { return o.Pips(); }
    [[nodiscard]] bool P_CanBearOff() const noexcept { return p.CanBearOff(); }
    [[nodiscard]] bool O_CanBearOff() const noexcept { return o.CanBearOff(); }
    [[nodiscard]] bool P_IsGameOver() const noexcept { return p.IsGameOver(); }
    [[nodiscard]] bool O_IsGameOver() const noexcept { return o.IsGameOver(); }

    [[nodiscard]] bool IsGameOver() const noexcept { return p.IsGameOver() or o.IsGameOver(); }
    [[nodiscard]] bool IsEndgame() const noexcept { return p.HighestChecker() < HalfPos::bar - o.HighestChecker(); }

    void SwitchPlayers() noexcept { std::swap(p, o); }
    void Play(const Move&);
    void Play(const Ply& ply) { for (const auto& move : ply) Play(move); }
};

template <>
struct std::hash<Position>
{
    [[nodiscard]] std::size_t operator()(const Position& pos) const { return pos.P().hash() * 37 + pos.O().hash(); }
};

[[nodiscard]]
Position Play(Position, const Move&);

[[nodiscard]]
Position Play(Position, const Ply&);

[[nodiscard]]
Position PlayPass(Position);

[[nodiscard]]
std::string to_string(const Position&);

// [[nodiscard]]
// std::vector<Position> PossibleNextPos(const Position&, int pips);

// [[nodiscard]]
// std::vector<Position> PossibleNextPos(const Position&, const Dice&);

// [[nodiscard]]
// std::vector<std::pair<Dice, std::vector<Position>>> PossibleNextPos(const Position&);