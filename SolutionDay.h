#pragma once

#include "util/util.h"

class ISolutionDay
{
protected:
  ofstream verbose;
public:

  ISolutionDay()
  {
    verbose.open(KVERBOSE, ios_base::out);
  }

  virtual auto Part1() -> string = 0;
  virtual auto Part2() -> string = 0;

  virtual ~ISolutionDay() { verbose.close(); };

  virtual auto Test() -> bool { mCurrentInput = "input";  return true; }

  virtual auto GetDay() -> string { return "0";  }

  string mCurrentInput{ "input" };

  auto GetInputPath() -> string 
  {
    const string day = GetDay(); 
    assert(day != "0");
    return KINPUT + day + "/" + mCurrentInput + ".txt";
  };

};
