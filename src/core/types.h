#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include <cstdint>

namespace period_calendar {

enum class DayType {
    BLANK,
    NORMAL,
};

enum class PeriodType {
    NONE,
    PERIOD,
};

struct Day {
    uint index = 0;
    DayType type = DayType::BLANK;
    PeriodType period = PeriodType::NONE;
};

} // namespace period_calendar

#endif // CORE_TYPES_H