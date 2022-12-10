#pragma once

struct SimpleCPU
{
  enum class RegistryType
  {
    X = 1,
  };

  using RegisterMap = unordered_map<RegistryType, LL>;

  struct Instruction
  {
    string name;
    LL     payload;

    virtual void Run(SimpleCPU & aCpu, LL aCrtInstCycle) = 0;
    virtual int  GetCycleCount(SimpleCPU & aCpu)         = 0;
  };

  using InstructionVector = vector<shared_ptr<Instruction>>;

  //---------------------------------------------------------------------------

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

  //---------------------------------------------------------------------------

  RegisterMap                       registers{};
  InstructionVector                 instructions{};
  function<void(SimpleCPU & aThis)> runFunctor{ nullptr };
  InstructionVector::iterator       instructionPointer;
  LL                                currentCycles{};

  static bool DefaultStoppingFunctor(SimpleCPU & aCpu)
  {
    return aCpu.instructionPointer == end(aCpu.instructions);
  };

  SimpleCPU(unordered_map<RegistryType, LL> aRegisters)
    : registers(aRegisters)
  {
  }

  void Reset() { instructions.clear(); }

  void ReadInstructions(vector<string> aLines, bool aClearExisting)
  {
    if (aClearExisting)
      Reset();

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

  void Run(InstructionVector::iterator instrPtr,
           function<bool(SimpleCPU &)> stopFunctor = DefaultStoppingFunctor)
  {
    LL instCycle       = 0;
    instructionPointer = instrPtr;

    while (true)
    {
      currentCycles++;
      instCycle++;

      runFunctor(*this);

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
