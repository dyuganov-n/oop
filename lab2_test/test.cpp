#include "pch.h"

#include "pch.h"
#include "gtest/gtest.h"

#include "../lab2_life_game/lab2_life_game/Game.h"
#include "../lab2_life_game/lab2_life_game/Parser.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(GameTest, EmptyField) {
	Game game;
	EXPECT_EQ(game.getStepCnt(), 0);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
