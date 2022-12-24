#pragma once

#include "SolutionDay.h"

struct StateD24
{
  int   minute;
  Point pos;
  bool  part2FinishedFirstGoalTrip{ false };
  bool  part2OnSecondTripToGoal{ false };

  bool operator==(const StateD24 & other) const
  {
    return minute == other.minute && pos == other.pos &&
           part2FinishedFirstGoalTrip == other.part2FinishedFirstGoalTrip &&
           part2OnSecondTripToGoal == other.part2OnSecondTripToGoal;
  }
};

template <>
struct hash<StateD24>
{
  auto operator()(const StateD24 & k) const -> std::size_t
  {
    string s = to_string(k.minute) + "_";
    s += k.pos.ToString() + "_";
    s += to_string(k.part2FinishedFirstGoalTrip);
    s += to_string(k.part2OnSecondTripToGoal);
    return hash<string>()(s);
  }
};

class Day24 : public ISolutionDay
{
private:
  vector<string> mData;

  const vector<char> kWinds = { '<', '>', 'v', '^' };

  using WindBlowLocationsT = vector<pair<Point, char>>;
  using StateCacheT        = unordered_map<StateD24, LL>;
  using CachedWindsT       = unordered_map<LL, DynamicMap<char>>;

  WindBlowLocationsT windBlowLocations;
  StateCacheT        cache;
  CachedWindsT       cachedWinds;

  Point FIRST, LAST;
  int   MAXCACHESIZE{ 1000 };

public:
  Day24() {}

  ~Day24() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "24"; }

  DynamicMap<char> generateNextWindMap(DynamicMap<char> & aCrtMap)
  {
    auto ret = aCrtMap;
    aCrtMap.for_each(
      [&](Point p, char c)
      {
        if (contains(kWinds, c))
          ret[p] = '.';
      });

    for (auto & [pos, wind] : windBlowLocations)
    {
      Point nextPos = pos.FromDirection(wind);

      if (wind == '>' && nextPos.x == aCrtMap.max_x)
        nextPos.x = aCrtMap.min_x + 1;
      else if (wind == 'v' && nextPos.y == aCrtMap.max_y)
        nextPos.y = aCrtMap.min_y + 1;
      else if (wind == '<' && nextPos.x == aCrtMap.min_x)
        nextPos.x = aCrtMap.max_x - 1;
      else if (wind == '^' && nextPos.y == aCrtMap.min_y)
        nextPos.y = aCrtMap.max_y - 1;

      ret[nextPos] = wind;
      pos          = nextPos;
    }

    return ret;
  }

  LL solve(StateD24 crtState)
  {
    if (cache.find(crtState) != end(cache))
      return cache[crtState];

    if (crtState.pos == LAST && crtState.part2FinishedFirstGoalTrip == true &&
        crtState.part2OnSecondTripToGoal == true)
      return crtState.minute;

    if (crtState.minute > MAXCACHESIZE)
      return MAXCACHESIZE;

    if (crtState.pos == LAST && !crtState.part2FinishedFirstGoalTrip)
      crtState.part2FinishedFirstGoalTrip = true;

    if (crtState.pos == FIRST && crtState.part2FinishedFirstGoalTrip &&
        !crtState.part2OnSecondTripToGoal)
      crtState.part2OnSecondTripToGoal = true;

    assert(cachedWinds.find(crtState.minute) != end(cachedWinds));
    auto & mNext = cachedWinds[crtState.minute + 1];

    LL bestAction{ numeric_limits<LL>::max() };
    // can we move up

    StateD24 next = crtState;
    next.minute   = crtState.minute + 1;
    // can we move
    for (auto c : kWinds)
    {
      Point cand = crtState.pos.FromDirection(c);
      if (mNext.isSetAt(cand) && mNext[cand] == '.')
      {
        StateD24 nextMove = next;
        nextMove.pos      = cand;
        bestAction        = min(bestAction, solve(nextMove));
      }
    }
    // can we stay in place
    if (mNext.isSetAt(crtState.pos) && mNext[crtState.pos] == '.')
    {
      bestAction = min(bestAction, solve(next));
    }
    LL ret          = bestAction != numeric_limits<LL>::max() ? bestAction : MAXCACHESIZE;
    cache[crtState] = ret;

    return ret;
  };

  LL DoWork(bool partTwo)
  {
    DynamicMap<char> inputMap;
    inputMap.fromlines(mData);

    FIRST = inputMap
              .first_if(
                [&](Point p, char c)
                {
                  return p.y == inputMap.min_y && c == '.';
                })
              ->first;

    LAST = inputMap
             .first_if(
               [&](Point p, char c)
               {
                 return p.y == inputMap.max_y && c == '.';
               })
             ->first;

    assert((FIRST != Point{ 0, 0 }));
    assert((LAST != Point{ 0, 0 }));

    cache.clear();
    windBlowLocations.clear();
    {
      inputMap.for_each(
        [&](Point p, char c)
        {
          if (contains(kWinds, c))
            windBlowLocations.push_back(make_pair(p, c));
        });
    }

    cachedWinds.clear();
    {
      auto winds     = inputMap;
      cachedWinds[0] = winds;
      for (int i = 1; i <= MAXCACHESIZE; ++i)
      {
        winds          = generateNextWindMap(inputMap);
        cachedWinds[i] = winds;
      }
    }

    StateD24 initState;
    initState.minute = 0;
    initState.pos    = FIRST;
    if (!partTwo)
    {
      initState.part2FinishedFirstGoalTrip = true;
      initState.part2OnSecondTripToGoal    = true;
    }

    return solve(initState);
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "253"s);
    aoc_assert(Part2(), "794"s);
    return true;
  }
};
