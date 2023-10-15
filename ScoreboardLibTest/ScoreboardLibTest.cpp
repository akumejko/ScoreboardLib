#include "pch.h"
#include "CppUnitTest.h"

#include "../Scoreboard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ScoreboardLibTest
{
	TEST_CLASS(ScoreTests)
	{
	public:
		
		TEST_METHOD(Test_ScoreShouldInitializeWithZero)
		{
			Score score;

			Assert::AreEqual(0, score.GetAwayGoals());
			Assert::AreEqual(0, score.GetHomeGoals());
		}

		TEST_METHOD(Test_ScoreShouldNotAllowNegativeGoals)
		{
			Score score1(-1, -1);
			Assert::AreEqual(0, score1.GetAwayGoals());
			Assert::AreEqual(0, score1.GetHomeGoals());

			Score score2(1, 2);
			Assert::IsFalse(score2.SetHomeGoals(-1));
			Assert::IsFalse(score2.SetAwayGoals(-1));

			Assert::AreEqual(1, score2.GetHomeGoals());
			Assert::AreEqual(2, score2.GetAwayGoals());
		}
	};

	TEST_CLASS(MatchTests)
	{
	public:

		TEST_METHOD(Test_MatchShouldInitializeWithId)
		{
			Match match;

			Assert::IsFalse(match.GetId().empty());
		}
	};

	TEST_CLASS(ScoreboardTests)
	{
	public:

		TEST_METHOD(Test_ScoreboardShouldInitializeWithEmptySummary)
		{
			Scoreboard scoreboard;

			Assert::IsTrue(scoreboard.GetMatchesSummary().empty());
		}
	};
}
