#pragma once

#include "SolutionDay.h"

using OpenedSet       = set<string>;
using OpenedSetElef   = set<string>;
using OpenedInfoPart1 = pair<LL, OpenedSet>;
using OpenedInfoPart2 = tuple<LL, OpenedSet, OpenedSetElef>;

using Part1HashT    = tuple<string, int, OpenedSet>;
using Part2HashT    = tuple<string, string, int, int, OpenedSet, OpenedSetElef>;
using Part1HashMapT = unordered_map<Part1HashT, OpenedInfoPart1>;
using Part2HashMapT = unordered_map<Part2HashT, OpenedInfoPart2>;

template <>
struct hash<Part1HashT>
{
  auto operator()(const Part1HashT & k) const -> std::size_t
  {
    string s;
    for (auto x : get<2>(k))
      s += x;

    s += get<0>(k) + to_string(get<1>(k));

    return hash<string>()(s);
  }
};

template <>
struct hash<Part2HashT>
{
  auto operator()(const Part2HashT & k) const -> std::size_t
  {
    string s;
    for (auto x : get<5>(k))
      s += x;
    s += "__";
    for (auto x : get<4>(k))
      s += x;

    s += get<0>(k) + "_" + get<1>(k) + to_string(get<2>(k)) + "_" + to_string(get<3>(k));

    return hash<string>()(s);
  }
};

class Day16 : public ISolutionDay
{
private:
  vector<string> mData;

  Graph<string> g{ 60 };

  vector<string>                                               valves;
  vector<string>                                               rightValves;
  unordered_map<string, LL>                                    flows;
  unordered_map<string, unordered_set<string>>                 tunnels;
  unordered_map<string, unordered_map<string, vector<string>>> roads;

  Part1HashMapT hashMap;
  Part2HashMapT cachePart2;

public:
  Day16() {}

  ~Day16() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
    valves.clear();
    rightValves.clear();
    flows.clear();
    tunnels.clear();
    roads.clear();
    hashMap.clear();
    cachePart2.clear();
    g = Graph<string>{ 60 };
  }

  string GetDay() override { return "16"; }

  pair<LL, set<string>> solve(int minute, string node, set<string> opened)
  {
    if (node != "AA" && flows[node] == 0)
    {
      return make_pair(0, opened);
    }

    // assert(minute < 30);

    bool justOpened = false;
    if (!contains(opened, node))
    {
      justOpened = true;
      opened.insert(node);
    }

    /*if (hashMap.find(make_tuple(node, minute, opened)) != end(hashMap))
    {
      cout << "Z " << endl;
      return hashMap[make_tuple(node, minute, opened)];
    }*/

    set<string>           retVisited = opened;
    pair<LL, set<string>> maxRet;
    LL                    max = -1;
    for (auto p : valves)
    {
      if (p != node && opened.find(p) == end(opened))
      {
        auto & road    = roads[node][p];
        LL     newTime = minute + road.size() + 1;
        if (newTime < 30)
        {
          pair<LL, set<string>> v;
          if (hashMap.find(make_tuple(p, newTime, opened)) != end(hashMap))
          {
            // cout << "Z " << endl;
            v = hashMap[make_tuple(p, newTime, opened)];
          }
          else
          {
            v                                       = solve(newTime, p, opened);
            hashMap[make_tuple(p, newTime, opened)] = v;
          }

          if (v.first > max)
          {
            max    = v.first;
            maxRet = v;
          }
        }
      }
    }

    LL crtPressure = 0;

    // auto retOpened = opened;
    if (max > -1)
    {
      // for (auto p : maxRet.second)
      //   retOpened.insert(p);
      crtPressure += max;

      for (auto p : get<1>(maxRet))
        retVisited.insert(p);
    }

    if (justOpened)
    {
      auto fn = flows[node];
      crtPressure += fn * (30 - minute);
    }
    //   hash[make_tuple(node, opened)] = crtPressure;
    return make_pair(crtPressure, retVisited);
  }

  //-------------------------------------------------------------------------------

  OpenedInfoPart2 solve2(int           minute,
                         int           minuteElef,
                         string        node,
                         string        elef,
                         OpenedSet     opened,
                         OpenedSetElef openedElef)
  {
    auto key = make_tuple(node, elef, minute, minuteElef, opened, openedElef);
    if (cachePart2.count(key) > 0)
    {
      return cachePart2[key];
    }

    bool justOpened     = false;
    bool justOpenedElef = false;

    openedElef.insert(elef);
    opened.insert(node);

    OpenedInfoPart2 maxRet;
    for (auto newNode : rightValves)
    {
      if (opened.count(newNode) > 0)
        continue;
      if (openedElef.count(newNode) > 0)
        continue;

      auto & road    = roads[node][newNode];
      LL     newTime = minute + road.size() + 1;

      for (auto newElef : rightValves)
      {
        if (opened.count(newElef) > 0)
          continue;
        if (openedElef.count(newElef) > 0)
          continue;
        if (newElef == newNode)
          continue;

        auto & roadElef    = roads[elef][newElef];
        LL     newTimeElef = minuteElef + roadElef.size() + 1;

        // if (newTime <= 26 && newTimeElef <= 26)
        {
          //  cout << newTime << " " << newTimeElef << endl;
          OpenedInfoPart2 pathPressure =
            solve2(newTime, newTimeElef, newNode, newElef, opened, openedElef);

          if (get<0>(pathPressure) > get<0>(maxRet))
            maxRet = pathPressure;
        }
      }
    }

    LL crtPressure = 0;

    OpenedSet     retVisited     = opened;
    OpenedSetElef retVisitedElef = openedElef;
    // auto retOpened = opened;
    if (get<0>(maxRet) > 0)
    {
      // for (auto p : maxRet.second)
      //   retOpened.insert(p);
      crtPressure += get<0>(maxRet);

      for (auto p : get<1>(maxRet))
        retVisited.insert(p);
      for (auto p : get<2>(maxRet))
        retVisitedElef.insert(p);
    }

    {
      auto fn = flows[node];
      crtPressure += fn * (26 - minute);
    }
    //  if (justOpenedElef)
    {
      auto fn = flows[elef];
      crtPressure += fn * (26 - minuteElef);
    }
    //   hash[make_tuple(node, opened)] = crtPressure;

    key             = make_tuple(node, elef, minute, minuteElef, opened, openedElef);
    cachePart2[key] = make_tuple(crtPressure, retVisited, retVisitedElef);

    return make_tuple(crtPressure, retVisited, retVisitedElef);
  }

  LL DoWork1()
  {
    for (auto d : mData)
    {
      auto [valve, flow, conn] =
        RegExMatch3(d, R"(Valve (.+) has flow rate=(.+); tunnels? leads? to valves? (.+))");
      vector<string> connections;
      for (auto t : tok(conn, ','))
        connections.push_back(trim(t));

      flows[valve] = stoll(flow);
      for (auto c : connections)
      {
        g.AddEdge(valve, c, 1);
        tunnels[valve].insert(c);
      }
      valves.push_back(valve);
    }

    for (auto p : valves)
    {
      for (auto q : valves)
      {
        if (p != q)
        {
          auto road = g.GetShortestPath(p, q);
          road.erase(road.begin());
          roads[p][q] = road;
        }
      }
    }

    LL t = 0;
    for (auto i : flows)
      t += i.second;

    // auto topoSort = g.SortTopologically();

    auto ret = solve(0, "AA", {});

    return get<0>(ret);
  }

  LL DoWork2()
  {
    for (auto d : mData)
    {
      auto [valve, flow, conn] =
        RegExMatch3(d, R"(Valve (.+) has flow rate=(.+); tunnels? leads? to valves? (.+))");
      vector<string> connections;
      for (auto t : tok(conn, ','))
        connections.push_back(trim(t));

      flows[valve] = stoll(flow);
      for (auto c : connections)
      {
        g.AddEdge(valve, c, 1);
        tunnels[valve].insert(c);
      }
      valves.push_back(valve);
    }

    for (auto p : valves)
    {
      for (auto q : valves)
      {
        if (p != q)
        {
          auto road = g.GetShortestPath(p, q);
          road.erase(road.begin());
          roads[p][q] = road;
        }
      }
    }

    LL t = 0;
    for (auto i : flows)
      t += i.second;

    // auto topoSort = g.SortTopologically();

    auto valvesSolution1 = solve(0, "AA", {});
    auto valvePressure   = valvesSolution1.first;
    cout << mCurrentInput << " part1: " << valvePressure << endl;
    auto valveSet = valvesSolution1.second;

    for (auto v : valveSet)
    {
      // if (v != "AA")
      rightValves.push_back(v);
    }

    /* t = 0;
     for (auto i : rightValves)
       t += flows[i];
     cout << "T = " << t << endl;*/

    auto valvesSolution2 = solve2(0, 0, "AA", "AA", {}, {});

    // ----
    int ret = get<0>(valvesSolution2);

    auto vis     = get<1>(valvesSolution2);
    auto visElef = get<2>(valvesSolution2);

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
    // aoc_assert(Part1(), "1651"s);
    aoc_assert(Part2(), "1707"s);
    // mCurrentInput = "input";
    // aoc_assert(Part1(), "2056"s);
    // aoc_assert(Part2(), "2513"s);
    ////    aoc_assert(Part2() != "");
    return true;
  }
};
