#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
using std::string;
using std::to_string;
using std::vector;



Process::Process(int pid):ProcessPid_(pid){};

// TODO: Return this process's ID
int Process::Pid() { return ProcessPid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()const
{
  vector<float> ProcessCPU_Usage = LinuxParser::CpuUtilization(ProcessPid_) ;
  float cpu_usage, total_time;
   long seconds;
  if(ProcessCPU_Usage.size() == MaxProcessCpuStates)
  {
   
   total_time =  ProcessCPU_Usage[kUtime_] + ProcessCPU_Usage[kStime_] + ProcessCPU_Usage[kCutime_] + ProcessCPU_Usage[kCstime_];
   seconds =  LinuxParser::UpTime() - LinuxParser::UpTime(ProcessPid_) ;
  
   cpu_usage =((total_time / sysconf(_SC_CLK_TCK)) / seconds);
  }
  else
  {
   cpu_usage = 0;
  }
  
  return cpu_usage;

}
 

// TODO: Return the command that generated this process
string Process::Command() {return LinuxParser::Command(ProcessPid_); }

// TODO: Return this process's memory utilization
string Process::Ram() {return LinuxParser::Ram(ProcessPid_);}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(ProcessPid_);}
  
 

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {//LinuxParser::UpTime(ProcessPid_);}
  long int uptime = LinuxParser::UpTime() - LinuxParser::UpTime(ProcessPid_);
  return uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
  bool status;
if ((a.CpuUtilization()) < (this -> CpuUtilization()))
  {
      status = true;
  }
  else
  {
     status = false;
  }
  return status;
}