#include "../../include/utils/TimeUtils.h"
#include <chrono>

Timestamp getTimestamp()
{
    using namespace std::chrono;

    return duration_cast<nanoseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}