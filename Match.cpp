#include "pch.h"
#include "Match.h"

Match::Match()
	: _homeTeamName("")
	, _awayTeamName("")
	, _id("")
	, _timestamp(0)
{

}

Match::Match(std::string homeTeamName, std::string awayTeamName)
	: _timestamp(0)
{
	SetHomeTeamName(homeTeamName);
	SetAwayTeamName(awayTeamName);

	if (IsValid())
	{
		_id = GetHomeTeamName() + GetAwayTeamName();
	}
}

const std::string& Match::GetId() const
{
	return _id;
}

const std::string& Match::GetHomeTeamName() const
{
	return _homeTeamName;
}

const std::string& Match::GetAwayTeamName() const
{
	return _awayTeamName;
}

const Score& Match::GetScore() const
{
	return _score;
}

const std::chrono::milliseconds Match::GetTimestamp() const
{
	return _timestamp;
}

const int Match::GetGoalCount() const
{
	return _score.GetHomeGoals() + _score.GetAwayGoals();
}

bool Match::IsValid() const
{
	return (!_homeTeamName.empty() && !_awayTeamName.empty());
}

void Match::Start()
{
	using namespace std::chrono;

	_timestamp = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch());
}

bool Match::SetHomeTeamName(std::string teamName)
{
	if (teamName.empty()) return false;

	_homeTeamName = trim(teamName);
	return true;
}

bool Match::SetAwayTeamName(std::string teamName)
{
	if (teamName.empty()) return false;

	_awayTeamName = trim(teamName);
	return true;
}

bool Match::SetScore(const Score score)
{
	if (!score.IsValid()) return false;

	_score.SetHomeGoals(score.GetHomeGoals());
	_score.SetAwayGoals(score.GetAwayGoals());

	return true;
}

bool Match::operator==(const Match& other) const
{
	return _homeTeamName == other._homeTeamName &&
		_awayTeamName == other._awayTeamName;
}

std::string Match::trim(const std::string& str)
{
	std::string whitespace = " \t";
	
	auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos) return "";

	auto strEnd = str.find_last_not_of(whitespace);
	auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}