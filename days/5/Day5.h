#pragma once

#include "SolutionDay.h"

class Day5 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day5() {}

  ~Day5() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "5"; }

  string DoWork(bool isPartOne)
  {
    string ret = "";

    LL minN = 1, maxN = 9;

    map<LL, LL> indices;
    for (LL i : rangeint(minN, maxN))
      indices[i] = 1 + (i - 1) * 4;

    map<LL, vector<char>> data;

    for (auto d : mData)
    {
      if (d.size() > 1 && d[0] == '[')
      {
        for (LL i : rangeint(minN, maxN))
        {
          char c = d[indices[i]];
          if (c != ' ')
            data[i].insert(begin(data[i]), c);
        }
      }
      if (d.size() < 1 || d[0] != 'm')
        continue;

      auto [many, from, to] = tuple_toll(RegExMatch3(d, R"(move (\d+) from (\d+) to (\d+))"));

      vector<char> temp;
      while (many-- > 0)
      {
        if (!data[from].empty())
        {
          temp.insert(isPartOne ? end(temp) : begin(temp), data[from].back());
          data[from].erase(data[from].end() - 1);
        }
      }

      for (auto c : temp)
        data[to].push_back(c);
    }
    for (LL i : rangeint(minN, maxN))
      ret += data[i].back();

    return ret;
  }

  LL DoWork2()
  {
    LL ret = 52;
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return DoWork(true);
  }

  string Part2() override
  {
    ReadData();

    return DoWork(false);
  }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "PTWLTDSJV"s);
    aoc_assert(Part2(), "WZMFVGGZP"s);
    return true;
  }
};
