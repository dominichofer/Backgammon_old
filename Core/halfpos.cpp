#include "halfpos.h"

int HalfPos::Pips() const noexcept
{
    int sum = 0;
    for (int i = 0; i < m.size(); i++)
        sum += m[i] * i;
    return sum;
}

std::size_t HalfPos::HighestChecker() const noexcept
{
    const auto rlast = m.rend() - 1;
    auto it = std::find_if(m.rbegin(), rlast, std::identity());
    return std::distance(it, rlast);
}

std::string to_string(const HalfPos& pos)
{
    std::string ret;
    for (auto field : pos)
        ret += std::to_string(field) + ' ';
    return ret;
}

HalfPos Play(HalfPos pos, const Move& move)
{
    pos.Play(move);
    return pos;
}

HalfPos Play(HalfPos pos, const Ply& ply)
{
    pos.Play(ply);
    return pos;
}



// std::vector<HalfPos> PossibleNextPos(const HalfPos& pos, int pips)
// {
//     auto pm = PossibleMoves(pos, pips);
//     if (pm.empty())
//         return { pos };
    
//     std::vector<HalfPos> ret;
//     ret.reserve(pm.size());
//     for (auto move : pm)
//         ret.push_back(Play(pos, move));
//     return ret;
// }

// [[nodiscard]]
// std::vector<HalfPos> PossibleNextPos(const HalfPos& pos, const Dice& roll)
// {
//     std::vector<HalfPos> ret;
//     if (roll.IsPair())
//         for (const HalfPos& next : PossibleNextPos(pos, roll.first))
//             for (const HalfPos& next : PossibleNextPos(next, roll.first))
//                 for (const HalfPos& next : PossibleNextPos(next, roll.first))
//                 {
//                     auto pm = PossibleNextPos(next, roll.first);
//                     ret.insert(ret.end(), pm.begin(), pm.end());
//                 }
//     else
//         for (const auto& r : {roll, Reverse(roll)})
//             for (const HalfPos& next : PossibleNextPos(pos, r.first))
//             {
//                 auto pm = PossibleNextPos(next, r.second);
//                 ret.insert(ret.end(), pm.begin(), pm.end());
//             }
//     return ret;
// }

// std::vector<std::pair<Dice, std::vector<HalfPos>>> PossibleNextPos(const HalfPos& pos)
// {
//     std::vector<std::pair<Dice, std::vector<HalfPos>>> ret;
//     for (const auto& roll : Dice::All())
//         ret.emplace_back(roll, PossibleNextPos(pos, roll));
//     return ret;
// }