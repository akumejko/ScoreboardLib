#pragma once

class Score
{
public:
	Score() {}

	const int GetHomeGoals() { return 0; }
	const int GetAwayGoals() { return 0; }

	bool SetHomeGoals(const int) { return false; }
	bool SetAwayGoals(const int) { return false; }
};
