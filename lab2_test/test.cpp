#include "pch.h"

#include "pch.h"
#include "gtest/gtest.h"

#include "../lab2_life_game/lab2_life_game/Game.h"
#include "../lab2_life_game/lab2_life_game/Parser.h"

TEST(Constructor, EmptyField) {
	Game game;

	EXPECT_EQ(game.getStepCnt(), 0);
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			EXPECT_EQ(game.getCurField()[i][j], 0);
		}
	}
	EXPECT_NO_THROW();
}

TEST(Reset, NormalUse) {
	Game game;
	
	game.setCell(0, 0);
	game.nextStep();
	game.resetGame();

	EXPECT_EQ(game.getStepCnt(), 0);
	EXPECT_EQ(game.getCurField()[0][0], 0);
	EXPECT_NO_THROW();
}

TEST(Reset, DoubleReset) {
	Game game;

	game.setCell(0, 0);
	game.resetGame();
	game.resetGame();

	EXPECT_EQ(game.getStepCnt(), 0);
	EXPECT_EQ(game.getCurField()[0][0], 0);
	EXPECT_NO_THROW();
}

TEST(Back, NormalUse) {
	Game game;
	
	game.setCell(0, 1);
	game.setCell(1, 1);
	game.setCell(2, 1);
	game.nextStep();
	
	EXPECT_NO_THROW(game.back());
	
	EXPECT_EQ(game.getCurField()[0][1], 1); 
	EXPECT_EQ(game.getCurField()[1][1], 1); 
	EXPECT_EQ(game.getCurField()[2][1], 1); 
	EXPECT_EQ(game.getCurField()[1][0], 0);
	EXPECT_EQ(game.getCurField()[1][2], 0);
}

TEST(Back, CantGoBack) {
	Game game;

	EXPECT_THROW(game.back(), exception);
}

TEST(SetCell, NormalUse) {
	Game game;

	EXPECT_NO_THROW(game.setCell(0, 0));
	EXPECT_NO_THROW(game.setCell(9, 9));
	EXPECT_NO_THROW(game.setCell(1, 0));
	EXPECT_NO_THROW(game.setCell(0, 1));


	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((i == 0 && j == 0) || (i == 9 && j == 9) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
				EXPECT_EQ(game.getCurField()[i][j], 1);
			}
			else {
				EXPECT_EQ(game.getCurField()[i][j], 0);
			}
		}
	}
}

TEST(SetCell, WrongIndex) {
	Game game;

	EXPECT_THROW(game.setCell(1, 10), exception);
	EXPECT_THROW(game.setCell(10, 1), exception);
	EXPECT_THROW(game.setCell(11, 11), exception);
}

TEST(SetCell, DoubleUse) {
	Game game;

	EXPECT_NO_THROW(game.setCell(0, 0));
	EXPECT_NO_THROW(game.setCell(9, 9));
	EXPECT_NO_THROW(game.setCell(1, 0));
	EXPECT_NO_THROW(game.setCell(0, 1));
	EXPECT_NO_THROW(game.setCell(0, 0));
	EXPECT_NO_THROW(game.setCell(9, 9));
	EXPECT_NO_THROW(game.setCell(1, 0));
	EXPECT_NO_THROW(game.setCell(0, 1));


	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((i == 0 && j == 0) || (i == 9 && j == 9) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
				EXPECT_EQ(game.getCurField()[i][j], 1);
			}
			else {
				EXPECT_EQ(game.getCurField()[i][j], 0);
			}
		}
	}
}

TEST(ClearCell, NormalUse) {
	Game game;
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			game.getCurField()[i][j] = 1;
		}
	}

	EXPECT_NO_THROW(game.clearCell(0, 0));
	EXPECT_NO_THROW(game.clearCell(9, 9));
	EXPECT_NO_THROW(game.clearCell(1, 0));
	EXPECT_NO_THROW(game.clearCell(0, 1));


	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((i == 0 && j == 0) || (i == 9 && j == 9) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
				EXPECT_EQ(game.getCurField()[i][j], 0);
			}
			else {
				EXPECT_EQ(game.getCurField()[i][j], 1);
			}
		}
	}
}

TEST(ClearCell, WrongIndex) {
	Game game;

	EXPECT_THROW(game.clearCell(1, 10), exception);
	EXPECT_THROW(game.clearCell(10, 1), exception);
	EXPECT_THROW(game.clearCell(11, 11), exception);
}

TEST(ClearCell, DoubleUse) {
	Game game;
	EXPECT_NO_THROW(game.clearCell(0, 0));

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			game.getCurField()[i][j] = 1;
		}
	}

	EXPECT_NO_THROW(game.clearCell(0, 0));
	EXPECT_NO_THROW(game.clearCell(9, 9));
	EXPECT_NO_THROW(game.clearCell(1, 0));
	EXPECT_NO_THROW(game.clearCell(0, 1));
	EXPECT_NO_THROW(game.clearCell(0, 0));
	EXPECT_NO_THROW(game.clearCell(9, 9));
	EXPECT_NO_THROW(game.clearCell(1, 0));
	EXPECT_NO_THROW(game.clearCell(0, 1));


	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((i == 0 && j == 0) || (i == 9 && j == 9) || (i == 1 && j == 0) || (i == 0 && j == 1)) {
				EXPECT_EQ(game.getCurField()[i][j], 0);
			}
			else {
				EXPECT_EQ(game.getCurField()[i][j], 1);
			}
		}
	}
}

TEST(Step, NormalUse) {
	Game game;
	game.setCell(3, 3);
	game.setCell(3, 4);
	game.setCell(3, 5);

	EXPECT_NO_THROW(game.nextStep());

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((i == 3 && j == 4) || (i == 2 && j == 4) || (i == 4 && j == 4)) {
				EXPECT_EQ(game.getCurField()[i][j], 1);
			}
			else {
				EXPECT_EQ(game.getCurField()[i][j], 0);
			}
		}
	}
	EXPECT_EQ(game.getStepCnt(), 1);
	EXPECT_NO_THROW(game.nextStep());
	EXPECT_EQ(game.getStepCnt(), 2);
}

TEST(Step, SingleCell) {
	Game game;
	game.setCell(3, 3);

	EXPECT_NO_THROW(game.nextStep());

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			EXPECT_EQ(game.getCurField()[i][j], 0);
		}
	}

	EXPECT_NO_THROW(game.nextStep());

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			EXPECT_EQ(game.getCurField()[i][j], 0);
		}
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
