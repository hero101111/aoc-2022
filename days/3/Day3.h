#pragma once

#include "SolutionDay.h"

class Day3 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day3(){ }

  ~Day3() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "3";
  }

  LL DoWork1()
  {
    LL ret = 31;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 32;
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
