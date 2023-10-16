#pragma once
#include <list>

#include "Match.h"
#include <map>

class Scoreboard
{
public:
	Scoreboard();

	std::string StartNewMatch(std::string homeTeamName, std::string awayTeamName);
	bool UpdateMatchScore(const std::string& matchId, const Score score);
	bool FinishMatch(const std::string& matchId);
	
	std::list<Match> GetMatchesSummary() const;

private:
	bool ProcessNewMatch(const Match& match);
	static bool sortByGoalsAndTimestamp(const Match& m1, const Match& m2);

private:
	std::map<std::string, Match> _matchContainer;
};