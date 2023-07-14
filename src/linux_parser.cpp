#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


template <typename T>
T findValueByKey(std::string const &keyFilter, std::string const &filename) {
  std::string line, key;
  T value;
  std::ifstream stream("/proc/" + filename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == keyFilter) {
          stream.close();
          return value;
        }
      }
    }
  }
  
  return value;
};

template <typename T>
T getValueOfFile(std::string const &filename) {
  std::string line;
  T value;

  std::ifstream stream("/proc/" + filename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
    stream.close();

  }
  return value;
};

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
  filestream.close();
}
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
    stream.close();

  }
  return kernel;
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
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
 float TotalMemory = findValueByKey<float>(kTotalMemory, kMeminfoFilename);//AccessMemInfoFileData(kTotalMemory);//
 float FreeMemory = findValueByKey<float>(kFreeMemory,kMeminfoFilename);//AccessMemInfoFileData(kFreeMemory);//
 float TotalUsedMemory = TotalMemory - FreeMemory;
  return TotalUsedMemory/TotalMemory;

}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {return long(getValueOfFile<long>(kUptimeFilename));
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
 string line,key,user,nice,system,idle,iowait, irq, softirq,steal,guest,guest_nice;
 vector <string> CpuInfos;
  
 std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
  {
    std::getline(stream,line);
    std::istringstream linestream(line);
	while(linestream >> key >> user >> nice >> system >> idle >>iowait >>irq >> softirq >> steal >> guest >> guest_nice)
    {
    	if(key == kFilterCpu)
        {
        	CpuInfos.emplace_back(user);
            CpuInfos.emplace_back(nice);
        	CpuInfos.emplace_back(system);
        	CpuInfos.emplace_back(idle);
        	CpuInfos.emplace_back(iowait);
        	CpuInfos.emplace_back(irq);
        	CpuInfos.emplace_back(softirq);
        	CpuInfos.emplace_back(steal);
        	CpuInfos.emplace_back(guest);
        	CpuInfos.emplace_back(guest_nice);
          
            return CpuInfos;


        }
      
    }
    stream.close();
 
  }
   return CpuInfos;

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {return findValueByKey<int>(kTotalNumberOfProcesses,kStatFilename);}



// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return findValueByKey<int>(kTotalNumberOfRunningProcesses,kStatFilename);}

// TODO: Read and return the command

//associated with a process
string LinuxParser::Command(int pid) { return std::string(getValueOfFile<std::string>(std::to_string(pid) + kCmdlineFilename));}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{
  
  int Value =findValueByKey<int>(kProcessMemory,to_string(pid)+kStatusFilename);
  Value  /= 1024;
  return to_string(Value);
  
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) 
{ 
string line, key;
string Value =findValueByKey<string>(kProcessUid,to_string(pid)+kStatusFilename);
return Value;

}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) 
{
string line, key, x;
string Value = "";
string UID = Uid(pid);
std::ifstream filestream(kPasswordPath);
 if (filestream.is_open())
 {
    while (std::getline(filestream, line)) 
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> Value >> x >> key) 
      {
        if (key == UID) 
        {
          
         return Value;
         filestream.close();

        }
      }
   }
 }
  return Value; 
}

std::vector<float> LinuxParser::CpuUtilization(int pid) 
{ 
 string line;
  string xs;
  float x;
  vector<float> ProcessData;
  int counter = 1;
  std::ifstream filestream(LinuxParser::kProcDirectory +"/"+ to_string(pid) + LinuxParser::kStatFilename);

  if (filestream.is_open())
  {
   while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while ((linestream >> xs)&& counter != 23) 
      {
        if((counter == kutime)||(counter == kstime)||(counter == kcutime)||(counter == kcstime)||(counter == kstarttime))
         {
       	  x = std::stof(xs);
          ProcessData.emplace_back(x);
         }
        counter ++;
      }
   }
      filestream.close();

  }
     return ProcessData;
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) 
{
string line;
long Starttime = 0;
  string x;
int counter = 1;
std::ifstream filestream(kProcDirectory +"/"+ to_string(pid)+ kStatFilename);
 if (filestream.is_open()) 
 {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while ((linestream >> x) &&(counter != 23)) 
      {
        if (counter == kstarttime)
        {
          Starttime = std::stol(x)/sysconf(_SC_CLK_TCK);
        }
         
        counter ++;
        
      }
   }
   filestream.close();

 }
   return Starttime;

}
