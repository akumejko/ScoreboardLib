#include "pch.h"
#include "Score.h"

Score::Score()
	: _homeGoals(0)
	, _awayGoals(0)
{

}

Score::Score(int homeGoals, int awayGoals)
	: _homeGoals(homeGoals)
	, _awayGoals(awayGoals)
{

}

const int Score::GetAwayGoals() const
{
	return _awayGoals;
}

const int Score::GetHomeGoals() const
{
	return _homeGoals;
}

bool Score::SetAwayGoals(const int goals)
{
	if (goals < 0) return false;

	_awayGoals = goals;
	return true;
}

bool Score::SetHomeGoals(const int goals)
{
	if (goals < 0) return false;

	_homeGoals = goals;
	return true;
}

bool Score::IsValid() const
{
	return (_homeGoals >= 0 && _awayGoals >= 0);
}