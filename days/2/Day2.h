#pragma once

#include "SolutionDay.h"

class Day2 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day2() {}

  ~Day2() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "2"; }

  LL DoWork1()
  {
    LL ret = 0;
    for (auto d : mData)
    {
      int mine   = d[2] - 'X';
      int theirs = d[0] - 'A';

      bool isWin = mine == (theirs + 1) % 3;

      ret += (mine + 1) + (isWin ? 6 : (mine == theirs ? 3 : 0));
    }
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;
    for (auto d : mData)
    {
      int strategy = d[2] - 'X';
      int theirs   = d[0] - 'A';

      bool isWin  = strategy == 2;
      bool isLose = strategy == 0;

      int mine = theirs;
      if (isWin)
        mine = (theirs + 1) % 3;
      else if (isLose)
      {
        mine = theirs - 1;
        if (mine == -1)
          mine = 2;
      }

      ret += (mine + 1) + (isWin ? 6 : (mine == theirs ? 3 : 0));
    }
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
    mCurrentInput = "input";
    assert(Part1() == "11475");
    assert(Part2() == "16862");
    return true;
  }
};
