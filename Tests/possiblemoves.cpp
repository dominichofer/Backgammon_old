#include "pch.h"

void SingleMove(const HalfPos& pos, int pip, const Move& expected)
{
	for (const auto& move : PossibleMoves(pos, pip))
		EXPECT_EQ(move, expected);
}

TEST(PossibleMoves_of_halfpos, single_move)
{
	SingleMove(HalfPos({0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{1,0});
	SingleMove(HalfPos({0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{2,1});
	SingleMove(HalfPos({0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{3,2});
	SingleMove(HalfPos({0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{4,3});
	SingleMove(HalfPos({0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{5,4});
	SingleMove(HalfPos({0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{6,5});

	SingleMove(HalfPos({0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{7,6});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{8,7});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{9,8});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{10,9});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{11,10});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{12,11});

	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{13,12});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{14,13});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0, 0}), 1, Move{15,14});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,0,0,0,0, 0}), 1, Move{16,15});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0}), 1, Move{17,16});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0,0,0,0,0,0, 0}), 1, Move{18,17});

	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0}), 1, Move{19,18});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,1,0,0,0,0, 0}), 1, Move{20,19});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,1,0,0,0, 0}), 1, Move{21,20});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,0,0, 0}), 1, Move{22,21});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,1,0, 0}), 1, Move{23,22});
	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,1, 0}), 1, Move{24,23});

	SingleMove(HalfPos({0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}), 1, Move{25,24});
}

TEST(PossibleMoves_of_halfpos, start_move)
{
	auto gen = PossibleMoves(HalfPos::Start(), 1);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 4);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(6,5)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(8,7)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(13,12)), moves.end());
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(24,23)), moves.end());
}

TEST(PossibleMoves_of_halfpos, must_play_bar)
{
	auto gen = PossibleMoves(HalfPos({0, 0,0,0,0,0,0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 1}), 1);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(HalfPos::bar,24)), moves.end());
}

TEST(PossibleMoves_of_halfpos, play_1)
{
	auto gen = PossibleMoves(HalfPos({0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(1,0)), moves.end());
}

TEST(PossibleMoves_of_halfpos, play_2)
{
	auto gen = PossibleMoves(HalfPos({0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 1);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(2,1)), moves.end());
}

TEST(PossibleMoves_of_halfpos, overplay_5)
{
	auto gen = PossibleMoves(HalfPos({0, 0,0,0,0,1,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 6);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(5,0)), moves.end());
}

TEST(PossibleMoves_of_halfpos, overplay_1)
{
	auto gen = PossibleMoves(HalfPos({0, 1,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 6);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(1,0)), moves.end());
}

TEST(PossibleMoves_of_halfpos, not_overplay)
{
	auto gen = PossibleMoves(HalfPos({0, 0,0,0,0,1,1, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), 6);
	Moves moves(gen.begin(), gen.end());

	EXPECT_EQ(moves.size(), 1);
	EXPECT_NE(std::find(moves.begin(), moves.end(), Move(6,0)), moves.end());
}

TEST(PossiblePlies_of_halfpos, start_move)
{
	auto gen = PossiblePlies(HalfPos::Start(), Dice{1,2});
	Plies plies(gen.begin(), gen.end());

	EXPECT_EQ(plies.size(), 39);
	EXPECT_NE(std::find(plies.begin(), plies.end(), Ply(Move(6,5), Move(6,4))), plies.end());
}

TEST(PossiblePlies_of_halfpos, some)
{
	auto gen = PossiblePlies(HalfPos({0, 0,1,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0}), Dice{1,1});
	Plies plies(gen.begin(), gen.end());

	EXPECT_EQ(plies.size(), 1);
	EXPECT_NE(std::find(plies.begin(), plies.end(), Ply(Move(2,1), Move(1,0))), plies.end());
}