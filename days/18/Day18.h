#pragma once

#include "SolutionDay.h"

class Day18 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day18() {}

  ~Day18() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "18"; }

  LL DoWork1()
  {
    LL                   ret = 0;
    unordered_set<Point> cubes;

    for (auto d : mData)
    {
      auto  coord = tok(d, ',');
      Point p{ coord[0], coord[1], coord[2] };

      cubes.insert(p);
    }
    vector<Point> neigh;
    for (auto x : rangeint(-1, 1))
      for (auto y : rangeint(-1, 1))
        for (auto z : rangeint(-1, 1))
        {
          if (abs(x) + abs(y) + abs(z) == 1)
            neigh.push_back(Point{ x, y, z });
        }

    unordered_map<Point, int> faces;
    for (auto c : cubes)
    {
      for (auto n : neigh)
      {
        auto cn = c + n;
        if (!contains(cubes, cn))
          ret += 1;
      }
    }

    return ret;
  }

  LL DoWork2()
  {
    LL                   ret = 0;
    unordered_set<Point> cubes;

    Point maxP{ numeric_limits<LL>::min(), numeric_limits<LL>::min(), numeric_limits<LL>::min() };
    Point minP{ numeric_limits<LL>::max(), numeric_limits<LL>::max(), numeric_limits<LL>::max() };
    for (auto d : mData)
    {
      auto  coord = tok(d, ',');
      Point p{ coord[0], coord[1], coord[2] };

      cubes.insert(p);
      for (int i : rangeint(0, 2))
      {
        minP[i] = min(minP[i], p[i]);
        maxP[i] = max(maxP[i], p[i]);
      }
    }
    vector<Point> neigh;
    for (auto x : rangeint(-1, 1))
      for (auto y : rangeint(-1, 1))
        for (auto z : rangeint(-1, 1))
        {
          if (abs(x) + abs(y) + abs(z) == 1)
            neigh.push_back(Point{ x, y, z });
        }

    auto InRange = [&](Point p)
    {
      for (auto i : rangeint(0, 2))
      {
        if (p[i] < minP[i] - 1)
          return false;
        if (p[i] > maxP[i] + 1)
          return false;
      }
      return true;
    };

    auto isActive = [&](Point p)
    {
      return cubes.find(p) == end(cubes);
    };

    Point startCube{ minP.x - 1, minP.y - 1, minP.z - 1 };

    unordered_set<Point> lavaFilledCubes;
    queue<Point>         cubesToProcess;
    cubesToProcess.push(startCube);
    lavaFilledCubes.insert(startCube);
    Point currentCube;
    int   neighCube;
    while (!cubesToProcess.empty())
    {
      currentCube = cubesToProcess.front();
      cubesToProcess.pop();
      for (auto offset : neigh)
      {
        auto neighCell = currentCube + offset;
        if (InRange(neighCell))
        {
          if (isActive(neighCell) && lavaFilledCubes.find(neighCell) == lavaFilledCubes.end())
          {
            cubesToProcess.push(neighCell);
            lavaFilledCubes.insert(neighCell);
          }
        }
      }
    }

    /*
    // debugging, to check correct total volume of fill algorithm
    LL cube = 1;
    for (auto i : rangeint(0, 2))
      cube *= maxP[i] - minP[i] + 3;*/

    LL val{ 0 };
    for (auto c : cubes)
    {
      for (auto n : neigh)
      {
        auto cn = c + n;
        if (lavaFilledCubes.find(cn) != end(lavaFilledCubes))
          val++;
      }
    }
    return val;
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
    aoc_assert(Part1(), "64"s);
    aoc_assert(Part2(), "58"s);
    mCurrentInput = "input";
    aoc_assert(Part1(), "3412"s);
    aoc_assert(Part2(), "2018"s);
    return true;
  }
};
