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

			Assert::AreEqual(score.GetAwayGoals(), 0);
			Assert::AreEqual(score.GetHomeGoals(), 0);
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
