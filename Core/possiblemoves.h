#include "objects.h"
#include "halfpos.h"
#include "position.h"
#include <set>
#include <iterator>
#include <experimental/generator>

class PossibleMoves2
{
    class Iterator
    {
        // from == HalfPos::heaven is end().
        int from{HalfPos::heaven}, pips{0};
        HalfPos pos{};
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = Move;
        using reference = Move&;
        using pointer = Move*;
        using iterator_category = std::input_iterator_tag;

        Iterator() noexcept = default;
        Iterator(HalfPos pos, int pips) noexcept : from(HalfPos::bar + 1), pips(pips), pos(std::move(pos)) { ++(*this); }

        [[nodiscard]] bool operator==(const Iterator& o) const noexcept { return from == o.from && (from == HalfPos::heaven || (pips == o.pips && pos == o.pos)); }
        [[nodiscard]] bool operator!=(const Iterator& o) const noexcept { return !(*this == o); }
        [[nodiscard]] Move operator*() const noexcept { return {from, std::max(from - pips, HalfPos::heaven)}; }
        Iterator& operator++() noexcept {
            if (from == HalfPos::bar || from == pips) {
                from = 0;
                return *this;
            }
            const bool moves_on_board = (from < HalfPos::bar) && (from > pips);
            while (--from > pips)
                if (pos[from])
                    return *this;
            if (pos.CanBearOff())
            {
                if (from == pips)
                    if (pos[pips])
                        return *this;
                if (not moves_on_board)
                    while (from > HalfPos::heaven) {
                        if (pos[from])
                            return *this;
                        from--;
                    }
            }
            from = 0;
            return *this;
        }
    };
public:
    int pips;
    HalfPos pos;

    PossibleMoves2(HalfPos pos, int pips) noexcept : pips(pips), pos(std::move(pos)) {}

    Iterator begin() const noexcept { return {pos, pips}; }
    Iterator cbegin() const noexcept { return {pos, pips}; }
    static Iterator end() noexcept { return {}; }
    static Iterator cend() noexcept { return {}; }
};

//[[nodiscard]]
//std::experimental::generator<Move> PossibleMoves(const HalfPos&, int pips);

[[nodiscard]]
inline PossibleMoves2 PossibleMoves(HalfPos pos, int pips)
{
    return {std::move(pos), pips};
}

[[nodiscard]]
std::experimental::generator<Move> PossibleMoves(const Position&, int pips);

template <class Pos>
[[nodiscard]]
std::experimental::generator<Ply> PossiblePlies(const Pos& pos1, const Dice& roll)
{
    if (roll.IsPair())
        for (const Move& m1 : PossibleMoves(pos1, roll.first))
        {
            auto pos2 = Play(pos1, m1);
            bool any2 = false;
            for (const Move& m2 : PossibleMoves(pos2, roll.first))
            {
                any2 = true;
                auto pos3 = Play(pos2, m2);
                bool any3 = false;
                for (const Move& m3 : PossibleMoves(pos3, roll.first))
                {
                    any3 = true;
                    auto pos4 = Play(pos3, m3);
                    bool any4 = false;
                    for (const Move& m4 : PossibleMoves(pos4, roll.first)) 
                    {
                        any4 = true;
                        co_yield Ply{m1,m2,m3,m4};
                    }
                    if (not any4)
                        co_yield Ply{m1,m2,m3};
                }
                if (not any3)
                    co_yield Ply{m1,m2};
            }
            if (not any2)
                co_yield Ply{m1};
        }
    else
        for (const auto& roll : {roll, Reverse(roll)})
            for (const Move& m1 : PossibleMoves(pos1, roll.first))
            {
                auto pos2 = Play(pos1, m1);
                bool any2 = false;
                for (const Move& m2 : PossibleMoves(pos2, roll.second))
                {
                    any2 = true;
                    co_yield {m1,m2};
                }
                if (not any2)
                    co_yield {m1};
            }
}

// template <class Pos>
// [[nodiscard]]
// std::vector<std::pair<Dice, Plies>> PossiblePlies(const Pos& pos)
// {
//     std::vector<std::pair<Dice, Plies>> ret;
//     for (const auto& roll : Dice::All())
//         ret.emplace_back(roll, PossiblePlies(pos, roll));
//     return ret;
// }

template <class Pos>
[[nodiscard]]
std::vector<std::pair<Pos, Ply>> UniqueNextPosAndPly(const Pos& pos, const Dice& roll)
{
    std::vector<std::pair<Pos, Ply>> ret;
    std::set<Pos> uniques;
    for (const auto& ply : PossiblePlies(pos, roll))
    {
        auto ins = uniques.insert(Play(pos, ply));
        if (ins.second /*was inserted*/)
            ret.emplace_back(*ins.first, ply);
    }
    return ret;
}

template <class Pos>
[[nodiscard]]
std::set<Pos> UniqueNextPositions(const Pos& pos, const Dice& roll)
{
    std::set<Pos> uniques;
    for (const auto& ply : PossiblePlies(pos, roll))
        uniques.insert(Play(pos, ply));
    return uniques;
}

template <class Pos>
[[nodiscard]]
std::vector<Ply> UniquePossiblePlies(const Pos& pos, const Dice& roll)
{
    std::vector<Ply> ret;
    std::set<Pos> uniques;
    for (const auto& ply : PossiblePlies(pos, roll))
    {
        auto ins = uniques.insert(Play(pos, ply));
        if (ins.second /*was inserted*/)
            ret.push_back(ply);
    }
    return ret;
}