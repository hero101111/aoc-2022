#pragma once

#include "SolutionDay.h"

class Day20 : public ISolutionDay
{
private:
  vector<string> mData;

  struct num
  {
    LL  v;
    int order{ 0 };

    num(LL a, int ord)
      : v(a)
      , order(ord)
    {
    }
  };

public:
  Day20() {}

  ~Day20() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "20"; }

  LL getPos(LL pos, int vSize)
  {
    if (pos < 0)
    {
      pos = -pos % (vSize);
      pos = vSize - pos;
    }
    else
    {
      pos = pos % (vSize);
    }
    return pos;
  }

  LL DoWork(bool partOne)
  {
    list<num> v;

    int t{ 0 };
    for (auto d : mData)
      v.insert(end(v), num(stoll(d) * (partOne ? 1 : 811589153), t++));

    LL ret = 0;

    for (int mix = 0; mix < (partOne ? 1 : 10); mix++)
    {
      int crtNumberToProcessOrder = 0;
      while (true)
      {
        bool found = false;
        int  dist  = 0;
        auto it    = v.begin();
        for (; it != v.end(); ++it, ++dist)
        {
          if (it->order != crtNumberToProcessOrder)
            continue;

          auto order = it->order;
          v.erase(it);

          LL   moveTo   = getPos(dist + it->v, mData.size() - 1);
          auto moveToIt = v.begin();
          advance(moveToIt, moveTo);
          auto inserted = v.insert(moveToIt, num(it->v, order));

          found = true;
          crtNumberToProcessOrder++;

          break;
        }
        if (!found)
          break;
      }
    }

    int  zeroPos = 0;
    auto zero    = v.begin();
    for (; zero != v.end(); ++zero, ++zeroPos)
      if (zero->v == 0)
        break;

    {
      auto it  = v.begin();
      auto pos = getPos(zeroPos + 1000, v.size());
      advance(it, pos);
      ret += it->v;
    }
    {
      auto it  = v.begin();
      auto pos = getPos(zeroPos + 2000, v.size());
      advance(it, pos);
      ret += it->v;
    }
    {
      auto it  = v.begin();
      auto pos = getPos(zeroPos + 3000, v.size());
      advance(it, pos);
      ret += it->v;
    }

    return ret;
  }

  LL DoWork2()
  {
    LL ret = 202;
    return ret;
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
    mCurrentInput = "input";
    aoc_assert(Part1(), "3473"s);
    aoc_assert(Part2(), "7496649006261"s);
    return true;
  }
};
