#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#include "date.h"
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
    date::year_month_day date;
    DayType type = DayType::BLANK;
    PeriodType period = PeriodType::NONE;
};

} // namespace period_calendar

#endif // CORE_TYPES_H