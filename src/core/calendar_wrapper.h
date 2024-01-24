#ifndef CORE_CALENDAR_WRAPPER_H
#define CORE_CALENDAR_WRAPPER_H

#include "calendar.h"
#include "date.h"
#include "types.h"
#include <vector>

namespace period_calendar {

class CalendarWrapper {
  public:
    CalendarWrapper();
    CalendarWrapper(date::year_month_day pillStartDay);
    const std::vector<Day>& view() const;
    void setMonth(int monthIndex);
    void setYear(int year);
    date::year_month setNextMonth();
    date::year_month setPrevMonth();
    void setPillStartDate(date::year_month_day date);
    date::year_month_day getPillStartDate() const;

  private:
    date::year_month page_;
    Calendar calendar_;
};

} // namespace period_calendar

#endif // CORE_CALENDAR_WRAPPER_H