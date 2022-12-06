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
    mElfs.clear();
    auto data = rffv(GetInputPath());
    for (auto elf : data)
      mElfs.push_back(reduce(begin(elf), end(elf), 0, [](LL a, string b){ return stoll(b) + a; }));
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
    mCurrentInput = "input";
    assert(Part1() == "68775");
    assert(Part2() == "202585");
    return true;
  }
};
