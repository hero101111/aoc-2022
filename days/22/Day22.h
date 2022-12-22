#pragma once

#include "SolutionDay.h"

class Day22 : public ISolutionDay
{
private:
  const int K{ 50 };

public:
  Day22() {}

  ~Day22() override {}

  string GetDay() override { return "22"; }

  bool IsPointInSquare(Point p, Point leftUp)
  {
    return p.x >= leftUp.x && p.y >= leftUp.y && p.x <= (leftUp.x + K - 1) &&
           p.y <= (leftUp.y + K - 1);
  }

  auto GetFace(Point p) -> int
  {
    if (IsPointInSquare(p, Point{ K + 1, 1 }))
      return 1;

    else if (IsPointInSquare(p, Point{ 2 * K + 1, 1 }))
      return 2;

    else if (IsPointInSquare(p, Point{ K + 1, K + 1 }))
      return 3;

    else if (IsPointInSquare(p, Point{ K + 1, 2 * K + 1 }))
      return 4;

    else if (IsPointInSquare(p, Point{ 1, 2 * K + 1 }))
      return 5;

    else if (IsPointInSquare(p, Point{ 1, 3 * K + 1 }))
      return 6;

    else
      assert(!"unsupported");
  }

  auto GetNormalizedFacePos(Point p, int face) -> Point
  {
    auto ret        = p;
    auto faceVerify = GetFace(p);
    assert(face == faceVerify);
    switch (face)
    {
    case 1:
      ret = ret - Point{ K, 0 };
      break;
    case 2:
      ret = ret - Point{ 2 * K, 0 };
      break;
    case 3:
      ret = ret - Point{ K, K };
      break;
    case 4:
      ret = ret - Point{ K, 2 * K };
      break;
    case 5:
      ret = ret - Point{ 0, 2 * K };
      break;
    case 6:
      ret = ret - Point{ 0, 3 * K };
      break;
    }
    assert(ret.x >= 1 && ret.x <= K);
    assert(ret.y >= 1 && ret.y <= K);
    return ret;
  }

  auto GetFacePosFromNormalised(int face, Point p) -> Point
  {
    auto ret = p;
    assert(p.x >= 1 && p.x <= K && p.y >= 1 && p.y <= K);
    switch (face)
    {
    case 1:
      ret = ret + Point{ K, 0 };
      break;
    case 2:
      ret = ret + Point{ 2 * K, 0 };
      break;
    case 3:
      ret = ret + Point{ K, K };
      break;
    case 4:
      ret = ret + Point{ K, 2 * K };
      break;
    case 5:
      ret = ret + Point{ 0, 2 * K };
      break;
    case 6:
      ret = ret + Point{ 0, 3 * K };
      break;
    }
    return ret;
  }

  auto GetNextPosition(Point p, char dir) -> pair<Point, char>
  {
    int face = GetFace(p);
    assert(contains(rangeint(1, 6), face));

    auto nextFace = face;
    auto nextDir  = dir;

    Point pNorm = GetNormalizedFacePos(p, face);

    auto nextPotentialNorm = pNorm.FromDirection(dir);

    auto nextPosNorm = nextPotentialNorm;

    switch (face)
    {
    case 1:
      switch (dir)
      {
      case 'l':
        if (nextPotentialNorm.x == 0)
        {
          nextFace      = 5;
          nextDir       = 'r';
          nextPosNorm.x = 1;
          nextPosNorm.y = K - pNorm.y + 1;
        }
        break;
      case 'r':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'd':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'u':
        if (nextPotentialNorm.y == 0)
        {
          nextFace      = 6;
          nextDir       = 'r';
          nextPosNorm.x = 1;
          nextPosNorm.y = pNorm.x;
        }
        break;
      }
      break;

    case 2:
      switch (dir)
      {
      case 'l':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'r':
        if (nextPotentialNorm.x == K + 1)
        {
          nextFace      = 4;
          nextDir       = 'l';
          nextPosNorm.x = K;
          nextPosNorm.y = K - pNorm.y + 1;
        }
        break;
      case 'd':
        if (nextPotentialNorm.y == K + 1)
        {
          nextFace      = 3;
          nextDir       = 'l';
          nextPosNorm.x = K;
          nextPosNorm.y = pNorm.x;
        }
        break;
      case 'u':
        if (nextPotentialNorm.y == 0)
        {
          nextFace      = 6;
          nextDir       = 'u';
          nextPosNorm.x = pNorm.x;
          nextPosNorm.y = K;
        }
        break;
      }
      break;

    case 3:
      switch (dir)
      {
      case 'l':
        if (nextPotentialNorm.x == 0)
        {
          nextFace      = 5;
          nextDir       = 'd';
          nextPosNorm.x = pNorm.y;
          nextPosNorm.y = 1;
        }
        break;
      case 'r':
        if (nextPotentialNorm.x == K + 1)
        {
          nextFace      = 2;
          nextDir       = 'u';
          nextPosNorm.x = pNorm.y;
          nextPosNorm.y = K;
        }
        break;
      case 'd':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'u':
        return make_pair(p.FromDirection(dir), dir);
        break;
      }
      break;

    case 4:
      switch (dir)
      {
      case 'l':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'r':
        if (nextPotentialNorm.x == K + 1)
        {
          nextFace      = 2;
          nextDir       = 'l';
          nextPosNorm.x = K;
          nextPosNorm.y = K - pNorm.y + 1;
        }
        break;
      case 'd':
        if (nextPotentialNorm.y == K + 1)
        {
          nextFace      = 6;
          nextDir       = 'l';
          nextPosNorm.x = K;
          nextPosNorm.y = pNorm.x;
        }
        break;
      case 'u':
        if (nextPotentialNorm.y == 0)
        {
          nextFace      = 3;
          nextDir       = 'u';
          nextPosNorm.x = pNorm.x;
          nextPosNorm.y = K;
        }
        break;
      }
      break;

    case 5:
      switch (dir)
      {
      case 'l':
        if (nextPotentialNorm.x == 0)
        {
          nextFace      = 1;
          nextDir       = 'r';
          nextPosNorm.x = 1;
          nextPosNorm.y = K - pNorm.y + 1;
        }
        break;
      case 'r':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'd':
        return make_pair(p.FromDirection(dir), dir);
        break;
      case 'u':
        if (nextPotentialNorm.y == 0)
        {
          nextFace      = 3;
          nextDir       = 'r';
          nextPosNorm.x = 1;
          nextPosNorm.y = pNorm.x;
        }
        break;
      }
      break;

    case 6:
      switch (dir)
      {
      case 'l':
        if (nextPotentialNorm.x == 0)
        {
          nextFace      = 1;
          nextDir       = 'd';
          nextPosNorm.x = pNorm.y;
          nextPosNorm.y = 1;
        }
        break;
      case 'r':
        if (nextPotentialNorm.x == K + 1)
        {
          nextFace      = 4;
          nextDir       = 'u';
          nextPosNorm.x = pNorm.y;
          nextPosNorm.y = K;
        }
        break;
      case 'd':
        if (nextPotentialNorm.y == K + 1)
        {
          nextFace      = 2;
          nextDir       = 'd';
          nextPosNorm.x = pNorm.x;
          nextPosNorm.y = 1;
        }
        break;
      case 'u':
        return make_pair(p.FromDirection(dir), dir);
        break;
      }
      break;
    }
    assert(nextPosNorm.x >= 1 && nextPosNorm.x <= K);
    assert(nextPosNorm.y >= 1 && nextPosNorm.y <= K);

    auto next = GetFacePosFromNormalised(nextFace, nextPosNorm);
    assert(GetFace(next) == nextFace);

    return make_pair(next, nextDir);
  }

  auto runCubeMathSanityChecks(DynamicMap<char> inputDataMap) -> void
  {
    DynamicMap<char> mVerify;
    inputDataMap.for_each(
      [&](Point p, char c)
      {
        if (c == '.' || c == '#' || c == 'c')
        {
          int face   = GetFace(p);
          mVerify[p] = face + '0';
        }
      });

    DynamicMap<char> mVerify2;
    for (auto i : rangeint(1, 6))
    {
      for (LL x : rangeint(1, K))
        for (LL y : rangeint(1, K))
        {
          auto p      = GetFacePosFromNormalised(i, { x, y });
          mVerify2[p] = i + '0';
        }
    }
    assert(mVerify == mVerify2);

    DynamicMap<char> mVerify3;
    for (auto f : rangeint(1, 6))
    {
      set<Point> pointsToCheck;
      {
        auto line1 = Point{ 1, 1 }.GetTo(Point{ K, 1 });
        for (auto p : line1)
          pointsToCheck.insert(p);
      }
      {
        auto line1 = Point{ K, 1 }.GetTo(Point{ K, K });
        for (auto p : line1)
          pointsToCheck.insert(p);
      }
      {
        auto line1 = Point{ K, K }.GetTo(Point{ 1, K });
        for (auto p : line1)
          pointsToCheck.insert(p);
      }
      {
        auto line1 = Point{ 1, K }.GetTo(Point{ 1, 1 });
        for (auto p : line1)
          pointsToCheck.insert(p);
      }

      for (auto p : pointsToCheck)
      {
        for (auto dir : { 'l', 'r', 'd', 'u' })
        {
          auto [next, newDir] = GetNextPosition(GetFacePosFromNormalised(f, p), dir);

          auto newFace = GetFace(next);

          if (newFace != f)
          {
            mVerify3[next] = newFace + '0';
            char dirBack   = Point::DirectionOpposite(newDir);

            next = GetNormalizedFacePos(next, newFace);
            auto [backTo, backDir] =
              GetNextPosition(GetFacePosFromNormalised(newFace, next), dirBack);

            assert(backTo == GetFacePosFromNormalised(f, p));
            assert(dir == Point::DirectionOpposite(backDir));

            for (int i : rangeint(1, (K - 2) / 2))
            {
              auto [backTo2, backDir2] = GetNextPosition(backTo, backDir);
              assert(backTo2.DistanceTo(backTo) == 1);
              assert(GetFace(backTo) == GetFace(backTo2));
              mVerify3[backTo2] = GetFace(backTo2) + '0';
              backTo            = backTo2;
            }
          }
        }
      }
    }

    // check movement inside areas
    for (auto f : rangeint(1, 6))
    {
      for (auto x : rangeint(2, K - 1))
      {
        for (auto y : rangeint(2, K - 1))
        {
          for (auto d : { 'u', 'r', 'd', 'l' })
          {
            auto p                = GetFacePosFromNormalised(f, { x, y });
            auto [pNext, dirNext] = GetNextPosition(p, d);
            assert(p.ManhattanDist(pNext) == 1);
            assert(GetFace(pNext) == f);
          }
        }
      }
    }

    // test full wrap around the cube, middle of face 1, going all directions
    for (auto dirTry : { 'l', 'r', 'u', 'd' })
    {
      Point p    = GetFacePosFromNormalised(1, { K / 2, K / 2 });
      Point init = p;
      char  dir  = dirTry;
      for (int s = 0; s < 4 * K; s++)
      {
        auto [pN, dN] = GetNextPosition(p, dir);
        p             = pN;
        dir           = dN;
      }
      assert(p == init);
    }

    // test right and left rotations for corners of each face and see if arrives back
    vector<tuple<Point, char, bool>> toTestRotations;
    toTestRotations.push_back(make_tuple(Point{ 1, 1 }, 'l', false));
    toTestRotations.push_back(make_tuple(Point{ 1, 1 }, 'u', true));
    toTestRotations.push_back(make_tuple(Point{ K, 1 }, 'r', true));
    toTestRotations.push_back(make_tuple(Point{ K, 1 }, 'u', false));
    toTestRotations.push_back(make_tuple(Point{ K, K }, 'r', false));
    toTestRotations.push_back(make_tuple(Point{ K, K }, 'd', true));
    toTestRotations.push_back(make_tuple(Point{ 1, K }, 'l', true));
    toTestRotations.push_back(make_tuple(Point{ 1, K }, 'd', false));

    for (auto [pTry, dirTry, rotateLeft] : toTestRotations)
    {
      for (auto f : rangeint(1, 6))
      {
        Point                    p     = GetFacePosFromNormalised(f, pTry);
        auto                     initP = p;
        vector<pair<int, Point>> stepsTaken;
        stepsTaken.push_back(make_pair(f, pTry));

        auto dir = dirTry;
        {
          auto [pN, dN] = GetNextPosition(p, dir);
          p             = pN;
          dir           = dN;
          auto crtFace  = GetFace(p);
          auto pNorm    = GetNormalizedFacePos(p, crtFace);
          int  i        = 0;
          stepsTaken.push_back(make_pair(crtFace, pNorm));
        }
        // rotate
        dir = Point::RotateDirection(dir, rotateLeft);

        {
          auto [pN, dN] = GetNextPosition(p, dir);
          p             = pN;
          dir           = dN;
          auto crtFace  = GetFace(p);
          auto pNorm    = GetNormalizedFacePos(p, crtFace);
          int  i        = 0;
          stepsTaken.push_back(make_pair(crtFace, pNorm));
        }
        // rotate again
        dir = Point::RotateDirection(dir, rotateLeft);
        {
          auto [pN, dN] = GetNextPosition(p, dir);
          p             = pN;
          dir           = dN;
          auto crtFace  = GetFace(p);
          auto pNorm    = GetNormalizedFacePos(p, crtFace);
          int  i        = 0;
          stepsTaken.push_back(make_pair(crtFace, pNorm));
        }
        assert(p == initP);
      }
    }

    assert(mVerify3 == mVerify2);
  }

  LL DoWork(bool partOne)
  {
    auto             data = rffv(GetInputPath());
    DynamicMap<char> m_;
    m_.fromlines(data[0]);
    DynamicMap<char> m;
    m_.for_each(
      [&](Point p, char c)
      {
        m[p + Point{ 1, 1 }] = c;
        return true;
      });

    string dirs = data[1][0];

    Point  pos{};
    int    crtC   = 0;
    string crtTok = "";

    for (auto x : rangeint(m.min_x, m.max_x))
      if (m[{ x, m.min_y }] == '.')
      {
        pos = Point{ x, m.min_y };
        break;
      }

    if (!partOne)
      runCubeMathSanityChecks(m);

    char direction = 'r';
    auto tryMove   = [&](int moveAmount)
    {
      bool canMove = true;
      // do our move
      while (moveAmount > 0)
      {
        Point dest = pos;
        canMove    = true;

        Point nextDest = pos;
        char  nextDir  = direction;

        if (partOne)
        {
          dest = pos.FromDirection(direction);
        }
        else
        {
          auto crtFace = GetFace(pos);
          auto crtRel  = GetNormalizedFacePos(pos, crtFace);

          auto [nextDest_, nextDir_] = GetNextPosition(pos, direction);
          auto newFace               = GetFace(nextDest_);
          auto newRel                = GetNormalizedFacePos(nextDest_, newFace);
          dest                       = nextDest_;
          nextDir                    = nextDir_;
        }

        if (m[dest] != '.' && m[dest] != '#')
        {
          if (!partOne)
            assert(!"Part2 should not get here");
          canMove        = false;
          Point wrapDest = dest;
          // wrap around
          if (direction == 'r')
          {
            for (auto x : rangeint2(m.min_x, dest.x - 1))
            {
              if (m[{ x, dest.y }] == '#')
                break;

              if (m[{ x, dest.y }] == '.')
              {
                wrapDest = { x, dest.y };
                break;
              }
            }
          }
          else if (direction == 'l')
          {
            for (auto x : rangeint2(m.max_x, dest.x + 1))
            {
              if (m[{ x, dest.y }] == '#')
                break;

              if (m[{ x, dest.y }] == '.')
              {
                wrapDest = { x, dest.y };
                break;
              }
            }
          }
          else if (direction == 'd')
          {
            for (auto y : rangeint2(m.min_y, dest.y - 1))
            {
              if (m[{ dest.x, y }] == '#')
                break;

              if (m[{ dest.x, y }] == '.')
              {
                wrapDest = { dest.x, y };
                break;
              }
            }
          }
          else if (direction == 'u')
          {
            for (auto y : rangeint2(m.max_y, dest.y + 1))
            {
              if (m[{ dest.x, y }] == '#')
                break;

              if (m[{ dest.x, y }] == '.')
              {
                wrapDest = { dest.x, y };
                break;
              }
            }
          }
          if (wrapDest != dest)
          {
            // we can move
            dest    = wrapDest;
            canMove = true;
          }
        }
        else if (m[dest] == '#')
        {
          canMove = false;
        }
        else if (m[dest] == '.')
        {
          canMove = true;
          m[pos]  = '.';
        }
        else
          assert(!"invalid state");

        if (canMove)
        {
          m[pos]    = '.';
          pos       = dest;
          direction = nextDir;

          m[dest] = 'c';
        }
        moveAmount -= 1;
      }
    };

    m[pos] = 'c';

    while (true)
    {
      char c = dirs[crtC];
      if (isdigit(c))
        crtTok.push_back(c);
      else
      {
        tryMove(stoi(crtTok));

        if (c == 'L')
        {
          direction = Point::RotateDirection(direction, true);
        }
        else if (c == 'R')
        {
          direction = Point::RotateDirection(direction, false);
        }
        else
          assert(!"unsupported");

        crtTok = "";
      }

      crtC++;
      if (crtC == dirs.size())
      {
        tryMove(stoi(crtTok));
        break;
      }
    }

    int facing = 0;
    if (direction == 'l')
      facing = 2;
    if (direction == 'u')
      facing = 3;
    if (direction == 'd')
      facing = 1;
    LL ret = 1000 * (pos.y) + 4 * (pos.x) + facing;
    return ret;
  }

  string Part1() override { return std::to_string(DoWork(true)); }

  string Part2() override { return std::to_string(DoWork(false)); }

  bool Test() override
  {
    mCurrentInput = "input";
    aoc_assert(Part1(), "146092"s);
    aoc_assert(Part2(), "110342"s);
    return true;
  }
};
