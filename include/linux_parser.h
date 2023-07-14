#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};
  
const std::string kTotalNumberOfProcesses{"processes"};
const std::string kTotalNumberOfRunningProcesses{"procs_running"};
const std::string kTotalMemory{"MemTotal"};
const std::string kFreeMemory{"MemFree"};
const std::string kProcessMemory{"VmRSS"};// Memory of a Process is VmRSS
const std::string kProcessUid{"Uid"};
const std::string kFilterCpu("cpu");

  




// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();
//Cpu
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
  
enum ProcessCPU_States_LP
{
  kutime = 14,//- CPU time spent in user code, measured in clock ticks
  kstime = 15, //- CPU time spent in kernel code, measured in clock ticks
  kcutime  = 16,//- Waited-for children's CPU time spent in user code (in clock ticks)
  kcstime = 17, //- Waited-for children's CPU time spent in kernel code (in clock ticks)
  kstarttime = 22  
};
  
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
//long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long UpTime(int pid);
std::vector<float>CpuUtilization(int pid);

};  // namespace LinuxParser

#endif