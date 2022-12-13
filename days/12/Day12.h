#pragma once

#include "SolutionDay.h"

class Day12 : public ISolutionDay
{
public:
  DynamicMap<char> map;
  Graph<Point>     graph;
  Point            origin, destination;

  Day12()
    : graph(Graph<Point>(150 * 50))
  {
  }

  ~Day12() override {}

  string GetDay() override { return "12"; }

  char getNodeName(char nodeNameUntouched)
  {
    char nodeName = nodeNameUntouched;
    if (nodeName == 'S')
      nodeName = 'a';
    if (nodeName == 'E')
      nodeName = 'z';

    nodeName = 'z' - nodeName + 'a';
    return nodeName;
  }

  void ReadData()
  {
    map.fromfile(GetInputPath());
    map.for_each(
      [&](Point node, char nodeNameUntouched)
      {
        if (nodeNameUntouched == 'S')
          origin = node;
        if (nodeNameUntouched == 'E')
          destination = node;
        char nodeName = getNodeName(nodeNameUntouched);

        int nodeHeight = nodeName - 'a';

        for (auto dir : { Point{ 1, 0 }, Point{ 0, 1 } })
        {
          if (auto neigh = node + dir; map.isSetAt(neigh))
          {
            int heightNeigh = getNodeName(map[neigh]) - 'a';
            if (auto costThere = heightNeigh - nodeHeight; costThere <= 1)
              graph.AddEdge(node, neigh, 1);
            if (auto costBack = nodeHeight - heightNeigh; costBack <= 1)
              graph.AddEdge(neigh, node, 1);
          }
        }
        return true;
      });
  }

  LL DoWork(bool firstPart)
  {
    ReadData();

    auto dist = graph.GetDistances(destination);

    if (firstPart)
    {
      return dist[origin];
    }
    else
    {
      LL minRet = numeric_limits<LL>::max();
      map.for_each(
        [&](Point node, char nodeNameUntouched)
        {
          char nodeName = getNodeName(nodeNameUntouched);
          if (nodeName == 'z' && dist[node] < minRet)
            minRet = dist[node];
          return true;
        });
      return minRet;
    }
  }

  string Part1() override { return std::to_string(DoWork(true)); }

  string Part2() override { return std::to_string(DoWork(false)); }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "462"s);
    aoc_assert(Part2(), "451"s);
    return true;
  }
};
