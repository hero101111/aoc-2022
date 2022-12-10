#pragma once

#include "SolutionDay.h"

class Day6 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day6() {}

  ~Day6() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "6"; }

  LL DoWork(int n)
  {
    string s = mData[0];
    for (LL c : rangeint(n, s.size() - 1))
    {
      string sub     = s.substr(c - n + 1, n);
      auto   freq    = getcharfreq(sub);
      bool   invalid = any_of(begin(freq), end(freq),
                              [](pair<char, int> p)
                              {
                              return p.second > 1;
                            });
      if (!invalid)
        return c + 1;
    }
    return 0;
  }

  string Part1() override
  {
    ReadData();

    return to_string(DoWork(4));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(14));
  }

  bool Test() override
  {
    mCurrentInput = "test";
    assert(Part1() == "11");
    assert(Part2() == "26");

    mCurrentInput = "input";
    assert(Part1() == "1480");
    assert(Part2() == "2746");
    return true;
  }
};
