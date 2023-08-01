#include "position.h"
#include "possiblemoves.h"
#include "endgame.h"
#include <cassert>
#include <iterator>
#include <limits>
#include <iostream>

// Generates all possible HalfPos' where only the last given number of fields contain checkers.
// Generates 'MultisetNumber(15, num_fields+1)' positions.
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


void FillMap()
{
    const int num_fields = 12;

    std::vector<HalfPos> all_pos;
    all_pos.reserve(MultisetNumber(15, num_fields + 1));
    generate_all(std::back_inserter(all_pos), num_fields);
    std::sort(all_pos.begin(), all_pos.end(), [](const HalfPos& l, const HalfPos& r){ return l.Pips() < r.Pips(); });

    std::vector<int> blocks;
    blocks.resize(all_pos.back().Pips() + 1);
    for (int i = 0; i < all_pos.size(); i++)
        blocks[all_pos[i].Pips()] = i + 1;

    // Initialize
    bearing_off_map[HalfPos({15, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0})] = ProbDist(std::vector{1.0});

    std::unordered_map<HalfPos, ProbDist> local_map;
    for (int j = 1; j < blocks.size(); j++)
    {
        #pragma omp parallel private(local_map)
        {
            #pragma omp for
            for (int i = blocks[j-1]; i < blocks[j]; i++)
            {
                ProbDist avg;
                for (const auto& roll : Dice::All())
                {
                    ProbDist best(std::vector{0.0, std::numeric_limits<double>::infinity()});
                    for (const auto& ply : PossiblePlies(all_pos[i], roll))
                        best = std::min(best, bearing_off_map.at(Play(all_pos[i], ply)));

                    avg += best;
                    if (!roll.IsPair())
                        avg += best;
                }
                avg.Normalize();
                avg.ShiftOneUp();
                local_map[all_pos[i]] = std::move(avg);
            }
            #pragma omp critical
                bearing_off_map.merge(local_map);
        }
    }
    std::cout << to_string(bearing_off_map[all_pos.back()]) << std::endl;
    std::cout << bearing_off_map[all_pos.back()].ExpectationValue() << std::endl;
}

void FillMap2()
{
    const int num_fields = 6;

	std::vector<HalfPos> all_pos;
    all_pos.reserve(MultisetNumber(15, num_fields + 1));
    generate_all(std::back_inserter(all_pos), num_fields);
    std::sort(all_pos.begin(), all_pos.end(), [](const HalfPos& l, const HalfPos& r){ return l.Pips() < r.Pips(); });

    //std::vector<int> blocks;
    //blocks.resize(all_pos.back().Pips() + 1);
    //for (int i = 0; i < all_pos.size(); i++)
    //    blocks[all_pos[i].Pips()] = i + 1;

    //std::vector<ProbDist> to_add;

    // Initialize
    bearing_off_map[HalfPos({15, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0})] = ProbDist(std::vector{1.0});

    //for (int j = 1; j < blocks.size(); j++)
    {
        //to_add.resize(blocks[j] - blocks[j-1]);

        //#pragma omp parallel for
        //for (int i = blocks[j-1]; i < blocks[j]; i++)
        for (int i = 1; i < all_pos.size(); i++)
        {
            ProbDist avg;
            for (const auto& roll : Dice::All())
            {
                ProbDist best(std::vector{0.0, std::numeric_limits<double>::max()});
                for (const auto& ply : PossiblePlies(all_pos[i], roll))
                    best = std::min(best, bearing_off_map.at(Play(all_pos[i], ply)));

                avg += best;
                if (!roll.IsPair())
                    avg += best;
            }
            avg.Normalize();
            avg.ShiftOneUp();
            //to_add[i-blocks[j-1]] = std::move(avg);
            bearing_off_map[all_pos[i]] = std::move(avg);
        }
        //for (int i = blocks[j-1]; i < blocks[j]; i++)
        //    bearing_off_map[all_pos[i]] = std::move(to_add[i-blocks[j-1]]);
    }
    std::cout << to_string(bearing_off_map[all_pos.back()]) << std::endl;
    std::cout << bearing_off_map[all_pos.back()].ExpectationValue() << std::endl;
}

//ProbDist BearingOffProbDist(const HalfPos& pos)
//{
//}
//
//double P_Win(const Position& pos)
//{
//	assert(pos.O_IsGameOver() == false);
//
//	const ProbDist P = BearingOffProbDist(pos.P());
//	const ProbDist O = BearingOffProbDist(pos.O());
//
//	double win_sum = P[0];
//	double o_sum = 0;
//
//	const std::size_t size = std::min(P.size(), O.size() + 1);
//	for (std::size_t i = 1; i < size; i++)
//	{
//		o_sum += O[i - 1];
//		win_sum += P[i] * (1.0 - o_sum);
//	}
//	return win_sum;
//}