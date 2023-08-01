#include "pch.h"

TEST(HalfPos, CanBearOff_True)
{
	EXPECT_TRUE(HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_TRUE(HalfPos({0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
}

TEST(HalfPos, CanBearOff_False)
{
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0}).CanBearOff());
	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0}).CanBearOff());

	EXPECT_FALSE(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).CanBearOff());
}

TEST(HalfPos, HighestChecker)
{
	EXPECT_EQ(HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).HighestChecker(), 0);
	EXPECT_EQ(HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}).HighestChecker(), 12);
	EXPECT_EQ(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}).HighestChecker(), HalfPos::bar);
}

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
TEST(HalfPosGenerator, Generates_correct_number_of_halfpos)
{
	for (int num_fields = 1; num_fields < 13; num_fields++)
	{
		HalfPosGenerator gen(num_fields);
		auto size = std::distance(gen.begin(), gen.end());
		EXPECT_EQ(size, MultisetNumber(15, num_fields + 1));
	}
}

// TODO: Move!
TEST(Position, IsEndgame)
{
	EXPECT_TRUE(Position(
		HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}),
		HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}))
		.IsEndgame());
	EXPECT_FALSE(Position::Start().IsEndgame());
	EXPECT_FALSE(Position(
		HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0}),
		HalfPos({1, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0}))
		.IsEndgame());
}