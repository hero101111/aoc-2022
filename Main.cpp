
#include "stdafx.h"
#include "SolutionDay.h"
#include "days/1/Day1.h"
#include "days/10/Day10.h"
#include "days/11/Day11.h"
#include "days/12/Day12.h"
#include "days/13/Day13.h"
#include "days/14/Day14.h"
#include "days/15/Day15.h"
#include "days/16/Day16.h"
#include "days/17/Day17.h"
#include "days/18/Day18.h"
#include "days/19/Day19.h"
#include "days/2/Day2.h"
#include "days/20/Day20.h"
#include "days/21/Day21.h"
#include "days/22/Day22.h"
#include "days/23/Day23.h"
#include "days/24/Day24.h"
#include "days/25/Day25.h"
#include "days/3/Day3.h"
#include "days/4/Day4.h"
#include "days/5/Day5.h"
#include "days/6/Day6.h"
#include "days/7/Day7.h"
#include "days/8/Day8.h"
#include "days/9/Day9.h"

#define REG_DAY(a) solutions[a] = static_cast<unique_ptr<ISolutionDay>>(new Day##a());

using namespace std;

int main(int argc, char ** argv)
{
  map<size_t, unique_ptr<ISolutionDay>> solutions;
  REG_DAY(1);
  REG_DAY(2);
  REG_DAY(3);
  REG_DAY(4);
  REG_DAY(5);
  REG_DAY(6);
  REG_DAY(7);
  REG_DAY(8);
  REG_DAY(9);
  REG_DAY(10);
  REG_DAY(11);
  REG_DAY(12);
  REG_DAY(13);
  REG_DAY(14);
  REG_DAY(15);
  REG_DAY(16);
  REG_DAY(17);
  REG_DAY(18);
  REG_DAY(19);
  REG_DAY(20);
  REG_DAY(21);
  REG_DAY(22);
  REG_DAY(23);
  REG_DAY(24);
  REG_DAY(25);

  bool runAllTests = false;
  if (runAllTests)
  {
    for (auto & runner : solutions)
    {
      cout << "Running tests for day " << runner.first << endl;
      runner.second->Test();
    }
  }

#pragma warning(disable : 4996)
  time_t now = time(0);
  tm *   ltm = localtime(&now);
#pragma warning(default : 4996)
  ///////////////////////////////
  int DAY  = ltm->tm_mday;
  int PART = 1;
  ///////////////////////////////

  auto & runner = solutions[DAY];
  string result;

  bool runPartOne = PART == 1;

  // run tests first
  const bool passedTests = runner->Test();
  if (!passedTests)
    cout << "[TESTS FAILED]" << endl;

  if (runPartOne)
  {
    cout << "Running Day " << DAY << " PART 1 " << endl;
    runner->mCurrentInput = "input";
    result                = runner->Part1();
  }
  else
  {
    cout << "Running Day " << DAY << " PART 2 " << endl;
    runner->mCurrentInput = "input";
    result                = runner->Part2();
  }

  cout << endl << endl << result << endl << endl << "copied to clipboard" << endl;

  // store result in clipboard
  pic(result);

  return 0;
}
