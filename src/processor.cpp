#include "processor.h"

Processor::Processor() {
  PrevTotal = LinuxParser::Jiffies();
  PrevIdle = LinuxParser::IdleJiffies();
}

// TODO: (Done)Return the aggregate CPU utilization
float Processor::Utilization()
{
  float Total = LinuxParser::Jiffies();
  float Idle = LinuxParser::IdleJiffies();
  float Cpu_Utilization = 0;

  if ((Total - PrevTotal)!=0)
  {
   Cpu_Utilization = ((Total - PrevTotal) - (Idle - PrevIdle)) / (Total - PrevTotal);
  }
  else
  {
    Cpu_Utilization = 0;
  }
  
  /* update previous total and idle value */  
  PrevTotal  = Total;
  PrevIdle = Idle;

  //return (Cpu_Utilization>0.0)? Cpu_Utilization : 0.0;
  return Cpu_Utilization;
  
  
}

/*****************************************************************************************************************
 *   https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
 *   PrevIdle = previdle + previowait
 *   Idle = idle + iowait
 *
 *   PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
 *   NonIdle = user + nice + system + irq + softirq + steal
 *
 *   PrevTotal = PrevIdle + PrevNonIdle
 *   Total = Idle + NonIdle
 *
 *   differentiate: actual value minus the previous one
 *   totald = Total - PrevTotal
 *   idled = Idle - PrevIdle
 *
 *   CPU_Percentage = (totald - idled)/totald
 ******************************************************************************************************************/