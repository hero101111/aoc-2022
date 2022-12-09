#pragma once

#include "SolutionDay.h"

class Day9 : public ISolutionDay
{
private:

  vector<string> mData;

public:

  Day9(){ }

  ~Day9() override { }

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "9";
  }
  
  bool AreTouching(Point head, Point tail)
  {
    return head.ChebyshevDist(tail) <= 1;
  }

  LL DoWork(int n)
  {
    set<Point> vis;
    vector<Point> knots(n);
    
    for (auto d : mData)
    {
      vis.insert(knots.back());
      
      auto [dir, lenStr] = RegExMatch2(d, R"((\w) (\d+))");
      LL len = stoll(lenStr);
      
      while (len-- > 0)
      {
        vis.insert(knots.back());
        
        auto & head = knots[0];
        head = head.FromDirection(dir[0]);
        
        for (auto it : rangeint(1, knots.size() - 1))
        {
          auto head = knots[it - 1];
          auto & tail = knots[it];
          
          if (AreTouching(head, tail))
            continue;
          
          tail.y += (head.y <=> tail.y)._Value;
          tail.x += (head.x <=> tail.x)._Value;
        }
      }
    }
    
    vis.insert(knots.back());
    LL ret = vis.size();
    return ret;
  }
  
  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(2));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(10));
  }

  bool Test() override
  {
    mCurrentInput = "input";
    assert(Part1() == "6190");
    assert(Part2() == "2516");
    return true;
  }
};
