#pragma once

#include "SolutionDay.h"

struct Monkey
{
  LL       id;
  list<LL> items;
  char     op;
  bool     opIsSquared{ false };
  LL       opAmmount;
  LL       disibleBy;
  LL       throwTrue;
  LL       throwFalse;
};

class Day11 : public ISolutionDay
{
private:
  vector<Monkey> monkeys;
  vector<LL>     inspect;

public:
  Day11() {}

  ~Day11() override {}

  void ReadData()
  {
    monkeys.clear();
    inspect.clear();
    auto monkeyData = rffv(GetInputPath());

    for (auto d : monkeyData)
    {
      Monkey m;
      m.id                 = d[0][7] - '0';
      string startingItems = d[1];
      auto [_, sItems]     = split(startingItems, ':');
      auto itemNumbers     = tok(sItems, ',');
      for (auto item : itemNumbers)
        m.items.insert(end(m.items), stoll(trim(item)));
      string operationStr = d[2];
      if (operationStr == "  Operation: new = old * old")
      {
        m.opIsSquared = true;
      }
      else
      {
        char   op        = operationStr[23];
        string opAmmount = operationStr.substr(24);
        m.op             = op;
        m.opAmmount      = stoll(opAmmount);
      }
      string divBy      = d[3].substr(21);
      m.disibleBy       = stoll(divBy);
      string throwTrue  = d[4].substr(29);
      m.throwTrue       = stoll(throwTrue);
      string throwFalse = d[5].substr(30);
      m.throwFalse      = stoll(throwFalse);
      monkeys.push_back(m);
      inspect.push_back(0);
    }
  }

  string GetDay() override { return "11"; }

  LL DoWork(bool isPartOne)
  {
    LL tmod = 1;
    if (!isPartOne)
      for (auto & m : monkeys)
        tmod *= m.disibleBy;

    int round = 0;
    while (true)
    {
      for (int i : rangeint(0, monkeys.size() - 1))
      {
        auto & monkey = monkeys[i];
        for (auto it = monkey.items.begin(); it != monkey.items.end();)
        {
          inspect[i]++;
          LL   worry    = *it;
          auto newWorry = worry;

          if (monkey.opIsSquared)
          {
            newWorry = worry * worry;
          }
          else if (monkey.op == '+')
            newWorry = worry + monkey.opAmmount;
          else if (monkey.op == '*')
          {
            newWorry = worry * monkey.opAmmount;
          }
          else
            assert(!"Unsupported");

          if (isPartOne)
          {
            double newWorryDbl = newWorry;
            newWorryDbl /= 3ll;
            newWorry = newWorryDbl;
          }
          else
            newWorry = newWorry % tmod;

          bool test    = (newWorry % monkey.disibleBy) == 0ull;
          auto throwTo = test ? monkey.throwTrue : monkey.throwFalse;
          monkeys[throwTo].items.insert(monkeys[throwTo].items.end(), newWorry);

          auto toRemove = it;
          it++;
          monkey.items.erase(toRemove);
        }
      }
      round++;
      if (round == 20)
      {
        int i = 0;
        ++i;
      }
      if (round == (isPartOne ? 20 : 10000))
        break;
    }
    sort(begin(inspect), end(inspect), greater<LL>());

    LL ret = inspect[0] * inspect[1];
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
    assert(Part1() == "110264");
    assert(Part2() == "23612457316");
    return true;
  }
};
