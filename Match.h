#pragma once
#include <string>
#include <chrono>

#include "Score.h"

class Match
{
public:
	Match() {}
	Match(std::string, std::string) {}

	const std::string GetId() const { return std::string(); }
	const std::string GetHomeTeamName() const { return std::string(); }
	const std::string GetAwayTeamName() const { return std::string(); }
	const Score GetScore() const { return Score(); }
	const std::chrono::milliseconds GetTimestamp() const { return std::chrono::milliseconds(0); }
	const int GetGoalCount() { return 0; }
	const bool IsValid() const { return false; }

	void Start() {};
	bool SetHomeTeamName(std::string) { return false; }
	bool SetAwayTeamName(std::string) { return false; }
	bool SetScore(const Score) { return false; }

	bool operator==(const Match&) const { return false; }
};
