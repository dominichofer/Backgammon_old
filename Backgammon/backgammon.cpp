#include "../Core/algorithm.h"
#include "../Core/objects.h"
#include "../Core/prob_dist.h"
#include "../Core/halfpos.h"
#include "../Core/position.h"
#include "../Core/possiblemoves.h"
#include "../Core/endgame.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <numeric>
#include <vector>
#include <iterator>


// Generates all possible HalfPos' where only the last given number of fields contain checkers.
// Will generate 'MultisetNumber(15, num_fields+1)' positions.
template <typename OutputIt>
void generate_all(OutputIt it, const int num_fields, HalfPos pos = {}, const int field_to_fill = 1)
{
    while (pos.Checkers() <= 15)
    {
        if (field_to_fill == num_fields)
            *it++ = pos;
        else
            generate_all(it, num_fields, pos, field_to_fill + 1);
        pos[field_to_fill]++;
    }
}

uint64_t foo(int remaining_white, int remaining_black, int field = 1)
{
    static std::map<std::tuple<int,int,int>,uint64_t> cache;
    if (remaining_white == 0 && remaining_black == 0)
        return 1;
    if (field == 24)
        return 1;
    auto it = cache.find(std::make_tuple(remaining_white, remaining_black, field));
    if (it != cache.end())
        return it->second;
    
    uint64_t sum = 0;
    for (int w = 0; w <= remaining_white; w++)
        sum += foo(remaining_white - w, remaining_black, field + 1);
    for (int b = 0; b <= remaining_black; b++)
        sum += foo(remaining_white, remaining_black - b, field + 1);
    cache[std::make_tuple(remaining_white, remaining_black, field)] = sum;
    return sum;
}

double foo()
{
    double sum = 0;
    for (int w1 = 0; w1 <= 15; w1++)
        for (int w2 = 0; w1 + w2 <= 15; w2++)
            for (int b1 = 0; b1 <= 15; b1++)
                for (int b2 = 0; b1 + b2 <= 15; b2++)
                    sum += foo(15 - w1 - w2, 15 - b1 - b2);
    return sum;
}

//std::unordered_map<Position, uint64_t> tt;
//
//uint64_t perft(int n, const Position& pos = Position::Start())
//{
//    if (n == 1)
//    {
//        uint64_t sum = 0;
//        for (const auto& roll : Dice::All())
//            sum += UniqueNextPositions(pos, roll).size();
//        return sum;
//    }
//
//    if (n > 2)
//    {
//        #pragma omp critical
//        {
//            if (tt.contains(pos))
//                return tt[pos];
//        }
//    }
//
//    uint64_t sum = 0;
//    #pragma omp parallel for reduction(+:sum)
//    for (int i = 0; i < 21; i++)
//    {
//        const auto& roll = Dice::All()[i];
//        for (const auto& next : UniqueNextPositions(pos, roll))
//            sum += perft(n - 1, next);
//    }
//
//    if (n > 2)
//    {
//        #pragma omp critical
//        tt[pos] = sum;
//    }
//    return sum;
//}

int main()
{
    std::chrono::high_resolution_clock::time_point start, stop;

    start = std::chrono::high_resolution_clock::now();
    FillMap();
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;
     
    //for (int i = 1; i < 10; i++)
    //{
    //    tt.clear();
    //    start = std::chrono::high_resolution_clock::now();
    //    auto result = perft(i);
    //    stop = std::chrono::high_resolution_clock::now();
    //    std::cout << result << std::endl;
    //    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;
    //}

    //auto pos = HalfPos::Start();
    //std::cout << to_string(pos) << std::endl;
    //std::vector<std::vector<std::pair<Position, Ply>>> tmp;
    //start = std::chrono::high_resolution_clock::now();
    //for (const auto& roll : Dice::All())
    //for (const Move& move : PossibleMoves(pos, 1))
    //    std::cout << to_string(move) << std::endl;
    //for (const Move& move : PossibleMoves(pos, 1))
    //    std::cout << to_string(move) << std::endl;
    //stop = std::chrono::high_resolution_clock::now();
    //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << std::endl;
    // std::cout << to_string(roll) << ": " << to_string(UniquePossiblePlies(pos, roll)) << std::endl;

    // pos.Play({8,7});
    // pos.Play({8,6});
    // pos.Play({24,18});
    // pos.Play({24,18});
    // std::cout << to_string(pos) << std::endl;
    // pos.SwitchPlayers();
    // std::cout << to_string(pos) << std::endl;
    // pos.Play({24,18});
    // pos.Play({18,17});
    // pos.Play({8,5});
    // pos.Play({8,5});
    // pos.Play({8,1});
    // pos.Play({6,4});
    // pos.Play({6,4});
    // pos.Play({6,1});
    // pos.Play({13,3});
    // pos.Play({13,3});
    // pos.Play({13,2});
    // pos.Play({13,2});
    // std::cout << to_string(pos) << std::endl;
    // pos.SwitchPlayers();
    // std::cout << to_string(pos) << std::endl;

    // std::chrono::system_clock::time_point start, stop;

    // start = std::chrono::high_resolution_clock::now();
    // auto result = foo();
    // stop = std::chrono::high_resolution_clock::now();
    // std::cout << result << std::endl;
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;


    // start = std::chrono::high_resolution_clock::now();
    // auto map = BearingOffMap(all_pos);
    // stop = std::chrono::high_resolution_clock::now();
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << std::endl;
    // std::cout << to_string(all_pos.back()) << std::endl;
    // std::cout << to_string(map.at(all_pos.back())) << std::endl;

    // for (const auto& it : map)
    //     std::cout << to_string(it.first) + '\n' + to_string(ProbDist{{1}});

    // MultisetNumber(15,  1) =              1
    // MultisetNumber(15,  2) =             16
    // MultisetNumber(15,  3) =            136
    // MultisetNumber(15,  4) =            816
    // MultisetNumber(15,  5) =          3'876
    // MultisetNumber(15,  6) =         15'504
    // MultisetNumber(15,  7) =         54'264
    // MultisetNumber(15,  8) =        170'544
    // MultisetNumber(15,  9) =        490'314
    // MultisetNumber(15, 10) =      1'307'504
    // MultisetNumber(15, 11) =      3'268'760
    // MultisetNumber(15, 12) =      7'726'160
    // MultisetNumber(15, 13) =     17'383'860
    // MultisetNumber(15, 14) =     37'442'160
    // MultisetNumber(15, 15) =     77'558'760
    // MultisetNumber(15, 16) =    155'117'520
    // MultisetNumber(15, 17) =    300'540'195
    // MultisetNumber(15, 18) =    565'722'720
    // MultisetNumber(15, 19) =  1'037'158'320
    // MultisetNumber(15, 20) =  1'855'967'520
    // MultisetNumber(15, 21) =  3'247'943'160
    // MultisetNumber(15, 22) =  5'567'902'560
    // MultisetNumber(15, 23) =  9'364'199'760
    // MultisetNumber(15, 24) = 15'471'286'560
    // MultisetNumber(15, 25) = 25'140'840'660
    // MultisetNumber(15, 26) = 40'225'345'056
    // Number of backgammon game-states: 4.7e+21
}