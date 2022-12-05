#pragma once

#include "SolutionDay.h"

class DayXXX : public ISolutionDay
{
private:

  vector<string> mData;

public:

  DayXXX(){ }

  ~DayXXX() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "XXX";
  }

  LL DoWork1()
  {
    LL ret = XXX1;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = XXX2;
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
