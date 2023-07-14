#include <string>

#include "format.h"
using std::string;
using std::to_string;

static string TimetoStrConversion(long Time);

// TODO: Complete this helper function
// INPUT: Long  measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
 int Hours,Minutes,Secs;
 string Hr_str,Min_str,Sec_str,Time;
  
 Hours = seconds / 3600;
 Minutes = (seconds % 3600)/60;
 Secs = (seconds % 3600)%60;

  
  Hr_str = TimetoStrConversion(Hours);
  Min_str=  TimetoStrConversion(Minutes);
  Sec_str = TimetoStrConversion(Secs);

 
  Time = Hr_str + ":" + Min_str + ":" + Sec_str;
  return Time;
  
}

static string TimetoStrConversion(long Time)
{
  if(Time>9)
  {
    return to_string(Time);
  }
  else
  {
    return "0"+ to_string(Time);

  }

}
