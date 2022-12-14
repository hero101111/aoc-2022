#pragma once

#include "SolutionDay.h"

class Day14 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day14() {}

  ~Day14() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "14"; }

  LL DoWork(bool isPartOne)
  {
    DynamicMap<char> m;
    for (auto d : mData)
    {
      auto tokens = RegExMatchN(d, R"(\d+,\d+)");
      Point p{-1, -1};
      for (auto t : tokens)
      {
        auto [x,y] = split(t, ',');
        Point newPoint{x, y};
        m[newPoint] = '#';
        if (p != Point{-1, -1})
        {
          auto path = p.GetTo(newPoint);
          for (auto pathP : path)
            m[pathP] = '#';
        }
        p = newPoint;
      }
    }
    
    // generate floor (needed for part2
    LL maxY = m.max_y + 2;
    
   // m.printf();
    Point sandOrigin{500, 0};
    Point sand;
    bool shouldEmitSand{ true };
    int totalSand {0};
    int sandRest {0};
    while (true)
    {
      if (shouldEmitSand)
      {
        // emit sand
        sand = sandOrigin;
        shouldEmitSand = false;
        m[sand] = 'o';
        totalSand++;
      }
      else
      {
        bool foundWay{false};
        for (Point diffP : {Point{0, 1}, Point{-1, 1}, Point{1, 1}})
        {
          Point cand = sand + diffP;
          if (m[cand] != '#' && m[cand] != 'o' && (isPartOne ? true : (cand.y < maxY)))
          {
            m[sand] = '.';
            sand = cand;
            m[sand] = 'o';
            foundWay = true;
            if (isPartOne && sand.y >= 500)
              return sandRest;
            
            break;
          }
        }
        if (!foundWay)
        {
          sandRest++;
          
          if (sand == sandOrigin)
          {
            return sandRest;
          }
        
          shouldEmitSand = true;
        }
      }
    }
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  bool Test() override
  {
    mCurrentInput = "test";
    aoc_assert(Part1(), "24"s);
    aoc_assert(Part2(), "93"s);
    mCurrentInput = "input";
    aoc_assert(Part1(), "655"s);
    aoc_assert(Part2(), "26484"s);
    return true;
  }
};
