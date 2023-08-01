#pragma once
#include "halfpos.h"
#include "prob_dist.h"
#include <unordered_map>

static std::unordered_map<HalfPos, ProbDist> bearing_off_map;

void FillMap();