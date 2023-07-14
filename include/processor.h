#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
  float PrevNonIdleCpuTime_;
  float PrevIdleCpuTime_;
  float NonIdleCpuTime_;
  float IdleCpuTime_;
};

enum ProcesCPU_States
{
  kUtime = 0,//- CPU time spent in user code, measured in clock ticks
  kStime = 1, //- CPU time spent in kernel code, measured in clock ticks
  kCutime  = 2,//- Waited-for children's CPU time spent in user code (in clock ticks)
  kCstime = 3, //- Waited-for children's CPU time spent in kernel code (in clock ticks)
  kStarttime = 4

};

#endif