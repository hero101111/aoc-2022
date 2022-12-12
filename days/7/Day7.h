#pragma once

#include "SolutionDay.h"

struct Item
{
  bool   isDir{ false };
  string name;
  LL     size{ 0 };

  LL getTotalSize()
  {
    LL ret = size;
    for (auto [name, child] : children)
      ret += child->getTotalSize();

    return ret;
  }

  map<string, Item *> children;
  Item *              parent{ nullptr };
};

class Day7 : public ISolutionDay
{
private:
public:
  vector<Item> mDiskItems;

  Day7() {}

  ~Day7() override {}

  void ReadData()
  {
    mDiskItems.clear();

    vector<string> mData = rff(GetInputPath());

    mDiskItems.reserve(mData.size());

    Item * crtDir{ nullptr };

    for (auto d : mData)
    {
      if (d[0] == '$' && d[2] == 'c' && d[3] == 'd')
      {
        string newDirName = d.substr(5);

        if (newDirName == "..")
        {
          crtDir = crtDir->parent;
        }
        else
        {
          bool foundAsChild = false;
          if (crtDir)
          {
            const auto foundChild = (crtDir->children).find(newDirName);
            if (foundChild != end(crtDir->children))
            {
              foundAsChild = true;
              crtDir       = foundChild->second;
            }
          }

          if (!foundAsChild)
          {
            mDiskItems.push_back(Item());
            Item * newItem  = &mDiskItems.back();
            newItem->name   = newDirName;
            newItem->parent = crtDir;
            newItem->isDir  = true;
            if (crtDir)
              crtDir->children[newDirName] = newItem;

            crtDir = newItem;
          }
        }
      }
      else if (isdigit(d[0]))
      {
        assert(crtDir);
        auto [sizeStr, itemName] = RegExMatch2(d, R"((\d+) (.+))");

        Item * newItem{ nullptr };
        for (auto [name, child] : crtDir->children)
        {
          if (child->name == itemName)
          {
            newItem = child;
            break;
          }
        }

        if (newItem == nullptr)
        {
          mDiskItems.push_back(Item());
          newItem                    = &mDiskItems.back();
          newItem->name              = itemName;
          newItem->parent            = crtDir;
          newItem->isDir             = false;
          crtDir->children[itemName] = newItem;
        }
        LL sizeN      = stoll(sizeStr);
        newItem->size = sizeN;
      }
    }
  }

  string GetDay() override { return "7"; }

  LL DoWork1()
  {
    LL ret = 0;

    for (auto i : mDiskItems)
    {
      if (i.isDir)
      {
        LL itemSize = i.getTotalSize();
        if (itemSize <= 100000)
          ret += itemSize;
      }
    }

    return ret;
  }

  LL DoWork2()
  {
    LL totalSize = mDiskItems[0].getTotalSize();
    LL available = 70000000 - totalSize;
    LL toFree    = 30000000 - available;

    vector<LL> candidates;

    for (auto i : mDiskItems)
    {
      if (i.isDir)
      {
        LL itemSize = i.getTotalSize();

        if (itemSize != totalSize)
          candidates.push_back(itemSize);
      }
    }

    sort(begin(candidates), end(candidates));
    for (auto c : candidates)
    {
      if (c >= toFree)
      {
        return c;
      }
    }
    return 0;
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
    aoc_assert(Part1(), "95437"s);
    aoc_assert(Part2(), "24933642"s);

    mCurrentInput = "input";
    aoc_assert(Part1(), "1989474"s);
    aoc_assert(Part2(), "1111607"s);
    return true;
  }
};
