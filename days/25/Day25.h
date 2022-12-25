#pragma once

#include "SolutionDay.h"

class Day25 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day25() {}

  ~Day25() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "25"; }

  LL toBaseDec(string snafuN)
  {
    LL ret = 0;

    LL pw = 0;
    for (auto it = snafuN.rbegin(); it != snafuN.rend(); it++)
    {
      LL pw5 = pow(5, pw);
      LL digit;
      if (isdigit(*it))
        digit = stoll(""s + *it);
      else if (*it == '=')
        digit = -2;
      else if (*it == '-')
        digit = -1;
      ret += pw5 * digit;
      pw++;
    }
    return ret;
  }

  string toBaseSNAFU(LL decN)
  {
    string ret;

    if (decN == 0)
      return "";
    else
      switch (decN % 5)
      {
      case 0:
        return toBaseSNAFU(decN / 5) + "0";
      case 1:
        return toBaseSNAFU(decN / 5) + "1";
      case 2:
        return toBaseSNAFU(decN / 5) + "2";
      case 3:
        return toBaseSNAFU((decN + 2) / 5) + "=";
      case 4:
        return toBaseSNAFU((decN + 2) / 5) + "-";
      }
    return ret;
  }

  string DoWork()
  {
    LL sum = 0;
    for (auto d : mData)
    {
      sum += toBaseDec(d);
    }

    string ret = toBaseSNAFU(sum);
    return ret;
  }

  string Part1() override
  {
    ReadData();

    return DoWork();
  }

  string Part2() override
  {
    ReadData();

    return "MERRY CHRISTMAS"s;
  }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "2-121-=10=200==2==21"s);
    aoc_assert(Part2(), "MERRY CHRISTMAS"s);
    return true;
  }
};
