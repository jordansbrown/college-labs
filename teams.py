from collections import OrderedDict
from dataclasses import dataclass, field
from datetime import datetime
from queue import PriorityQueue
from string import Template

from sportsipy.ncaab.teams import Teams

@dataclass(order=True)
class PrioritizedItem:
    opp_points_per_games_played: float
    win_percentage: float
    timestamp: float = field(init=False, default_factory=datetime.now().time)
    team: Teams = field(compare=False)


print('=' * 80)
print('Starting heaping')
heap = PriorityQueue()
for team in Teams(2021):
    if team.opp_points is None or team.name is None or team.win_percentage is None or team.games_played is None:
        continue
    opp_points_per_games_played = team.opp_points / team.games_played
    prioritizedTeam = PrioritizedItem(opp_points_per_games_played, team.win_percentage, team)
    heap.put(prioritizedTeam)
print('=' * 80)
print('Finished heaping')
orderedDict = OrderedDict()
while not heap.empty():
    prioritizedTeam = heap.get()
    templ_string = '$team allows on average $points points with a win percentage of $win'
    msg = Template(templ_string).substitute(team=prioritizedTeam.team.name,
                                            points=prioritizedTeam.opp_points_per_games_played,
                                            win=prioritizedTeam.win_percentage)
    # print('=' * 80)
    # print(msg)
    
orderedDict[prioritizedTeam.team] = prioritizedTeam
print('=' * 80)
print('=' * 80)
print('=' * 80)


high_scoring_teams_so_far = []
counter = 100
while orderedDict and counter > 0:
    counter -= 1
    team = orderedDict.popitem()[0]
    schedule = team.schedule
    for game in schedule:
        if game.datetime < datetime.now():
            continue
        if game.opponent_name in high_scoring_teams_so_far:
            print('=' * 80)
            print(
                Template('Jackpot! $name allows a lot of points ($teampoints) and plays $opponent on $date').substitute(
                    name=team.name,
                    teampoints=team.opp_points,
                    opponent=game.opponent_name,
                    date=game.date))
    high_scoring_teams_so_far.append(team.name)