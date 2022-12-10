#pragma once

struct SimpleCPU
{
  enum class RegistryType
  {
    X = 1,
  };

  struct Instruction
  {
    string name;
    LL     payload;

    virtual void Run(SimpleCPU & aCpu, LL aCrtInstCycle) = 0;
    virtual int  GetCycleCount(SimpleCPU & aCpu)         = 0;
  };

  struct NoopInstruction : Instruction
  {
    NoopInstruction() {}

    int GetCycleCount(SimpleCPU &) override { return 1; }

    void Run(SimpleCPU &, LL) override{ /* do nothing */ };
  };

  struct AddXInstruction : Instruction
  {
    AddXInstruction(LL aPayload) { this->payload = aPayload; }

    int GetCycleCount(SimpleCPU &) override { return 2; }

    void Run(SimpleCPU & aCpu, LL aCrtInstCycle) override
    {
      if (aCrtInstCycle == 2)
        aCpu.registers[RegistryType::X] += payload;
    };
  };

  unordered_map<RegistryType, LL>              registers;
  vector<shared_ptr<Instruction>>              instructions;
  function<void(SimpleCPU & aThis, LL aCycle)> runFunctor{ nullptr };
  vector<shared_ptr<Instruction>>::iterator    instructionPointer;

  static bool DefaultStoppingFunctor(SimpleCPU & aCpu)
  {
    return aCpu.instructionPointer == end(aCpu.instructions);
  };

  SimpleCPU(unordered_map<RegistryType, LL> aRegisters)
    : registers(aRegisters)
  {
  }

  void ReadInstructions(vector<string> aLines, bool aClearExisting)
  {
    if (aClearExisting)
      instructions.clear();
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

  void Run(vector<shared_ptr<Instruction>>::iterator instrPtr,
           function<bool(SimpleCPU &)>               stopFunctor = DefaultStoppingFunctor)
  {
    LL crtCycle        = 0;
    LL instCycle       = 0;
    instructionPointer = instrPtr;

    while (true)
    {
      crtCycle++;
      instCycle++;

      runFunctor(*this, crtCycle);

      (*instructionPointer)->Run(*this, instCycle);

      if ((*instructionPointer)->GetCycleCount(*this) == instCycle)
      {
        instructionPointer++;
        instCycle = 0;

        if (stopFunctor != nullptr && stopFunctor(*this))
          break;

        if (instructionPointer == end(instructions))
          instructionPointer = begin(instructions);
      }
    }
  }
};
