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

			Assert::IsTrue(score.IsValid());
		}

		TEST_METHOD(Test_ScoreShouldNotAllowNegativeGoals)
		{
			Score score1(-1, -1);
			Assert::IsFalse(score1.IsValid());
			
			Score score2(1, 2);
			Assert::IsTrue(score2.IsValid());

			Assert::IsFalse(score2.SetHomeGoals(-1));
			Assert::IsFalse(score2.SetAwayGoals(-1));

			Assert::AreEqual(1, score2.GetHomeGoals());
			Assert::AreEqual(2, score2.GetAwayGoals());
			Assert::IsTrue(score2.IsValid());
		}
	};

	TEST_CLASS(MatchTests)
	{
	public:

		TEST_METHOD(Test_MatchShouldNotBeValidWithoutTeamNames)
		{
			Match match;
			Assert::IsFalse(match.IsValid());

			Match match2("", "England");
			Assert::IsFalse(match2.IsValid());

			Match match3("England", "");
			Assert::IsFalse(match3.IsValid());
		}

		TEST_METHOD(Test_MatchShouldHaveDifferentTimestampBasedOnStart)
		{
			Match match1, match2;

			match1.Start();
			Sleep(50); // this should be ideally replace with time mocking
			match2.Start();

			Assert::IsTrue(match2.GetTimestamp() > match1.GetTimestamp());
		}

		TEST_METHOD(Test_MatchShouldHaveDifferentIdBasedOnTeamNames)
		{
			Match match1("Poland", "England");
			Match match2("Brazil", "Argentina");
			Match match3("Poland", "England");

			Assert::AreEqual(std::string("Poland"), match1.GetHomeTeamName());
			Assert::AreEqual(std::string("England"), match1.GetAwayTeamName());

			Assert::AreNotEqual(match1.GetId(), match2.GetId());
			Assert::AreEqual(match1.GetId(), match3.GetId());
		}

		TEST_METHOD(Test_MatchShouldNotAllowEmptyTeamNames)
		{
			Match match1("", "England");
			Assert::IsFalse(match1.IsValid());
			Assert::IsFalse(match1.SetAwayTeamName(""));
			Assert::AreEqual(std::string("England"), match1.GetAwayTeamName());

			Assert::IsTrue(match1.SetHomeTeamName("Poland"));
			Assert::IsTrue(match1.IsValid());


			Match match2("Brazil", "");
			Assert::IsFalse(match2.IsValid());
			Assert::IsFalse(match2.SetHomeTeamName(""));
			Assert::AreEqual(std::string("Brazil"), match2.GetHomeTeamName());

			Assert::IsTrue(match2.SetAwayTeamName("Argentina"));
			Assert::IsTrue(match2.IsValid());
		}

		TEST_METHOD(Test_MatchAllowSettingValidScore)
		{
			Match match;

			Assert::IsTrue(match.SetScore(Score(1, 4)));
			Assert::AreEqual(5, match.GetGoalCount());

			// don't allow ovveride with invalid score
			Assert::IsFalse(match.SetScore(Score(- 1, 2)));
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

		TEST_METHOD(Test_ScoreboardShouldAllowStartingAndFinishingMatches)
		{
			Scoreboard scoreboard;
			const std::string& match1Id = scoreboard.StartNewMatch("Poland", "England");

			Assert::IsFalse(match1Id.empty());
			Assert::AreEqual(1, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			std::string& match2Id = scoreboard.StartNewMatch("Poland", "England");
			// same game is already on the board - should not add new game
			Assert::IsTrue(match2Id.empty());
			Assert::AreEqual(1, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			std::string& match3Id = scoreboard.StartNewMatch("Brazil", "Argentina");
			Assert::IsFalse(match3Id.empty());
			Assert::AreEqual(2, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			Assert::IsTrue(scoreboard.FinishMatch(match1Id));
			Assert::AreEqual(1, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			// should not allow finishing the same game again
			Assert::IsFalse(scoreboard.FinishMatch(match1Id));
			Assert::AreEqual(1, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			// random matchId should not affect the scoreboard
			std::string randomId = "randomId";
			Assert::IsFalse(scoreboard.FinishMatch(randomId));
			Assert::AreEqual(1, static_cast<int>(scoreboard.GetMatchesSummary().size()));

		}

		TEST_METHOD(Test_ScoreboardShouldAllowUpdatingValidScores)
		{
			Scoreboard scoreboard;

			const std::string& matchPolEngId = scoreboard.StartNewMatch("Poland", "England");
			const std::string& matchBraArgId = scoreboard.StartNewMatch("Brazil", "Argentina");
			const std::string& matchFraUruId = scoreboard.StartNewMatch("France", "Uruguay");

			Assert::AreEqual(3, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			Assert::IsTrue(scoreboard.UpdateMatchScore(matchPolEngId, Score(1, 0)));
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchBraArgId, Score(2, 2)));
			Assert::IsFalse(scoreboard.UpdateMatchScore(matchFraUruId, Score(-1, 0)));
		}

		TEST_METHOD(Test_ScoreboardShouldReturnMatchlistAccordingToGoalCountAndTimestamp)
		{
			Scoreboard scoreboard;

			/*	Example:
				
				Given:
				a.Mexico 0 - Canada 5
				b.Spain 10 - Brazil 2
				c.Germany 2 - France 2
				d.Uruguay 6 - Italy 6
				e.Argentina 3 - Australia 1 
				
				Should return:
				1. Uruguay 6 - Italy 6
				2. Spain 10 - Brazil 2
				3. Mexico 0 - Canada 5
				4. Argentina 3 - Australia 1
				5. Germany 2 - France 2 */

			const std::string& matchMexCanId = scoreboard.StartNewMatch("Mexico", "Canada");
			const std::string& matchSpaBraId = scoreboard.StartNewMatch("Spain", "Brazil");
			const std::string& matchGerFraId = scoreboard.StartNewMatch("Germany", "France");
			const std::string& matchUruItaId = scoreboard.StartNewMatch("Uruguay", "Italy");
			const std::string& matchArgAusId = scoreboard.StartNewMatch("Argentina", "Australia");

			Assert::AreEqual(5, static_cast<int>(scoreboard.GetMatchesSummary().size()));

			Assert::IsTrue(scoreboard.UpdateMatchScore(matchMexCanId, Score(0, 5)));
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchSpaBraId, Score(10, 2)));
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchGerFraId, Score(2, 2)));
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchUruItaId, Score(6, 6)));
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchArgAusId, Score(3, 1)));

			std::list<Match> expectedList;
			Match matchUruIta, matchSpaBra, matchMexCan, matchArgAus, matchGerFra;
			matchUruIta.SetScore(Score(6, 6));
			matchSpaBra.SetScore(Score(10, 2));
			matchMexCan.SetScore(Score(2, 2));
			matchArgAus.SetScore(Score(3, 1));
			matchGerFra.SetScore(Score(2, 2));

			
			expectedList.push_back(matchUruIta);
			expectedList.push_back(matchSpaBra);
			expectedList.push_back(matchMexCan);
			expectedList.push_back(matchArgAus);
			expectedList.push_back(matchGerFra);

			Assert::IsTrue(expectedList == scoreboard.GetMatchesSummary());

			// finished match should be removed from summary
			Assert::IsTrue(scoreboard.FinishMatch(matchGerFraId));
			Assert::AreEqual(4, static_cast<int>(scoreboard.GetMatchesSummary().size()));
			
			expectedList.remove(matchGerFra);
			Assert::IsTrue(expectedList == scoreboard.GetMatchesSummary());

			// updated score should affect the order
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchSpaBraId, Score(10, 3)));
			expectedList.remove(matchSpaBra);
			expectedList.push_front(matchSpaBra);

			Assert::IsTrue(expectedList == scoreboard.GetMatchesSummary());

			// new game should affect the order
			const std::string& matchHunTurId = scoreboard.StartNewMatch("Hungary", "Turkey");
			Assert::IsTrue(scoreboard.UpdateMatchScore(matchHunTurId, Score(3, 1)));

			Match matchHunTur("Hungary", "Turkey");
			matchHunTur.SetScore(Score(3, 1));

			expectedList.clear();
			expectedList.push_back(matchSpaBra);
			expectedList.push_back(matchUruIta);
			expectedList.push_back(matchMexCan);
			expectedList.push_back(matchHunTur);
			expectedList.push_back(matchArgAus);
		}

	};
}
