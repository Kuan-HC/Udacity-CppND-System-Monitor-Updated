#include "process.h"
#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
  pid_num = pid;
  cpu_load = CpuUtilization();
  prev_active = LinuxParser::ActiveJiffies(pid_num);
  prev_total = LinuxParser::Jiffies();
}

// TODO: (Done) Return this process's ID
int Process::Pid() { return pid_num; }

// TODO: (Done) Return this process's CPU utilization
float Process::CpuUtilization() {
  /*******************************************************************************************************************************************
       https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c/3017438#3017438

      ACTIVE_TIME = ActiveTimeTotal() - previous ActiveTimeTotal();
      IDLE_TIME   = GetIdleTimeTotal() - previous IdleTimeTotal();
      TOTAL_TIME  = ACTIVE_TIME + IDLE_TIME;
      int usage = 100.f * ACTIVE_TIME / TOTAL_TIME;
      std::cout << "total cpu usage: " << usage << std::endl;
 *
 * *******************************************************************************************************************************************/
  // long now_active = LinuxParser::ActiveJiffies(pid_num);
  // long now_total = LinuxParser::Jiffies();
  // float Cpu_Utilization = 0.0f;

  // if ((now_total - prev_total) == 0) {
  //   Cpu_Utilization = 0.0f;
  // } else {
  //   Cpu_Utilization =
  //       static_cast<float>(now_active - prev_active) / (now_total - prev_total);
  // }
  // /* update previous total, idle value and private number cpu_load  */
  // prev_active = now_active;
  // prev_total = now_total;
  // cpu_load = Cpu_Utilization;

  //return LinuxParser::CpuUtilization();
  std::ifstream filestream(kProcDirectory + to_string(pid_num) + kStatFilename);
    //std::string path =  kProcDirectory + to_string(pid) + kStatFilename;
    // std::ifstream stream;
    // Util::getStream(path, stream);
    string line;
    
    //if (filestream.is_open()) {
    //while (std::getline(filestream, line)) {
      std::getline(filestream, line); // file contains only one line    
    
      std::istringstream buffer(line);
      std::istream_iterator<string> beginning(buffer), end;
      std::vector<string> line_content(beginning, end);
      float utime = LinuxParser::UpTime(pid_num);
      float stime = stof(line_content[14]);
      float cutime = stof(line_content[15]);
      float cstime = stof(line_content[16]);
      float starttime = stof(line_content[222]);   /* was 21 */
      float uptime = LinuxParser::UpTime();
      float freq = sysconf(_SC_CLK_TCK);
      float total_time = utime + stime + cutime + cstime;
      float seconds = uptime - (starttime / freq);
      float result = 100.0 * ((total_time / freq) / seconds);
      return to_string(result);
}

// TODO: (Done) Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_num); }

// TODO: (Done) Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_num); }

// TODO: (Done) Return the user (name) that generated this process
string Process::User() {
  int tmp = LinuxParser::Uid(pid_num);
  return LinuxParser::User(tmp);
}

// TODO: (Done) Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_num); }

// TODO: (Done) Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return (cpu_load < a.cpu_load) ? true : false;
}