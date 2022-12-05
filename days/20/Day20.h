#pragma once

#include "SolutionDay.h"

class Day20 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day20(){ }

  ~Day20() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "20";
  }

  LL DoWork1()
  {
    LL ret = 201;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 202;
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
    //assert(Part1() != "");
    //assert(Part2() != "");
    return true;
  }
};
