#include "system.h"

#include <unistd.h>

#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: (DOne) Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: (Done)Return a container composed of the system's processes
vector<Process>& System::Processes() {
  /**************************************************************
   * Vector processes_ ; first remove all element than
   * instantiate new obj with pid from LinuxParser::Pids()
   * ************************************************************/
  processes_.clear();
  std::vector<int> item = LinuxParser::Pids();
  for (int pid : item) {
    /* to intantiate obj with pid, need to create constructor in class Process in Process.h */
    processes_.emplace_back(Process(pid));     
  }
  std::sort(processes_.begin(), processes_.end());
  reverse(processes_.begin(), processes_.end());
  return processes_;
}

// TODO: (Done) Return the system's kernel identifier (string)
std::string System::Kernel() {
  return Kernel_Num == "Unknown" ? Kernel_Num = LinuxParser::Kernel() : Kernel_Num;
}

// TODO: (Done) Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: (Done) Return the operating system name
std::string System::OperatingSystem() {
  return OS_Name == "Unknown" ? (OS_Name = LinuxParser::OperatingSystem()) : OS_Name;
}

// TODO: (Done) Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
 }

// TODO: (Done) Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: (Done) Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }