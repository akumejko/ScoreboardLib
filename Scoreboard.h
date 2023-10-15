#pragma once
#include <list>

#include "Match.h"

class Scoreboard
{
public:
	Scoreboard() {}

	std::string StartNewMatch(std::string homeTeamName, std::string awayTeamName) { return std::string(); }
	bool UpdateMatchScore(const std::string&, const Score) { return false; }
	bool FinishMatch(const std::string&) { return false; }
	
	std::list<Match> GetMatchesSummary() const { return std::list<Match>(); }
};