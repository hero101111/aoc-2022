#pragma once

#include "../../util/SimpleCPU.h"
#include "SolutionDay.h"

class Day10 : public ISolutionDay
{
public:
  Day10() {}

  ~Day10() override {}

  void ReadData() {}

  string GetDay() override { return "10"; }

  LL DoWork1()
  {
    LL ret = 0;

    unordered_map<SimpleCPU::RegistryType, LL> registers;
    registers[SimpleCPU::RegistryType::X] = 1;

    SimpleCPU cpu(registers);
    cpu.ReadInstructions(rff(GetInputPath()), false);
    cpu.runFunctor = [&](SimpleCPU & aThis, LL aCycle)
    {
      if (contains(vector{ 20, 60, 100, 140, 180, 220 }, aCycle))
        ret += aCycle * aThis.registers[SimpleCPU::RegistryType::X];
    };
    cpu.Run(begin(cpu.instructions));

    return ret;
  }

  string DoWork2()
  {
    int line = 0;
    int col  = 0;

    unordered_map<SimpleCPU::RegistryType, LL> registers;
    registers[SimpleCPU::RegistryType::X] = 1;

    ostringstream outS;
    SimpleCPU     cpu(registers);
    cpu.ReadInstructions(rff(GetInputPath()), false);
    cpu.runFunctor = [&](SimpleCPU & aThis, LL aCycle)
    {
      bool lit = false;

      auto xReg = aThis.registers[SimpleCPU::RegistryType::X];
      lit       = abs(col - xReg) <= 1;
      if (lit)
        outS << "#";
      else
        outS << ".";

      col += 1;
      if (col == 40)
      {
        line += 1;
        col = 0;
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
