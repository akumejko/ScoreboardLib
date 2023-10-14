#pragma once
#include <string>
#include <ctime>

#include "Score.h"

class Match
{
public:
	Match() {}

	const std::string GetId() const { return std::string(); }
	const std::string GetHomeTeamName() const { return std::string(); }
	const std::string GetAwayTeamName() const { return std::string(); }
	const Score GetScore() const { return Score(); }
	const std::time_t GetTimestamp() const { return std::time_t(); }

	void Start() {};
	bool SetHomeTeamName(std::string&) { return false; }
	bool SetAwayTeamName(std::string&) { return false; }
};
