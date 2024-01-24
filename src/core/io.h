#ifndef CORE_IO_H
#define CORE_IO_H

#include "date.h"
#include <filesystem>

date::year_month_day loadDate(const std::filesystem::path& path);
void saveDate(date::year_month_day date, const std::filesystem::path& path);

#endif // CORE_IO_H