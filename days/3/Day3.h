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
    LL ret = 0;
    for (auto d : mData)
    {
      set<char> left, right;
      size_t n = d.size();
      for (int i = 0; i < n; ++i)
      {
        if (i < n / 2)
          left.insert(d[i]);
        else
          right.insert(d[i]);
      }
      
      set<char> inter;
      for (auto c : left)
        if (right.find(c) != end(right))
          inter.insert(c);
      
      LL val = 0;
      for (auto c : inter)
      {
        if (c >= 'A' and c <= 'Z')
          val = c - 'A' + 27;
        else
          val = c - 'a'+ 1;
      }
      ret += val;
    }
    
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 0;
    for (int i = 0; i < mData.size() - 1; i += 3)
    {
      set<char> s1, s2, s3;
      for (auto c : mData[i])
        s1.insert(c);
      for (auto c : mData[i + 1])
        s2.insert(c);
      for (auto c : mData[i + 2])
        s3.insert(c);
      
      set<char> inter;
      for (auto c : s1)
        if (s2.find(c) != end(s2) && s3.find(c) != end(s3))
          inter.insert(c);
      
      LL val = 0;
      for (auto c : inter)
      {
        if (c >= 'A' and c <= 'Z')
          val = c - 'A' + 27;
        else
          val = c - 'a'+ 1;
      }
      ret += val;
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
    assert(Part1() == "7824");
    assert(Part2() == "2798");
    return true;
  }
};
