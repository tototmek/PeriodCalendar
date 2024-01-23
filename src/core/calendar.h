#ifndef CORE_CALENDAR_H
#define CORE_CALENDAR_H

#include "date.h"

namespace period_calendar {

constexpr uint kDaysPerMonth = 6 * 7;
constexpr uint kPillPeriod = 28;
constexpr uint kPeriodDays = 4;

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

class Calendar {
  public:
    Calendar();
    const std::vector<Day>& view() const;
    void setCalendarPage(date::year_month date);
    void setPillStartDate(date::year_month_day date);

  private:
    Day analyzeDay(date::year_month_day date) const;
    mutable std::vector<Day> days_;
    date::year_month page_;
    date::year_month_day pillStartDate_;
};

} // namespace period_calendar

#endif // CORE_CALENDAR_H