#pragma once
#include <list>

#include "Match.h"

class Scoreboard
{
public:
	Scoreboard() {}

	bool StartNewMatch(const Match&) { return false; }
	bool UpdateMatchScore(const std::string&) { return false; }
	bool FinishMatch(const std::string&) { return false; }
	
	std::list<Match> GetMatchesSummary() const { return std::list<Match>(); }
};