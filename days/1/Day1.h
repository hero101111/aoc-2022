#pragma once

#include "SolutionDay.h"

class Day1 : public ISolutionDay
{
private:

  vector<LL> mElfs;

public:

  Day1(){ }

  ~Day1() override { }

  void ReadData()
  {
    vector<string> data = rff(GetInputPath());
    LL crt = 0;
    for (auto crtS : data)
    {
      if (crtS.size() > 0)
        crt += stoll(crtS);
      else
      {
        mElfs.push_back(crt);
        crt = 0;
      }
    }
    if (crt > 0)
      mElfs.push_back(crt);
  }
  
  string GetDay() override
  {
    return "1";
  }

  LL DoWork1()
  {
    return *max_element(begin(mElfs), end(mElfs));
  }

  LL DoWork2()
  {
    nth_element(begin(mElfs), begin(mElfs) + 2, end(mElfs), greater<LL>());
    return reduce(begin(mElfs), begin(mElfs) + 3, 0, [](LL a, LL b){ return a + b;});
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
