#include "position.h"

void Position::Play(const Move& move)
{
    assert(O(move.to) < 2);
    p.Play(move);
    o.Hit(HalfPos::bar - move.to);
}

Position Play(Position pos, const Move& move)
{
    pos.Play(move);
    return pos;
}

Position Play(Position pos, const Ply& ply)
{
    pos.Play(ply);
    return pos;
}

Position PlayPass(Position pos)
{
    pos.SwitchPlayers();
    return pos;
}

[[nodiscard]]
char Hex(int i)
{
    switch (i)
    {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
    default: throw;
    }
}

std::string to_string(const Position& pos)
{
    std::string board = 
        "+-+-+-+-+-+-+---+-+-+-+-+-+-+\n"
        "|Y|Y|Y|Y|Y|Y|   |Y|Y|Y|Y|Y|Y|\n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| \n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| Pips: N\n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| \n"
        "|Y|Y|Y|Y|Y|Y|   |Y|Y|Y|Y|Y|Y|\n"
        "|-|-|-|-|-|-|~-~|-|-|-|-|-|-|\n"
        "|Y|Y|Y|Y|Y|Y|   |Y|Y|Y|Y|Y|Y|\n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| \n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| Pips: M\n"
        "|Y|Y|Y|Y|Y|Y| ? |Y|Y|Y|Y|Y|Y| \n"
        "|Y|Y|Y|Y|Y|Y|   |Y|Y|Y|Y|Y|Y|\n"
        "+-+-+-+-+-+-+---+-+-+-+-+-+-+\n";

    // Fill the points
    for (int num = 1; num <= 5; num++)
    {
        // Upper half
        for (int i = 13; i < 25; i++)
        {
            auto it = std::find(board.begin(), board.end(), 'Y');
            if (num == 5 && pos.P(i) + pos.O(i) > 5)
                *it = Hex(pos.P(i) + pos.O(i));
            else if (pos.P(i) >= num)
                *it = 'X';
            else if (pos.O(i) >= num)
                *it = 'O';
            else
                *it = ' ';
        }

        // Lower half
        for (int i = 1; i < 13; i++)
        {
            auto it = std::find(board.rbegin(), board.rend(), 'Y');
            if (num == 5 && pos.P(i) + pos.O(i) > 5)
                *it = Hex(pos.P(i) + pos.O(i));
            else if (pos.P(i) >= num)
                *it = 'X';
            else if (pos.O(i) >= num)
                *it = 'O';
            else
                *it = ' ';
        }
    }

    // Fill upper bar
    for (int num = 1; num <= 3; num++)
    {
        auto it = std::find(board.begin(), board.end(), '?');
        if (num == 2 && pos.O_Bar() > 3)
            *it = Hex(pos.O_Bar());
        else if (pos.O_Bar() >= num)
            *it = 'O';
        else
            *it = ' ';
    }

    // Fill lower bar
    for (int num = 1; num <= 3; num++)
    {
        auto it = std::find(board.rbegin(), board.rend(), '?');
        if (num == 2 && pos.P_Bar() > 3)
            *it = Hex(pos.P_Bar());
        else if (pos.P_Bar() >= num)
            *it = 'X';
        else
            *it = ' ';
    }

    // Fill in player's pip
    board.replace(board.find('N'), 1, std::to_string(pos.P_Pips()));

    // Fill in opponent's pip
    board.replace(board.find('M'), 1, std::to_string(pos.O_Pips()));

    return board;
}

// std::vector<Position> PossibleNextPos(const Position& pos, int pips)
// {
//     auto pm = PossibleMoves(pos, pips);
//     if (pm.empty())
//         return { pos };
    
//     std::vector<Position> ret;
//     ret.reserve(pm.size());
//     for (auto move : pm)
//         ret.push_back(Play(pos, move));
//     return ret;
// }

// std::vector<Position> PossibleNextPos(const Position& pos, const Dice& roll)
// {
//     std::vector<Position> ret;
//     if (roll.IsPair())
//         for (const Position& next : PossibleNextPos(pos, roll.first))
//             for (const Position& next : PossibleNextPos(next, roll.first))
//                 for (const Position& next : PossibleNextPos(next, roll.first))
//                 {
//                     auto pm = PossibleNextPos(next, roll.first);
//                     ret.insert(ret.end(), pm.begin(), pm.end());
//                 }
//     else
//         for (const auto& r : {roll, Reverse(roll)})
//             for (const Position& next : PossibleNextPos(pos, r.first))
//             {
//                 auto pm = PossibleNextPos(next, r.second);
//                 ret.insert(ret.end(), pm.begin(), pm.end());
//             }
//     return ret;
// }

// std::vector<std::pair<Dice, std::vector<Position>>> PossibleNextPos(const Position& pos)
// {
//     std::vector<std::pair<Dice, std::vector<Position>>> ret;
//     for (const auto& roll : Dice::All())
//         ret.emplace_back(roll, PossibleNextPos(pos, roll));
//     return ret;
// }
