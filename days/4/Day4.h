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
    LL ret = 41;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 42;
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
    assert(Part1() != "");
    assert(Part2() != "");
    return true;
  }
};
