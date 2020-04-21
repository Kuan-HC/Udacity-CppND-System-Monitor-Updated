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

        ACTIVE_TIME = ActiveTimeTotal() - previous ActiveTimeTotal();
        IDLE_TIME   = GetIdleTimeTotal() - previous IdleTimeTotal();
        TOTAL_TIME  = ACTIVE_TIME + IDLE_TIME;
        int usage = 100.f * ACTIVE_TIME / TOTAL_TIME;
        std::cout << "total cpu usage: " << usage << std::endl;
   * 
   * *******************************************************************************************************************************************/
    long now_active = LinuxParser::ActiveJiffies(pid_num);
    long now_total = LinuxParser::Jiffies();
    float Cpu_Utilization = 0.0f;

    if ((now_total - prev_total) == 0)
    {
        Cpu_Utilization = -0.1f;
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
string Process::Command() { return LinuxParser::Command(pid_num); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_num); }

// TODO: (test)Return the user (name) that generated this process
string Process::User()
{
    int tmp = LinuxParser::Uid(pid_num);
    return LinuxParser::User(tmp);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_num); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{
    return (cpu_load < a.cpu_load) ? true :false; 
}