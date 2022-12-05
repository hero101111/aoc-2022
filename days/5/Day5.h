#pragma once

#include "SolutionDay.h"

class Day5 : public ISolutionDay
{
private:
  
  vector<string> mData;
  
public:
  
  Day5(){ }
  
  ~Day5() override { }
  
  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }
  
  string GetDay() override
  {
    return "5";
  }
  
  string DoWork(bool isPartOne)
  {
    string ret = "";
    
    int minN = 1, maxN = 9;
    
    map<int, int> indices;
    for (int i : rangeint(minN, maxN))
      indices[i] = 1 + (i - 1) * 4;
    
    map<int, vector<char>> data;
    
    for (auto d : mData)
    {
      if (d.size() > 1 && d[0] == '[')
      {
        for (int i : rangeint(minN, maxN))
        {
          char c = d[indices[i]];
          if (c != ' ')
            data[i].insert(begin(data[i]), c);
        }
      }
      if (d.size() < 1 || d[0] != 'm')
        continue;
      
      auto [many, from, to] = tuple_toll(RegExMatch3(d, R"(move (\d+) from (\d+) to (\d+))"));
      
      vector<char> temp;
      while (many > 0)
      {
        if (!data[from].empty())
        {
          auto t = data[from].back();
          
          if (isPartOne)
            temp.push_back(t);
          else
            temp.insert(begin(temp), t);
          
          data[from].erase(data[from].end() - 1);
        }
        many -= 1;
      }
      
      for (auto c : temp)
        data[to].push_back(c);
    }
    for (LL i : rangeint(minN, maxN))
      ret += data[i].back();
    
    return ret;
  }
  
  LL DoWork2()
  {
    LL ret = 52;
    return ret;
  }
  
  string Part1() override
  {
    ReadData();
    
    return DoWork(true);
  }
  
  string Part2() override
  {
    ReadData();
    
    return DoWork(false);
  }
  
  bool Test() override
  {
    mCurrentInput = "test";
    //assert(Part1() != "");
    //assert(Part2() != "");
    return true;
  }
};
