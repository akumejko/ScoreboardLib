#include "pch.h"
#include "Scoreboard.h"

Scoreboard::Scoreboard()
{

}

std::string Scoreboard::StartNewMatch(std::string homeTeamName, std::string awayTeamName)
{
	std::string id = "";
	Match newMatch(homeTeamName, awayTeamName);

	if (newMatch.IsValid())
	{
		if (ProcessNewMatch(newMatch))
		{
			id = newMatch.GetId();
		}
	}

	return id;
}

bool Scoreboard::UpdateMatchScore(const std::string& matchId, const Score score)
{

	if (_matchContainer.find(matchId) == _matchContainer.end())
	{
		// key doesn't exist
		return false;
	}

	return _matchContainer[matchId].SetScore(score);
}

bool Scoreboard::FinishMatch(const std::string& matchId)
{
	return _matchContainer.erase(matchId) != size_t(0);
}

std::list<Match> Scoreboard::GetMatchesSummary() const
{
	std::list<Match> summary;
	for (auto item : _matchContainer)
	{
		summary.push_back(item.second);
	}

	summary.sort(sortByGoalsAndTimestamp);

	return summary;
}

bool Scoreboard::ProcessNewMatch(const Match& match)
{
	if (_matchContainer.find(match.GetId()) != _matchContainer.end())
	{
		// match already in the container
		return false;
	}

	_matchContainer[match.GetId()] = match;
	_matchContainer[match.GetId()].Start();

	return true;
}

bool Scoreboard::sortByGoalsAndTimestamp(const Match& m1, const Match& m2)
{
	int goals1 = m1.GetGoalCount();
	int goals2 = m2.GetGoalCount();
	
	if (goals2 < goals1) return true;

	if (goals1 == goals2)
	{
		return m2.GetTimestamp() < m1.GetTimestamp();
	}

	return false;
}