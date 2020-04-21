#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h" /* to use function in namespace LinuxParser */
#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: (Done) See src/system.cpp
  long UpTime();                      // TODO: (Done) See src/system.cpp
  int TotalProcesses();               // TODO: (Done) See src/system.cpp
  int RunningProcesses();             // TODO: (Done) See src/system.cpp
  std::string Kernel();               // TODO: (Done) See src/system.cpp
  std::string OperatingSystem();      // TODO: (Done) See src/system.cpp

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  /* add variable to store system info */
  std::string OS_Name{"Unknown"};
  std::string Kernel_Num{"Unknown"};
};

#endif