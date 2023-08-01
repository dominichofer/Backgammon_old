#include "possiblemoves.h"

//std::experimental::generator<Move> PossibleMoves(const HalfPos& pos, int pips)
//{
//    assert(pips >= 1);
//    assert(pips <= 6);
//
//    // if there is a checker on the bar it has to be played
//    if (pos.Bar())
//    {
//        co_yield {HalfPos::bar, HalfPos::bar - pips};
//        co_return;
//    }
//
//    // all moves on the board
//    bool moves_on_board = false;
//    for (int from = HalfPos::bar - 1; from > pips; from--)
//        if (pos[from])
//        {
//            co_yield {from, from - pips};
//            moves_on_board = true;
//        }
//
//    if (pos.CanBearOff())
//        if (pos[pips])
//            co_yield {pips, HalfPos::heaven};
//        else if (not moves_on_board) // can overplay
//            for (int from = pips - 1; from > HalfPos::heaven; from--)
//                if (pos[from])
//                    co_yield {from, HalfPos::heaven};
//}

std::experimental::generator<Move> PossibleMoves(const Position& pos, int pips)
{
    assert(pips >= 1);
    assert(pips <= 6);

    // if there is a checker on the bar it has to be played
    if (pos.P_Bar())
    {
        int to = HalfPos::bar - pips;
        if (pos.O(to) < 2)
            co_yield {HalfPos::bar, to};
        co_return;
    }

    // all moves on the board
    bool moves_on_board = false;
    for (int from = pips + 1; from < HalfPos::bar; from++)
    {
        int to = from - pips;
        if (pos.P(from) && (pos.O(to) < 2))
        {
            co_yield { from, to };
            moves_on_board = true;
        }
    }

    if (pos.P_CanBearOff())
    {
        if (pos.P(pips))
            co_yield {pips, HalfPos::heaven};
        else if (not moves_on_board) // can overplay
            for (int i = pips - 1; i > HalfPos::heaven; i--)
                if (pos.P(i))
                    co_yield {i, HalfPos::heaven};
    }
}