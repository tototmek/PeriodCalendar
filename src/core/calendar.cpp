#include "calendar.h"

#include "date.h"
#include "types.h"
#include <chrono>

namespace period_calendar {

namespace {

date::year_month_day getFirstDayOfPage(date::year_month page) {
    auto first_day = date::year_month_day{page / 1};
    auto weekday = date::weekday{first_day};
    auto days_to_previous_monday = date::days{weekday - date::Monday};
    auto last_monday = date::sys_days(first_day) - days_to_previous_monday;
    return date::year_month_day{last_monday};
}

date::year_month_day getLastDayOfPage(date::year_month page) {
    auto last_day = date::year_month_day{page / date::last};
    auto weekday = date::weekday{last_day};
    auto days_to_next_sunday = date::days{date::Sunday - weekday};
    auto next_sunday = date::sys_days(last_day) + days_to_next_sunday;
    return date::year_month_day{next_sunday};
}

date::year_month_day getNextDay(date::year_month_day day) {
    return date::year_month_day(date::sys_days(day) + date::days(1));
}

inline int positive_modulo(int i, int n) { return (i % n + n) % n; }

} // namespace

Calendar::Calendar(date::year_month page, date::year_month_day pillStartDate) {
    page_ = page;
    pillStartDate_ = pillStartDate;
    days_.resize(kDaysPerMonth);
}

const std::vector<Day>& Calendar::view() const {
    auto day = getFirstDayOfPage(page_);
    auto last_day = getLastDayOfPage(page_);
    uint i = 0;
    while (day <= last_day) {
        days_[i] = analyzeDay(day);
        day = getNextDay(day);
        ++i;
    }
    while (i < days_.size()) {
        days_[i] = analyzeDay(day);
        day = getNextDay(day);
        ++i;
    }
    return days_;
}

void Calendar::setCalendarPage(date::year_month date) { page_ = date; }
void Calendar::setPillStartDate(date::year_month_day date) {
    pillStartDate_ = date;
}

Day Calendar::analyzeDay(date::year_month_day date) const {
    Day result;
    result.index = uint(date.day());
    result.type = DayType::NORMAL;
    result.period = PeriodType::NONE;
    if (date.month() != page_.month() || date.year() != page_.year()) {
        result.type = DayType::BLANK;
    }
    auto delta = date::sys_days(date) - date::sys_days(pillStartDate_);
    uint cycleDay = positive_modulo(delta.count(), kPillPeriod);
    if (cycleDay >= kPillPeriod - kPeriodDays) {
        result.period = PeriodType::PERIOD;
    }
    return result;
}

} // namespace period_calendar