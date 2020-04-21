#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
{
    pid_num = pid;
    cpu_load = CpuUtilization();
    prev_active = LinuxParser::ActiveJiffies(pid_num);
    prev_total = LinuxParser::Jiffies();
}

// TODO: Return this process's ID
int Process::Pid() { return pid_num; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    /*******************************************************************************************************************************************
         https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c/3017438#3017438

        ACTIVE_TIME = ActiveTimeTotal() - previous GetActiveTimeTotal();
        IDLE_TIME   = GetIdleTimeTotal() - previous GetIdleTimeTotal();
        TOTAL_TIME  = ACTIVE_TIME + IDLE_TIME;
        int usage = 100.f * ACTIVE_TIME / TOTAL_TIME;
        std::cout << "total cpu usage: " << usage << std::endl;
   * 
   * *******************************************************************************************************************************************/
    long now_active = LinuxParser::ActiveJiffies(pid_num);
    long now_total = LinuxParser::Jiffies();
    float Cpu_Utilization = 0.0f;

    if ((now_total - prev_total) < EPSILON)
    {
        Cpu_Utilization = 0.0f;
    }
    else
    {
        Cpu_Utilization = static_cast<float>(now_active - prev_active) / (now_total - prev_total);    
    }
  
    /* update previous total and idle value */  
    prev_active = now_active;
    prev_total = now_total;
        
    return Cpu_Utilization;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }