#pragma once

struct SimpleCPU
{
  using RegisterMap = unordered_map<LL, LL>;

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
  function<void(SimpleCPU & aThis)> runBeforeInstructionFunctor{ nullptr };
  function<void(SimpleCPU & aThis)> runAfterInstructionFunctor{ nullptr };
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

      if (runBeforeInstructionFunctor != nullptr)
        runBeforeInstructionFunctor(*this);

      (*currentInstrPtr)->Run(*this, instCycle);

      if (runAfterInstructionFunctor != nullptr)
        runAfterInstructionFunctor(*this);

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
