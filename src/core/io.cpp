#include "io.h"

#include <fstream>

date::year_month_day loadDate(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file for reading.");
    }
    int year, month, day;
    file >> year >> month >> day;
    if (!file.eof()) {
        throw std::runtime_error("Error: Invalid data in file.");
    }
    return date::year_month_day{date::year(year), date::month(month),
                                date::day(day)};
}

void saveDate(date::year_month_day date, const std::filesystem::path& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file for writing.");
    }
    file << date.year() << ' ' << static_cast<unsigned int>(date.month()) << ' '
         << date.day();
}