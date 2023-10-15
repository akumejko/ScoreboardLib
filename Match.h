#pragma once
#include <string>
#include <chrono>

#include "Score.h"

class Match
{
public:
	Match();
	Match(std::string homeTeamName, std::string awayTeamName);

	const std::string& GetId() const;
	const std::string& GetHomeTeamName() const;
	const std::string& GetAwayTeamName() const;
	const Score& GetScore() const;
	const std::chrono::milliseconds GetTimestamp() const;
	const int GetGoalCount();
	bool IsValid() const;

	void Start();
	bool SetHomeTeamName(std::string teamName);
	bool SetAwayTeamName(std::string teamName);
	bool SetScore(const Score score);

	bool operator==(const Match& other) const;

private:
	std::string _homeTeamName;
	std::string _awayTeamName;
	std::string _id;
	Score _score;
	std::chrono::milliseconds _timestamp;
};
