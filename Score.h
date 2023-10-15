#pragma once

class Score
{
public:
	Score() {}
	Score(int, int) {}

	const int GetHomeGoals() { return 0; }
	const int GetAwayGoals() { return 0; }

	bool SetHomeGoals(const int) { return false; }
	bool SetAwayGoals(const int) { return false; }

	const bool IsValid() const { return false; }
};
