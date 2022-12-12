#pragma once

#include "SolutionDay.h"

class Day12 : public ISolutionDay
{
public:
  Day12() {}

  ~Day12() override {}

  string GetDay() override { return "12"; }

  LL DoWork(bool firstPart)
  {
    DynamicMap<char> map;
    map.fromfile(GetInputPath());
    int          n = (map.max_x + 20) * map.max_y;
    Graph<Point> graph(n);

    Point origin, destination;
    auto  getNodeName = [](char nodeNameUntouched)
    {
      char nodeName = nodeNameUntouched;
      if (nodeName == 'S')
        nodeName = 'a';
      if (nodeName == 'E')
        nodeName = 'z';

      nodeName = 'z' - nodeName + 'a';
      return nodeName;
    };
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

    return 0;
  }

  string Part1() override { return std::to_string(DoWork(true)); }

  string Part2() override { return std::to_string(DoWork(false)); }

  bool Test() override
  {
    mCurrentInput = "input";
    assert(Part1() == "462");
    assert(Part2() == "451");
    return true;
  }
};
