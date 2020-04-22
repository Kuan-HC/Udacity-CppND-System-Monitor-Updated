#include "process.h"
#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

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
  string line;
  float result = 0.0f;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_num) + LinuxParser::kStatFilename);
  if (stream.is_open()) {
  std::getline(stream, line); // file contains only one line    
  std::istringstream buffer(line);
  std::istream_iterator<string> beginning(buffer), end;
  std::vector<string> line_content(beginning, end);

  float utime = stof(line_content[13;//]LinuxParser::UpTime(pid_num);
  float stime = stof(line_content[14]);
  float cutime = stof(line_content[15]);
  float cstime = stof(line_content[16]);
  float starttime = stof(line_content[21]);   

  float uptime = LinuxParser::UpTime();
  float freq = sysconf(_SC_CLK_TCK);
  float total_time = utime + stime + cutime + cstime;
  float seconds = uptime - (starttime / freq);
  result = 100.0 * ((total_time / freq) / seconds);
  }
  return result;
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