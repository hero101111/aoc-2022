#pragma once

#include "SolutionDay.h"

struct ListItem
{
private:
  string           value;
  vector<ListItem> children;

  strong_ordering operator<=>(const ListItem & b)
  {
    auto & a = *this;
    if (a.IsNumber() && b.IsNumber())
    {
      return stoi(a.value) <=> stoi(b.value);
    }
    else if (a.IsNumber() ^ b.IsNumber())
    {
      return b.IsNumber() ? (a <=> ListFromValue(b.value)) : (ListFromValue(a.value) <=> b);
    }
    else
    {
      for (int sweepIndex = 0;; sweepIndex++)
      {
        if (sweepIndex >= min(a.children.size(), b.children.size()))
          return a.children.size() <=> b.children.size();

        auto order = a.children[sweepIndex] <=> b.children[sweepIndex];
        if (order != strong_ordering::equal)
          return order;
      }
    }
    return strong_ordering::less;
  }

public:
  ListItem() {}

  ListItem(string number) { value = number; }

  bool IsNumber() const { return !value.empty(); }

  static ListItem ListFromValue(ListItem aChild)
  {
    ListItem ret;
    ret.children.push_back(aChild);
    return ret;
  }

  static ListItem FromString(string aString)
  {
    stack<ListItem> itemStack;

    size_t sweepIndex = 0;
    while (true)
    {
      char c = aString[sweepIndex];
      if (c == '[')
      {
        itemStack.push(ListItem());
      }
      else if (c == ']')
      {
        if (!itemStack.empty())
        {
          auto child = itemStack.top();
          itemStack.pop();
          if (!itemStack.empty())
          {
            auto & parent = itemStack.top();
            parent.children.push_back(child);
          }
          else
          {
            return child;
          }
        }
      }
      else if (isdigit(c))
      {
        size_t numberEndIndex = sweepIndex;
        while (isdigit(aString[numberEndIndex]))
          numberEndIndex++;
        string numberStr = aString.substr(sweepIndex, numberEndIndex - sweepIndex);
        assert(!itemStack.empty());
        auto & parent = itemStack.top();
        auto   child  = ListItem(numberStr);
        parent.children.push_back(child);
        sweepIndex = numberEndIndex - 1;
      }
      sweepIndex += 1;
    }
  }

  string ToString()
  {
    string ret = "[";
    if (value.empty())
    {
      for (auto c : children)
      {
        if (ret.size() > 1)
          ret += ",";
        ret += c.ToString();
      }
    }
    else
    {
      return value;
    }
    ret += "]";
    return ret;
  }

  bool operator<(const ListItem & b) { return strong_ordering::less == *this <=> b; }
};

class Day13 : public ISolutionDay
{
public:
  Day13() {}

  ~Day13() override {}

  string GetDay() override { return "13"; }

  LL DoWork1()
  {
    auto pairs = rffv(GetInputPath());

    int index = 1;
    LL  ret   = 0;
    for (auto p : pairs)
    {
      bool rightOrder = ListItem::FromString(p[0]) < ListItem::FromString(p[1]);
      if (rightOrder)
        ret += index;
      index += 1;
    }
    return ret;
  }

  LL DoWork2()
  {
    auto             pairs = rffv(GetInputPath());
    vector<ListItem> items;

    for (auto p : pairs)
    {
      auto first  = ListItem::FromString(p[0]);
      auto second = ListItem::FromString(p[1]);
      items.push_back(first);
      items.push_back(second);
    }
    items.push_back(ListItem::FromString("[[2]]"));
    items.push_back(ListItem::FromString("[[6]]"));

    sort(begin(items), end(items));

    int index = 1;
    LL  ret   = 1;
    for (auto & d : items)
    {
      string dStr = d.ToString();
      if (dStr == "[[2]]" || dStr == "[[6]]")
        ret *= index;

      index += 1;
    }

    return ret;
  }

  string Part1() override { return std::to_string(DoWork1()); }

  string Part2() override { return std::to_string(DoWork2()); }

  bool Test() override
  {
    mCurrentInput = "test";
    aoc_assert(Part1(), "13"s);
    aoc_assert(Part2(), "140"s);
    mCurrentInput = "input";
    aoc_assert(Part1(), "6369"s);
    aoc_assert(Part2(), "25800"s);

    return true;
  }
};
