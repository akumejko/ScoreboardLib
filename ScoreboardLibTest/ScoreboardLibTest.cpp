#include "pch.h"
#include "CppUnitTest.h"
#include <windows.h>

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

		TEST_METHOD(Test_MatchShouldNotInitializeWithEmptyValues)
		{
			Match match;

			Assert::IsFalse(match.GetId().empty());
			Assert::IsFalse(match.GetAwayTeamName().empty());
			Assert::IsFalse(match.GetHomeTeamName().empty());
			bool isTimestampInitialized = std::chrono::milliseconds(0) == match.GetTimestamp();
			Assert::IsTrue(isTimestampInitialized);
		}

		TEST_METHOD(Test_MatchShouldHaveDifferentTimestampBasedOnStart)
		{
			Match match1, match2;

			match1.Start();
			match2.Start();

			Assert::IsTrue(match2.GetTimestamp() > match1.GetTimestamp());
		}

		TEST_METHOD(Test_MatchShouldHaveDifferentIdBasedOnTeamNames)
		{
			Match match1("Poland", "England");
			Match match2("Brazil", "Argentina");

			Assert::AreEqual(std::string("Poland"), match1.GetHomeTeamName());
			Assert::AreEqual(std::string("England"), match1.GetAwayTeamName());

			Assert::AreNotEqual(match1.GetId(), match2.GetId());
		}

		TEST_METHOD(Test_MatchShouldNotAllowEmptyTeamNames)
		{
			Match match1("", "England");
			Assert::IsFalse(match1.GetHomeTeamName().empty());

			Match match2("Brazil", "");
			Assert::IsFalse(match2.SetHomeTeamName(""));
			Assert::AreEqual(std::string("Brazil"), match2.GetHomeTeamName());
		}

		TEST_METHOD(Test_MatchAllowSettingValidScore)
		{
			Match match;

			match.SetScore(Score(1, 4));
			Assert::AreEqual(5, match.GetGoalCount());
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
