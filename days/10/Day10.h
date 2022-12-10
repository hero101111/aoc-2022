#pragma once

#include "SolutionDay.h"

class Day10 : public ISolutionDay
{
public:
  Day10() {}

  ~Day10() override {}

  void ReadData() {}

  string GetDay() override { return "10"; }

  auto GetCPU()
  {
    SimpleCPU::RegisterMap registers;
    registers[SimpleCPU::RegistryType::X] = 1;

    SimpleCPU cpu(registers);
    cpu.ReadInstructions(rff(GetInputPath()), false);

    return cpu;
  }

  LL DoWork1()
  {
    LL ret = 0;

    auto cpu       = GetCPU();
    cpu.runFunctor = [&](SimpleCPU & aCpu)
    {
      if (contains(vector{ 20, 60, 100, 140, 180, 220 }, aCpu.currentCycleCount))
        ret += aCpu.currentCycleCount * aCpu.registers[SimpleCPU::RegistryType::X];
    };
    cpu.Run(begin(cpu.instructions));

    return ret;
  }

  string DoWork2()
  {
    int           crtLine = 0;
    int           crtCol  = 0;
    ostringstream outS;

    auto cpu       = GetCPU();
    cpu.runFunctor = [&](SimpleCPU & aCpu)
    {
      const bool isLit = abs(crtCol - aCpu.registers[SimpleCPU::RegistryType::X]) <= 1;
      if (isLit)
        outS << "#";
      else
        outS << ".";

      crtCol += 1;
      if (crtCol == 40)
      {
        crtLine += 1;
        crtCol = 0;
        outS << endl;
      }
    };
    cpu.Run(begin(cpu.instructions));

    return outS.str();
  }

  string Part1() override
  {
    ReadData();

    return std::to_string(DoWork1());
  }

  string Part2() override
  {
    ReadData();

    return DoWork2();
  }

  bool Test() override
  {
    mCurrentInput = "test";
    assert(Part1() == "13140");

    mCurrentInput = "input";
    assert(Part1() == "17940");

    string testVal = R"(####..##..###...##....##.####...##.####.
...#.#..#.#..#.#..#....#.#.......#....#.
..#..#....###..#..#....#.###.....#...#..
.#...#....#..#.####....#.#.......#..#...
#....#..#.#..#.#..#.#..#.#....#..#.#....
####..##..###..#..#..##..#.....##..####.
)";
    assert(Part2() == testVal);
    return true;
  }
};
