#pragma once

#include "SolutionDay.h"

using ItemT      = int;
using ResourcesT = unordered_map<ItemT, int>;
using BotsT      = unordered_map<ItemT, int>;
struct State
{
  ResourcesT resources;
  BotsT      bots;
  int        timeLeft;

  bool operator==(const State & other) const
  {
    return resources == other.resources && bots == other.bots && timeLeft == other.timeLeft;
  }

  State() {}

  State(int aTimeLeft, ResourcesT aResources, BotsT aBots)
    : timeLeft(aTimeLeft)
    , resources(aResources)
    , bots(aBots)
  {
  }
};

template <>
struct hash<State>
{
  auto operator()(const State & k) const -> std::size_t
  {
    string s = to_string(k.timeLeft) + "_";
    for (auto & [res, resV] : k.resources)
      s += res + "_" + to_string(resV);
    for (auto & [robot, robotV] : k.bots)
      s += robot + "_" + to_string(robotV);
    return hash<string>()(s);
  }
};

class Day19 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day19() {}

  ~Day19() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());  // xxxxxxxxxxxxxxxxxxxxxxxxxxxx
  }

  int ore{ 0 };
  int clay{ 1 };
  int obs{ 2 };
  int geode{ 3 };

  string GetDay() override { return "19"; }

  using CostMapT   = unordered_map<ItemT, unordered_map<ItemT, int>>;
  using CacheT     = unordered_map<State, int>;
  using MaxDemandT = unordered_map<ItemT, int>;

  bool shouldBuildBot(ItemT robotType, BotsT bots, MaxDemandT & maxDemand)
  {
    return bots[robotType] < maxDemand[robotType];
  }

  optional<ResourcesT> canBuildBot(ItemT robotType, const ResourcesT & res, CostMapT & costs)
  {
    ResourcesT ret = res;
    for (auto [req, reqQ] : costs[robotType])
    {
      ret[req] -= reqQ;
      if (ret[req] < 0)
        return nullopt;
    }
    return ret;
  }

  ResourcesT updateResources(ResourcesT res, BotsT bots)
  {
    ResourcesT ret = res;
    for (auto [botName, botCount] : bots)
    {
      res[botName] += botCount;
    }
    return res;
  }

  LL solve(const State & state, CacheT & cache, CostMapT costs, MaxDemandT maxDemand)
  {
    if (cache.find(state) != end(cache))
      return cache[state];

    if (state.timeLeft == 0)
    {
      auto geodeIt = state.resources.find(geode);
      return geodeIt == end(state.resources) ? 0 : geodeIt->second;
    }

    if (auto canBuildGeode = canBuildBot(geode, state.resources, costs))
    {
      auto newResources = updateResources(*canBuildGeode, state.bots);
      auto newRobots    = state.bots;
      newRobots[geode] += 1;
      State newState{ state.timeLeft - 1, newResources, newRobots };
      return solve(newState, cache, costs, maxDemand);
    }

    int        typesShouldBuild = 0;
    int        typesCanBuild    = 0;
    vector<LL> candidates;

    for (auto robotType : { ore, clay, obs })
    {
      if (shouldBuildBot(robotType, state.bots, maxDemand))
      {
        if (auto newMaterials = canBuildBot(robotType, state.resources, costs))
        {
          ResourcesT newResources = updateResources(*newMaterials, state.bots);
          BotsT      newRobots    = state.bots;
          newRobots[robotType] += 1;
          State buildNewBotState{ state.timeLeft - 1, newResources, newRobots };
          candidates.push_back(solve(buildNewBotState, cache, costs, maxDemand));
          typesCanBuild += 1;
        }
        typesShouldBuild += 1;
      }
    }

    if (typesCanBuild < typesShouldBuild)
    {
      ResourcesT newResources = updateResources(state.resources, state.bots);
      State      doNothingState{ state.timeLeft - 1, newResources, state.bots };
      candidates.push_back(solve(doNothingState, cache, costs, maxDemand));
    }

    LL best = 0;
    for (auto res : candidates)
      best = max(best, res);

    cache[state] = best;
    return best;
  }

  LL DoWork(bool partOne)
  {
    LL geodeScores[30];

    int blueprintCount{ 0 };
    {
      vector<jthread> workers;
      workers.reserve(40);
      if (!partOne)
        mData.erase(mData.begin() + 3, mData.end());

      for (auto d : mData)
      {
        workers.push_back(jthread(
          [&](string inputLine, LL & outScore)
          {
            CacheT cache;

            CostMapT   costs;
            MaxDemandT maxDemand;

            string rgx =
              R"(Blueprint (.+): Each ore robot costs (.+) ore. Each clay robot costs (.+) ore. Each obsidian robot costs (.+) ore and (.+) clay. Each geode robot costs (.+) ore and (.+) obsidian.)";
            auto [blueprint, oreRCostOre, clayRCostOre, obsRCostOre, obsRCostClay, geodeRCostOre,
                  geodeRCostObidian] = RegExMatch7(inputLine, rgx);

            costs[ore][ore]   = stoll(oreRCostOre);
            costs[clay][ore]  = stoll(clayRCostOre);
            costs[obs][ore]   = stoll(obsRCostOre);
            costs[obs][clay]  = stoll(obsRCostClay);
            costs[geode][ore] = stoll(geodeRCostOre);
            costs[geode][obs] = stoll(geodeRCostObidian);

            for (auto res : { ore, clay, obs })
              maxDemand[res] = -1;
            for (auto res : { ore, clay, obs, geode })
              for (auto [resReqN, resReqV] : costs[res])
                maxDemand[resReqN] = max(maxDemand[resReqN], resReqV);

            State initState;
            initState.bots[ore] = 1;
            initState.timeLeft  = partOne ? 24 : 32;

            auto geodeScore = solve(initState, cache, costs, maxDemand);
            cout << "| " << geodeScore << endl;
            outScore = geodeScore;
          },
          d, ref(geodeScores[blueprintCount++])));
      }
    }

    LL ret = 0;
    if (partOne)
    {
      for (int i = 0; i < blueprintCount; ++i)
        ret += geodeScores[i] * (i + 1);
    }
    else
    {
      ret = geodeScores[0] * geodeScores[1] * geodeScores[2];
    }
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  bool Test() override
  {
    mCurrentInput = "test";
    // aoc_assert(Part1(), ""s);
    //  aoc_assert(Part2() != "");
    return true;
  }
};
