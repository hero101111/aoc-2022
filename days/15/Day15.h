#pragma once

#include "SolutionDay.h"
#include "z3++.h"

class Day15 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day15() {}

  ~Day15() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "15"; }

  LL DoWork1()
  {
    LL               ret = 0;
    DynamicMap<char> m;

    unordered_set<Point> sensors;
    unordered_set<Point> beacons;
    unordered_set<Point> cannotList;

    z3::context c;
    z3::expr    x = c.int_const("x");
    z3::expr    y = c.int_const("y");
    z3::solver  solver(c);
    solver.add(x >= 0);
    solver.add(x <= 4000000);
    solver.add(y >= 0);
    solver.add(y <= 4000000);

    LL maxy = 2000000;
    for (auto d : mData)
    {
      auto [sx, sy, bx, by] = RegExMatch4(
        d, R"(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))");
      Point s{ sx, sy };
      Point b{ bx, by };

      sensors.insert(s);
      beacons.insert(b);
      auto dist = s.ManhattanDist(b);

      /*for (auto x : rangeint(s.x - dist, s.x + dist + 1))
      {
        if (s.ManhattanDist(Point{ x, maxy }) <= dist)
          cannotList.insert(Point{ x, maxy });
      }*/

      solver.add(z3::abs(x - c.int_val(s.x)) + z3::abs(y - c.int_val(s.y)) > c.int_val(dist));
    }

    // auto diff = getDifference(cannotList, beacons);
    // ret       = diff.size();

    solver.check();
    auto solution = solver.get_model();
    auto retValue = solution.eval(x * 4000000 + y).to_string();
    ret           = stoll(retValue);
    // m.printf();
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 152;
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
    // mCurrentInput = "test";
    // aoc_assert(Part1(), ""s);
    //   aoc_assert(Part2() != "");
    return true;
  }
};
