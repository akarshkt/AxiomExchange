#pragma once

#include <cstdint>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
using Timestamp = uint64_t;

inline  std::string formatTimestamp(uint64_t timestampInSeconds)
{
    // 1. Convert raw number to a time_t object
    std::time_t timetOld = static_cast<std::time_t>(timestampInSeconds);

    // 2. Convert to local time structure safely
    std::tm *localTime = std::localtime(&timetOld);
    if (!localTime)
        return "Invalid Time";

    // 3. Format into a readable string using stream manipulators
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
inline  std::string formatNanosecondTimestamp(uint64_t timestampInNanoseconds)
{
    // 1. Separate whole seconds from the remaining fractional nanoseconds
    uint64_t seconds = timestampInNanoseconds / 1'000'000'000;
    uint64_t nanosecondsRemainder = timestampInNanoseconds % 1'000'000'000;

    // 2. Convert seconds to a calendar structure
    std::time_t timetOld = static_cast<std::time_t>(seconds);
    std::tm *localTime = std::localtime(&timetOld);
    if (!localTime)
        return "Invalid Time";

    // 3. Format the main date/time and append the nanoseconds precision
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");

    // Set width to 9 digits with zero padding for the nanoseconds section
    ss << "." << std::setfill('0') << std::setw(9) << nanosecondsRemainder;

    return ss.str();
}
inline  Timestamp getTimestamp()
{
    using namespace std::chrono;
    // system_clock tracks true real-world calendar time
    return duration_cast<nanoseconds>(
               system_clock::now().time_since_epoch())
        .count();
}
