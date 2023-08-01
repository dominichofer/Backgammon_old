#include "objects.h"
#include "algorithm.h"

std::string to_string(const Dice& roll)
{
    return std::to_string(roll.first) + '-' + std::to_string(roll.second);
}

std::string to_string(const Move& move)
{
    return std::to_string(move.from) + '/' + std::to_string(move.to);
}

std::string to_string(const Moves& moves)
{
    return join(" ", moves);
}

std::string to_string(const Ply& moves)
{
    return join(" ", moves);
}

std::string to_string(const Plies& plies)
{
    return join(", ", plies);
}

// std::string to_string(const std::vector<std::pair<Dice, Plies>>& pairs)
// {
//     std::string ret;
//     for (const auto& pair : pairs)
//         ret += to_string(pair.first) + ": " + join(", ", pair.second) + '\n';
//     return ret;
// }


std::array<Dice, 21> Dice::All() noexcept
{
    return {
        Dice{1,1}, Dice{1,2}, Dice{1,3}, Dice{1,4}, Dice{1,5}, Dice{1,6},
        Dice{2,2}, Dice{2,3}, Dice{2,4}, Dice{2,5}, Dice{2,6},
        Dice{3,3}, Dice{3,4}, Dice{3,5}, Dice{3,6},
        Dice{4,4}, Dice{4,5}, Dice{4,6},
        Dice{5,5}, Dice{5,6},
        Dice{6,6}
    };
}