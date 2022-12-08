#pragma once

#include "SolutionDay.h"

class Day8 : public ISolutionDay
{
private:

  DynamicMap<LL> mMap;
  
public:

  Day8(){ }

  ~Day8() override { }

  void ReadData()
  {
    mMap.fromfile(GetInputPath(), [](char c)->LL{ return c - '0'; });
  }
  
  string GetDay() override
  {
    return "8";
  }
  
  LL DoWork1()
  {
    return mMap.for_each([&](Point p, LL)
    {
      for (auto dir : WalkDirections)
      {
        vector<Point> walk = mMap.walkToBorder(p, dir);
        walk.erase(begin(walk));
        
        if (end(walk) == find_if(begin(walk), end(walk), [&](Point w){ return mMap[w] >= mMap[p]; }))
          return true;
      }
      return false;
    });
  }

  LL DoWork2()
  {
    auto getScenicScore = [&](Point p)
    {
      LL ret = 1;
      
      for (auto dir : WalkDirections)
      {
        vector<Point> walk = mMap.walkToBorder(p, dir);
        walk.erase(begin(walk));
        LL factor = 0;
        for (Point q : walk)
        {
          factor++;
          if (mMap[q] >= mMap[p])
            break;
        }
        ret *= factor;
      }
      
      return ret;
    };
    
    LL maxScore = -1;
    mMap.for_each([&](Point p, LL v)
    {
      maxScore = max(maxScore, getScenicScore(p));
      return true;
    });
    
    return maxScore;
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
    assert(Part1() == "21");
    assert(Part2() == "8");
    mCurrentInput = "input";
    assert(Part1() == "1690");
    assert(Part2() == "535680");
    return true;
  }
};
