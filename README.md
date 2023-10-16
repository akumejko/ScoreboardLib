# ScoreboardLib

> * **Language:** C++
> * **Platform:** Windows
> * **Compiler/IDE:** Microsoft Visual Studio 2022 (Community Edition)
---
## Overview
ScoreboardLib is a simple C++ static library serving a functionality to manage football matches scoreboard.  
There are 3 main objects to use:  
* `Score` - a class holding a score, with a basic logic checking against invalid input
* `Match` - a class representing a match between 2 teams
* `Scoreboard` - core class holding the logic to process matches and return ordered summary. Scoreboard implements following interface:  
  * `std::string StartNewMatch(std::string homeTeamName, std::string awayTeamName)` - method returning id of a newly created match (empty string in case of error)
  * `bool UpdateMatchScore(const std::string& matchId, const Score score)` - method to update given match's score (returns true in case of success)
  * `bool FinishMatch(const std::string& matchId)` - method removing given match from the scoreboard (returns true in case of success)
  * `std::list<Match> GetMatchesSummary() const` - method returning a list of matches order by number of goals (1st) and timestamp of the beginning of the match (2nd)
  
Additionally project contains a set of unit test verifying library's functionality (`ScoreboardLibTest` folder)

---
## Compilation and usage
In order to compile the project MSVC compiler is required. Most convinient option is to download [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) (licenses apply, library was created with Community Edition) - solution file is provided as part of this project.

---
## Further improvement ideas
Library is focusing on rather simple solution, here are some ideas for improvements and further exploration:  
* improved dummy protection against inacceptable team names (eg.assuming World Cup competition and team names being actual country names it might be worth allowing only latin alphabetical characters, no special signs or numbers)
* unit tests contain Sleep statements - proper method of implementation should pass time controlling object that can be mocked in tests (omitted due to simplicity and low impact on test time execution)
* library does not check if same team is listed in different matches in the scoreboard (in reality one might assume a team cannot play 2 games at once, following validity checks can be applied)
* library return true/false (or empty string) in case of simple failures without providing more information on the nature of the error - error handling can be enhanced
* performance and functionality can be improved in different aspects:  
  * different sorting model are easily addedd by providing more static compare methods in `Scoreboard` class
  * match id handling can be solved by internal id creation rather than by concatenating team names (eg. int or guid could be returned, potentially thread safety would have to be considered then)
  * sorting is done on every get - this could be improved depending on the library usage to sort on match start/finish or by limiting sorting on get by introducing update flag (again - thread safety might become an issue)
