#pragma once

#include "SolutionDay.h"

struct ListItem
{
  string value;
  vector<ListItem> children;
  
  ListItem()
  {    
  }
  
  ListItem(string number)
  {
    value = number;
  }
  
  string toString()
  {
    string ret = "[";
    if (value.empty())
    {
      for (auto c : children)
      {
        if (ret.size() > 1)
          ret += ",";
        ret += c.toString();
      }
    }
    else
    {
      return value;
    }
    ret += "]";
    return ret;
  }
};

class Day13 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day13() {}

  ~Day13() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "13"; }
  
  ListItem parseStr(string s)
  {
    vector<ListItem> q;
    q.reserve(1000);
    
    size_t i = 0, pi = 0;
    while (true)
    {
      char c = s[i];
      if (c == '[')
      {
        q.push_back(ListItem());
        pi = i + 1;
      }
      else if (c == ']')
      {
        string piStr = s.substr(pi, i - pi);
        if (piStr != "")
        {
          assert(!q.empty());
          auto & parent = q.back();
          auto child = ListItem(piStr);
          parent.children.push_back(child);
        }
        
        if (!q.empty())
        {
          auto child = q.back();
          q.erase(q.end() - 1);
          if (!q.empty())
          {
            auto & parent = q.back();
            parent.children.push_back(child);
          }
          else
          {
            return child;
          }
          pi = i + 1;
        }
      }
      else if (c == ',')
      {
        string piStr = s.substr(pi, i - pi);
        if (piStr != "]" && piStr != "")
        {
          assert(!q.empty());
          auto & parent = q.back();
          auto child = ListItem(piStr);
          parent.children.push_back(child);
        }
        pi = i + 1;
      }
      i += 1;
    }
    
  }
  
  bool isRightOrder(const ListItem & a, const ListItem & b, bool & cont)
  {
    bool ret = true;
    if (!a.value.empty() && !b.value.empty())
    {
      if (stoi(a.value) < stoi(b.value))
        return true;
      else if (stoi(a.value) > stoi(b.value))
        return false;
      else cont = true;
    }
    else if (a.value.empty() && !b.value.empty())
    {
      ListItem foo;
      foo.children.push_back(ListItem(b.value));
      return isRightOrder(a, foo, cont);
    }
    else if (b.value.empty() && !a.value.empty())
    {
      ListItem foo;
      foo.children.push_back(ListItem(a.value));
      return isRightOrder(foo, b, cont);
    }
    else
    {
      int aIndex = 0, bIndex = 0;
      while (true)
      {
        if (a.children.size() + b.children.size() == 0)
        {
          cont = true;
          return true;
        }
        if (aIndex >= a.children.size() && bIndex >= b.children.size())
        {
          cont = true;
          return true;
        }
        if (aIndex >= a.children.size())
          return true;
        if (bIndex >= b.children.size())
          return false;
        auto itemA = a.children[aIndex];
        auto itemB = b.children[bIndex];
        bool cont = false;
        bool rightOrder = isRightOrder(itemA, itemB, cont);
        if (!cont && !rightOrder)
          return false;
        if (!cont && rightOrder)
          return true;
        
        aIndex++;
        bIndex++;
      }
    }
    return true;
  };
  
  bool isLessThan(const ListItem & a, const ListItem & b)
  {
    bool cont{false};
    return isRightOrder(a, b, cont);
  }

  LL DoWork1()
  {
    auto pairs = rffv(GetInputPath());
  
    int index = 1;
    LL ret = 0;
    for (auto d : pairs)
    {
      auto first = parseStr(d[0]);
      auto second = parseStr(d[1]);
      
      auto firstString = first.toString();
      auto secondString = second.toString();
      
      assert(d[0] == firstString);
      assert(d[1] == secondString);
      
      if (index == 3)
      {
        int i = 0;
      }
      bool rightOrder = isLessThan(first, second);
      if (rightOrder)
      {
        ret += index;
        //fprintf(KVERBOSE, d[0] + "\n"s + d[1] + "\n\n"s, true);
      }
      else
      {
        int i = 0;
        //isRightOrder(first, second);
      }
      index+=1;
    }
    return ret;
  }

  LL DoWork2()
  {
    auto pairs = rffv(GetInputPath());
    vector<ListItem> items;
    
    for (auto d : pairs)
    {
      auto first = parseStr(d[0]);
      auto second = parseStr(d[1]);
      items.push_back(first);
      items.push_back(second);
    }
    items.push_back(parseStr("[[2]]"));
    items.push_back(parseStr("[[6]]"));
    
    for (int i = 0; i < items.size() - 1; ++i)
      for (int j = i + 1; j < items.size(); ++j)
      {
        auto a = items[i];
        auto b = items[j];
        
        if (!isLessThan(a, b))
        {
          items[i] = b;
          items[j] = a;
        }
      }
    
    auto z1 = parseStr("[9]");
    auto z2 = parseStr("[[6]]");
    auto isValid = isLessThan(z1, z2);
    
    for (int i = 0; i < items.size() - 1; ++i)
    {
      for (int j = i + 1; j < items.size(); ++j)
        assert(isLessThan(items[i], items[j]));
    }
    //sort(begin(items), end(items), [&](const ListItem & a, const ListItem & b){ return isLessThan(a, b);});
    
    fprintf(KVERBOSE, "");
    
    int index = 1;
    LL ret = 1;
    for (auto & d : items)
    {
      string dStr = d.toString();
      fprintf(KVERBOSE, dStr, true);
      if (dStr == "[[2]]" || dStr == "[[6]]")
        ret *= index;
      
      index += 1;
    }
    
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
    mCurrentInput = "test";
    aoc_assert(Part1(), "13"s);
    aoc_assert(Part2(), "140"s);
    mCurrentInput = "input";
    aoc_assert(Part1(), "6369"s);
    aoc_assert(Part2(), "25800"s)
    
    
    return true;
  }
};
