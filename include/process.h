#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using std::string;
 enum ProcessCPU_States
{
  kUtime_ = 0 ,//- CPU time spent in user code, measured in clock ticks
  kStime_ , //- CPU time spent in kernel code, measured in clock ticks
  kCutime_ ,//- Waited-for children's CPU time spent in user code (in clock ticks)
  kCstime_ , //- Waited-for children's CPU time spent in kernel code (in clock ticks)
  kStarttime_,
  MaxProcessCpuStates,
  
};
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  string User();                           // TODO: See src/process.cpp
  string Command();                        // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  string Ram();                            // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int ProcessPid_;
  
};

#endif