#include "calendar_wrapper.h"

#include "calendar.h"

namespace period_calendar {

namespace {

date::year_month_day getToday() {
    return date::year_month_day(
        date::floor<date::days>(std::chrono::system_clock::now()));
}

} // namespace

CalendarWrapper::CalendarWrapper()
    : page_(getToday().year(), getToday().month()),
      calendar_(page_, getToday()) {}

CalendarWrapper::CalendarWrapper(date::year_month_day pillStartDay)
    : page_(getToday().year(), getToday().month()),
      calendar_(page_, pillStartDay) {}

const std::vector<Day>& CalendarWrapper::view() const {
    return calendar_.view();
}

void CalendarWrapper::setMonth(int monthIndex) {
    page_ = date::year_month(page_.year() / (monthIndex + 1));
    calendar_.setCalendarPage(page_);
}

void CalendarWrapper::setYear(int year) {
    page_ = date::year_month(date::year(year), page_.month());
    calendar_.setCalendarPage(page_);
}

date::year_month CalendarWrapper::setNextMonth() {
    page_ += date::months(1);
    calendar_.setCalendarPage(page_);
    return page_;
}

date::year_month CalendarWrapper::setPrevMonth() {
    page_ -= date::months(1);
    calendar_.setCalendarPage(page_);
    return page_;
}

} // namespace period_calendar