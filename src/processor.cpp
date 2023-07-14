#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

Processor::Processor(): PrevNonIdleCpuTime_(0), PrevIdleCpuTime_(0), NonIdleCpuTime_(0), IdleCpuTime_(0) {};

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
 vector <string> CpuInfos;
  float user,nice,system,idle,iowait, irq, softirq,steal,guest,guest_nice,TotalCpuTime,PrevTotalCpuTime;
 CpuInfos = LinuxParser::CpuUtilization();
 
  user = std::stof(CpuInfos[LinuxParser::kUser_]);
  nice = std::stof(CpuInfos[LinuxParser::kNice_]);
  system = std::stof(CpuInfos[LinuxParser::kSystem_]);
  idle = std::stof(CpuInfos[LinuxParser::kIdle_]);
  iowait = std::stof(CpuInfos[LinuxParser::kIOwait_]);
  irq = std::stof(CpuInfos[LinuxParser::kIRQ_]);
  softirq = std::stof(CpuInfos[LinuxParser::kSoftIRQ_]);
  steal = std::stof(CpuInfos[LinuxParser:: kSteal_]);
  guest = std::stof(CpuInfos[LinuxParser::kGuest_]);
  guest_nice = std::stof(CpuInfos[LinuxParser::kGuestNice_]);

  IdleCpuTime_ = idle + iowait;
  NonIdleCpuTime_ = user + nice + system + irq + softirq + steal + guest + guest_nice;
  
  TotalCpuTime = IdleCpuTime_ + NonIdleCpuTime_;
  PrevTotalCpuTime = PrevIdleCpuTime_ + PrevNonIdleCpuTime_;
  
  float TotalCpuTimeDiff = TotalCpuTime - PrevTotalCpuTime;
  float IdleCpuTimeDiff = IdleCpuTime_ - PrevIdleCpuTime_;
  
  float CurrentCpuUtilization =  (TotalCpuTimeDiff - IdleCpuTimeDiff)/TotalCpuTimeDiff;
    
  PrevIdleCpuTime_ = IdleCpuTime_;
  PrevNonIdleCpuTime_ = NonIdleCpuTime_;

  return CurrentCpuUtilization;
	
}