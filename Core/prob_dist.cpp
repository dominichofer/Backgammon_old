#include "prob_dist.h"
#include <string>

std::string to_string(const ProbDist& dist)
{
    std::string ret;
    for (int i = 0; i < dist.size(); i++)
        ret += std::to_string(i) + ": " + std::to_string(dist[i]) + '\n';
    return ret;
}