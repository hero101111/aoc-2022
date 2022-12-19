#pragma once

#include "SolutionDay.h"

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
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "19"; }

  LL DoWork1()
  {
    LL ret = 0;
    
    for (auto d : mData)
    {
      string rgx = R"(Blueprint (.+): Each ore robot costs (.+) ore. Each clay robot costs (.+) ore. Each obsidian robot costs (.+) ore and (.+) clay. Each geode robot costs (.+) ore and (.+) obsidian.)";
      auto [blueprint, oreRCost, clayRCost, obsRCostOre, obsRCostClay, geodeRCostOre, geodeRCostObidian] = RegExMatch7(d, rgx);
      
      map<string, map<string, LL>> costs;
      costs["ore"]["ore"] = stoll(oreRCost);
      costs["clay"]["ore"] = stoll(clayRCost);
      costs["obs"]["ore"] = stoll(obsRCostOre);
      costs["obs"]["clay"] = stoll(obsRCostClay);
      costs["geode"]["ore"] = stoll(geodeRCostOre);
      costs["geode"]["obs"] = stoll(geodeRCostObidian);
      
      LL minute = 1;
      unordered_map<string, LL> res;
      unordered_map<string, LL> robots;
      robots["ore"] = 1;
      
      auto construct = [&](string type)
      {
        auto cost = costs[type];
        
        bool canAfford = true;
        while (true)
        {
          for (auto [costItemName, costItemVal] : cost)
          {
            if (res[costItemName] < costItemVal)
              canAfford = false;
          }
          if (!canAfford)
            break;
          
          for (auto [costItemName, costItemVal] : cost)
          {
            res[costItemName] -= costItemVal;
          }
          robots[type] += 1;
        }
      };
      
      while (true)
      {
        // collect
        for (auto r : robots)
          res[r.first] += r.second;
        
        // construct geode robot
        construct("geode");
        construct("obs");
        construct("clay");
        construct("ore");
        
        
        if (minute++ == 24) break;
      }
      LL qualityLevel = res["geode"] * stoll(blueprint);
      ret += qualityLevel;
    }
    
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 192;
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork2());
  }

  bool Test() override
  {
    mCurrentInput = "test";
     aoc_assert(Part1(), ""s);
    // aoc_assert(Part2() != "");
    return true;
  }
};
