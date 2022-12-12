#pragma once

#include "SolutionDay.h"

struct Day10CPU : public SimpleCPU
{
  enum RegistryType
  {
    X = 1,
  };

  struct NoopInstruction : SimpleCPU::Instruction
  {
    NoopInstruction() {}

    int GetCycleCount(SimpleCPU &) override { return 1; }

    void Run(SimpleCPU &, LL) override{ /* do nothing */ };
  };

  struct AddXInstruction : SimpleCPU::Instruction
  {
    AddXInstruction(LL aPayload) { this->payload = aPayload; }

    int GetCycleCount(SimpleCPU &) override { return 2; }

    void Run(SimpleCPU & aCpu, LL aCrtInstCycle) override
    {
      if (aCrtInstCycle == 2)
        aCpu.registers[RegistryType::X] += payload;
    };
  };

  void ReadInstructions(vector<string> aLines)
  {
    for (auto d : aLines)
    {
      auto   tokens    = tok(d, ' ');
      string instrName = tokens[0];

      if (instrName == "noop")
        instructions.push_back(make_shared<NoopInstruction>());
      else if (instrName == "addx")
        instructions.push_back(make_shared<AddXInstruction>(stoll(tokens[1])));
      else
        assert(!"unsupported instruction");
    }
  }

  Day10CPU(string inputFile)
  {
    registers[RegistryType::X] = 1;
    ReadInstructions(rff(inputFile));
  }
};

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

    Day10CPU cpu(GetInputPath());
    cpu.runBeforeInstructionFunctor = [&](SimpleCPU & aCpu)
    {
      if (contains(vector{ 20, 60, 100, 140, 180, 220 }, aCpu.currentCycleCount))
        ret += aCpu.currentCycleCount * aCpu.registers[Day10CPU::RegistryType::X];
    };
    cpu.Run(begin(cpu.instructions));

    return ret;
  }

  string DoWork2()
  {
    int           crtLine = 0;
    int           crtCol  = 0;
    ostringstream outS;

    Day10CPU cpu(GetInputPath());
    cpu.runBeforeInstructionFunctor = [&](SimpleCPU & aCpu)
    {
      const bool isLit = abs(crtCol - aCpu.registers[Day10CPU::RegistryType::X]) <= 1;
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
    aoc_assert(Part1(), "13140"s);

    mCurrentInput = "input";
    aoc_assert(Part1(), "17940"s);

    string testVal = R"(####..##..###...##....##.####...##.####.
...#.#..#.#..#.#..#....#.#.......#....#.
..#..#....###..#..#....#.###.....#...#..
.#...#....#..#.####....#.#.......#..#...
#....#..#.#..#.#..#.#..#.#....#..#.#....
####..##..###..#..#..##..#.....##..####.
)";
    aoc_assert(Part2(), testVal);
    return true;
  }
};
