#pragma once

#include "SolutionDay.h"

class Day17 : public ISolutionDay
{
private:
  vector<string> mData;

public:
  Day17() {}

  ~Day17() override {}

  void ReadData()
  {
    mData.clear();
    mData = rff(GetInputPath());
  }

  string GetDay() override { return "17"; }

  LL DoWork1()
  {
    string movement = mData[0];

    vector<DynamicMap<char>> rocks;
    auto                     rocksStr = rffv(GetNamedFile("rocks"));
    for (auto rockData : rocksStr)
    {
      DynamicMap<char> rock;
      rock.fromlines(rockData);

      rocks.push_back(rock.clone_if(
        [](Point, char c)
        {
          return c == '#';
        }));
    }

    DynamicMap<char> m;

    int              floorY = 10000;
    int              step   = 0;
    int              xPos, yPos, crtRockToSpawn{ 0 };
    auto             moveIt = movement.begin();
    bool             stoppedMoving{ true };
    bool             movingDownNext{ false };
    DynamicMap<char> crtSpawnedRock;
    int              restedRocks{ 0 };
    bool             isEmpty{ true };
    while (true)
    {
      if (stoppedMoving)
      {
        if (!isEmpty)
        {
          // m.printf(KVERBOSE, ' ', '.');

          // LL towerHeight = abs(m.min_y - m.max_y);
          // towerHeight++;
        }

        // emit new rock  --------------------------------------------------
        xPos = 2;
        if (isEmpty)
        {
          yPos    = floorY - 5;
          isEmpty = false;
        }
        else
        {
          if (restedRocks == 8)
          {
            int i = 0;
          }
          int highestRockY{ floorY };
          m.for_each(
            [&](Point p, char)
            {
              if (p.y < highestRockY)
                highestRockY = p.y;
              return true;
            });
          yPos = highestRockY - 5;
        }

        crtSpawnedRock = rocks[crtRockToSpawn];

        LL rockLowerY{ 0 };
        crtSpawnedRock.for_each(
          [&](Point p, char c)
          {
            if (p.y > rockLowerY)
              rockLowerY = p.y;
            return true;
          });
        LL diffY = yPos - rockLowerY;

        crtSpawnedRock = crtSpawnedRock.transform(
          [&](Point p, char c)
          {
            return make_tuple(true, p + Point{ xPos, diffY }, c);
          });

        crtRockToSpawn = (crtRockToSpawn + 1) % rocks.size();
        stoppedMoving  = false;
        movingDownNext = true;
      }
      else
      // move rock --------------------------------------------------
      {
        Point diff;

        if (movingDownNext)
        {
          diff           = Point{ 0, 1 };
          movingDownNext = false;
        }
        else
        {
          movingDownNext = true;
          switch (*moveIt)
          {
          case '>':
            diff = Point(1, 0);
            break;
          case '<':
            diff = Point(-1, 0);
            break;
          }

          moveIt++;
          if (moveIt == end(movement))
            moveIt = begin(movement);
        }

        DynamicMap<char> movedRock = crtSpawnedRock.transform(
          [&](Point p, char c)
          {
            return make_tuple(true, p + diff, c);
          });

        bool shouldStop{ false };
        bool canMoveSideways{ true };
        movedRock.for_each(
          [&](Point p, char c)
          {
            if (p.x < 0 || p.x > 6)
              canMoveSideways = false;
            if (p.y == floorY)
            {
              shouldStop = true;
            }
            if (m.isSetAt(p))
            {
              if (!movingDownNext)
                shouldStop = true;
              else
                canMoveSideways = false;
            }
          });
        if (!shouldStop && canMoveSideways)
          crtSpawnedRock = movedRock;
        if (shouldStop)
        {
          m += crtSpawnedRock;

          //  m.printf(KVERBOSE, "", '.');
          restedRocks += 1;

          stoppedMoving = true;
        }

        if (restedRocks == 2022)
          break;

        step++;
      }
    }

    LL towerHeight = abs(m.min_y - m.max_y) + 1;

    LL ret = towerHeight;
    return ret;
  }

  LL DoWork2()
  {
    LL ret = 172;
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
    aoc_assert(Part1(), "3068"s);
    mCurrentInput = "input";
    aoc_assert(Part1(), "3153"s);
    // aoc_assert(Part2() != "");
    return true;
  }
};
