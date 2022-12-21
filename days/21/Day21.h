#pragma once

#include "SolutionDay.h"

class Day21 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day21() {}

  ~Day21() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "21"; }

  LL DoWork1()
  {
    map<string, string> mE;
    map<string, LL>     mV;
    for (auto d : mData)
    {
      auto [mon, exp] = split(d, ':');
      mE[mon]         = trim(exp);
    }

    for (auto [m, e] : mE)
    {
      bool isNumber = true;
      for (auto c : e)
        if (!isdigit(c))
          isNumber = false;
      if (!isNumber)
        continue;
      mV[m] = stoll(e);
    }

    while (true)
    {
      bool found = false;

      for (auto [m, e] : mE)
      {
        if (e.size() < 4)
          continue;
        if (mV.find(m) != end(mV))
          continue;

        auto [left, op, right] = RegExMatch3(e, R"((\w+) (.) (\w+))");
        LL l{}, r{};
        if (mV.find(left) != end(mV))
          l = mV[left];
        else
          continue;
        if (mV.find(right) != end(mV))
          r = mV[right];
        else
          continue;

        LL res = 0;
        if (op == "+")
          res = l + r;
        if (op == "-")
          res = l - r;
        if (op == "*")
          res = l * r;
        if (op == "/")
          res = l / r;

        if (m == "root")
          res = l == r;

        found = true;

        mV[m] = res;
      }
      if (!found)
        break;
    }
    LL ret = mV["root"];
    return ret;
  }

  string DoWork2()
  {
    map<string, string> mE;
    map<string, string> mExp;

    for (auto d : mData)
    {
      auto [mon, exp] = split(d, ':');
      mE[mon]         = trim(exp);
    }

    for (auto [m, e] : mE)
    {
      bool isNumber = true;
      for (auto c : e)
        if (!isdigit(c))
          isNumber = false;
      if (!isNumber)
        continue;
      mExp[m] = e;
    }

    mExp["humn"] = "X";

    while (true)
    {
      bool found = false;

      for (auto [m, e] : mE)
      {
        if (e.size() < 4)
          continue;
        if (mExp.find(m) != end(mExp))
          continue;

        auto [left, op, right] = RegExMatch3(e, R"((\w+) (.) (\w+))");
        string l{}, r{};
        if (mExp.find(left) != end(mExp))
          l = mExp[left];
        else
          continue;
        if (mExp.find(right) != end(mExp))
          r = mExp[right];
        else
          continue;

        if (m == "root")
          op = "==";

        bool isDirty = false;
        if (l.find("X") != string::npos)
          isDirty = true;
        if (r.find("X") != string::npos)
          isDirty = true;

        string exp;
        if (!isDirty)
        {
          if (op == "+")
            exp = to_string(stoll(l) + stoll(r));
          if (op == "-")
            exp = to_string(stoll(l) - stoll(r));
          if (op == "*")
            exp = to_string(stoll(l) * stoll(r));
          if (op == "/")
            exp = to_string(stoll(l) / stoll(r));
        }
        else
        {
          exp = "("s + l + " " + op + " " + r + ")"s;
        }

        if (m == "root")
        {
          return exp;
        }
        else
        {
          assert(!exp.empty());
          mExp[m] = exp;
        }

        found = true;
      }
      if (!found)
        break;
    }

    return "";
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return DoWork2();
  }

  bool Test() override
  {
    mCurrentInput = "test";
    // aoc_assert(Part1() != "");
    // aoc_assert(Part2() != "");
    return true;
  }
};
