#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h" /* For utilizing functions in namespace LinuxParser */

class Processor {
 public:
 Processor(); /* add constructor to initilize previoud PrevIdle and PrevTotal */
 float Utilization();  // TODO: (Done) See src/processor.cpp

 // TODO: (Done) Declare any necessary private members
 private:
 float PrevTotal{0.0f};
 float PrevIdle{0.0f};
};

#endif