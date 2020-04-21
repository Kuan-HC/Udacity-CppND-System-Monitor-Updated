#include "format.h"

#include <iomanip> /* Fill number with digit 0 */
#include <string>

#define MINSEC 60
#define HOURMIN 60
#define HOURSEC 3600

using std::string;

// TODO: (Done) Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  unsigned int seconds_ = seconds % MINSEC;
  unsigned int minutes_ = seconds % HOURSEC;
  minutes_ /= HOURMIN;
  unsigned int hours_ = seconds / HOURSEC;

  std::stringstream output;

  output << std::setw(2) << std::setfill('0') << hours_ << ":";
  output << std::setw(2) << std::setfill('0') << minutes_ << ":";
  output << std::setw(2) << std::setfill('0') << seconds_;

  return output.str();
}
