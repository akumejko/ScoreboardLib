#pragma once

class Score
{
public:
	Score();
	Score(int homeGoals, int awayGoals);

	const int GetHomeGoals() const;
	const int GetAwayGoals() const;

	bool SetHomeGoals(const int goals);
	bool SetAwayGoals(const int goals);

	bool IsValid() const;
	
private:
	int _homeGoals;
	int _awayGoals;
};
