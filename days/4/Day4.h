#pragma once

#include "SolutionDay.h"

class Day4 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day4(){ }

  ~Day4() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "4";
  }

  LL DoWork1()
  {
    LL ret = 0;
    
    for (auto d : mData)
    {
      auto [a1, a2, b1, b2] = tuple_toll(RegExMatch4(d, R"((-?\d+)-(-?\d+),(-?\d+)-(-?\d+))"));
      if (b1 >= a1 && b2 <= a2)
        ret++;
      else if (a1 >= b1 && a2 <= b2)
        ret++;
    }
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;

    for (auto d : mData)
    {
      auto [a1, a2, b1, b2] = tuple_toll(RegExMatch4(d, R"((-?\d+)-(-?\d+),(-?\d+)-(-?\d+))"));
      if (b1 >= a1 && b1 <= a2)
        ret++;
      else if (a1 >= b1 && a1 <= b2)
        ret++;

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
    mCurrentInput = "test";
   // assert(Part1() != "");
   // assert(Part2() != "");
    return true;
  }
};
