#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: (Done) Return the system's kernel identifier (string)
std::string System::Kernel()
{
    return Kernel_Num == "Unknown"? Kernel_Num = LinuxParser::Kernel():Kernel_Num;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization()
{
    return LinuxParser::MemoryUtilization();
}

// TODO: (done) Return the operating system name
std::string System::OperatingSystem()
{
    return OS_Name == "Unknown"? (OS_Name = LinuxParser::OperatingSystem()):OS_Name;
}

// TODO: (done) Return the number of processes actively running on the system
int System::RunningProcesses()
{
    return LinuxParser::RunningProcesses();
}

// TODO: (Done) Return the total number of processes on the system
int System::TotalProcesses()
{
    return LinuxParser::TotalProcesses();
}
// TODO: (Done) Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }