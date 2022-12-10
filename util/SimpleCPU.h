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

  RegisterMap                       registers{};
  InstructionVector                 instructions{};
  function<void(SimpleCPU & aThis)> runFunctor{ nullptr };
  InstructionVector::iterator       currentInstrPtr;
  LL                                currentCycleCount{};

  static bool DefaultStoppingFunctor(SimpleCPU & aCpu)
  {
    return aCpu.currentInstrPtr == end(aCpu.instructions);
  };

  void Run(InstructionVector::iterator instrPtr,
           function<bool(SimpleCPU &)> stopFunctor = DefaultStoppingFunctor)
  {
    LL instCycle    = 0;
    currentInstrPtr = instrPtr;

    while (true)
    {
      currentCycleCount++;
      instCycle++;

      runFunctor(*this);

      (*currentInstrPtr)->Run(*this, instCycle);

      if ((*currentInstrPtr)->GetCycleCount(*this) == instCycle)
      {
        currentInstrPtr++;
        instCycle = 0;

        if (stopFunctor != nullptr && stopFunctor(*this))
          break;

        if (currentInstrPtr == end(instructions))
          currentInstrPtr = begin(instructions);
      }
    }
  }
};
