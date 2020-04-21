#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stol;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, ver_num;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> ver_num;
  }
  return ver_num;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  string line, mem_key; 
  double total, free, value;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> mem_key >> value) {
        if (mem_key == "MemTotal:")
        {
          total = value;
        }
        else if (mem_key == "MemFree:")
        {
          free = value;
        }
        else
        {
          /* do nothing */
        }        
      }
    }
  }
  return static_cast<float>((total - free) /total); /* transfer to percentage */
}

// TODO: (Done) Read and return the system uptime
long LinuxParser::UpTime()
{
  string line;
  long time;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> time;
  }
  return time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies()
{
  return ActiveJiffies() + IdleJiffies();
}

// TODO: (Done) Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{
  /*******************************************************************************************************************************************
   * https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
   * meaning of each value:
   * https://web.archive.org/web/20130302063336/http://www.lindevdoc.org/wiki//proc/pid/stat
   * 
   * target: return the sum of: 
   * utime + stime + cutime + cstime    locate in position 14 - 17
   * *****************************************************************************************************************************************/
  string line;
  string pid_name,utime, stime, cutime, cstime;

  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> pid_name;
    for (int i = 0; i <= 3; i++)
    {
      linestream >> utime >> stime>> cutime >>cstime;
    }

  return (stol(utime)+stol(stime)+stol(cutime)+stol(stime));
  }
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{
  std::vector<long> cpu_data = Jiffies_Arr();

  return cpu_data[kUser_] + cpu_data[kNice_] + cpu_data[kSystem_] + cpu_data[kIRQ_] + cpu_data[kSoftIRQ_] + cpu_data[kSteal_];
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
  std::vector<long> cpu_data = Jiffies_Arr();

  return cpu_data[kIdle_] + cpu_data[kIOwait_];
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: (Done) Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  return FilterValue("processes");
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  return FilterValue("procs_running");
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }

/* Helpler Function */
int LinuxParser::FilterValue(string target_key) {
  string line, key;
  int value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == target_key) {
          return value;
        }
      }
    }
  }
  return value;
}

std::vector<long> LinuxParser::Jiffies_Arr()
{
  string line, key;
  long value_1, value_2, value_3, value_4, value_5, value_6, value_7, value_8,value_9, value_10;
  std::vector<long> tmp_cpu(10,0);

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key ) {
        if (key == "cpu") {
          linestream >> value_1 >> value_2 >> value_3 >> value_4 >> value_5 >>
                        value_6 >> value_7 >> value_8 >> value_9 >> value_10;
      
          tmp_cpu = {value_1 , value_2 , value_3 , value_4 , value_5 , value_6 ,
                     value_7 , value_8 , value_9 , value_10};
          return tmp_cpu;
      }
    }  
  } 
 }
return tmp_cpu;
}