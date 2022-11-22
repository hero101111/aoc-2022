#pragma once

#include "SolutionDay.h"

class Day1 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "1";
  }

  LL DoWork1()
  {
    LL ret = 11;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 12;
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
