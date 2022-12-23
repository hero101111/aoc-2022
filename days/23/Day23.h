#pragma once

#include "SolutionDay.h"

class Day23 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day23() {}

  ~Day23() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "23"; }

  LL DoWork(bool partTwo)
  {
    DynamicMap<char> m;
    m.fromlines(mData);
    auto isElfAt = [&](Point p)
    {
      return m.isSetAt(p) && m[p] == '#';
    };

    auto noElfAt = [&](Point elf, vector<string> & orientations)
    {
      bool ret = true;
      for (auto o : orientations)
      {
        if (isElfAt(elf.FromOrientation(o)))
          return false;
      }
      return ret;
    };

    vector<pair<vector<string>, string>> considered;
    considered.push_back(make_pair(vector<string>{ "N", "NE", "NW" }, "N"));
    considered.push_back(make_pair(vector<string>{ "S", "SE", "SW" }, "S"));
    considered.push_back(make_pair(vector<string>{ "W", "NW", "SW" }, "W"));
    considered.push_back(make_pair(vector<string>{ "E", "NE", "SE" }, "E"));

    for (int round = 0; partTwo || (round < 10); round++)
    {
      vector<pair<Point, Point>> proposals;

      vector<Point> elfs;

      m.for_each(
        [&](Point elf, char c)
        {
          if (isElfAt(elf))
          {
            elfs.push_back(elf);

            Point proposal;

            bool noNeighs = true;
            auto neigh    = elf.GetNeighbours(1);
            for (auto n : neigh)
              if (isElfAt(n))
                noNeighs = false;
            if (noNeighs)
            {
              // do nothing
            }
            else
            {
              for (auto & [dirs, target] : considered)
              {
                if (noElfAt(elf, dirs))
                {
                  proposals.emplace_back(elf, elf.FromOrientation(target));
                  break;
                }
              }
            }
          }
        });

      auto firstCons = *begin(considered);
      considered.erase(begin(considered));
      considered.push_back(firstCons);

      DynamicMap<char> newM;
      for (auto elf : elfs)
      {
        vector<Point>   otherElfProps;
        optional<Point> myProp;
        for (auto [elf2, prop2] : proposals)
        {
          if (elf2 == elf)
          {
            myProp = prop2;
          }
        }
        if (myProp)
        {
          for (auto [elf2, prop2] : proposals)
          {
            if (prop2 == *myProp && elf != elf2)
            {
              otherElfProps.push_back(elf2);
            }
          }
        }

        if (myProp && otherElfProps.empty())
        {
          newM[*myProp] = '#';
        }
        else
        {
          newM[elf] = '#';
        }
      }

      if (newM == m)
      {
        return round + 1;
      }
      m = newM;

      int i = 0;
    }

    LL ret = 0;
    for (auto x : rangeint(m.min_x, m.max_x))
      for (auto y : rangeint(m.min_y, m.max_y))
      {
        if (m[{ x, y }] != '#')
          ret += 1;
      }
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 232;
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork(false));
  }

  string Part2() override
  {
    ReadData();

    return std::to_string(DoWork(true));
  }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "3877"s);
    aoc_assert(Part2(), "982"s);
    return true;
  }
};
