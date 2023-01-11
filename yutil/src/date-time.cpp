// Alrorithms from:
// http://howardhinnant.github.io/date_algorithms.html#days_from_civil
#include "date-time.h"
#include <cctype>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>

namespace yutil {

#define DAY_MILLS    86400000
#define HOUR_MILLS   3600000
#define MINUTE_MILLS 60000
#define SECOND_MILLS 1000

DateTime::DateTime() {
  auto now      = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  mills = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

DateTime::DateTime(const string& iso) {
  date d = dateFromIso(iso);
  mills  = durationFromDate(d);
}

string DateTime::toISO() const {
  auto [year, month, day, hour, minute, second, millisecond] =
      dateFromDuration(mills);

  std::stringstream ss;

  ss << std::setfill('0') << std::setw(4) << year << "-" << std::setw(2)
     << month << "-" << std::setw(2) << day << "T" << std::setw(2) << hour
     << ":" << std::setw(2) << minute << ":" << std::setw(2) << second << "."
     << std::setw(3) << millisecond << "Z";

  return ss.str();
}

DateTime::date DateTime::dateFromDuration(
    std::chrono::duration<long long, std::milli> duration) {
  long long mills = duration.count();

  long long days          = mills / DAY_MILLS;
  long long leftoverMills = mills - (days * DAY_MILLS);
  int       hours         = leftoverMills / HOUR_MILLS;
  leftoverMills           = leftoverMills - (hours * HOUR_MILLS);
  int minutes             = leftoverMills / MINUTE_MILLS;
  leftoverMills           = leftoverMills - (minutes * MINUTE_MILLS);
  int seconds             = leftoverMills / SECOND_MILLS;
  leftoverMills           = leftoverMills - (seconds * SECOND_MILLS);

  days += 719468;
  long long era = (days >= 0 ? days : days - 146096) / 146097;
  long long doe = days - era * 146097;
  long long yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
  int       y   = yoe + era * 400;
  long long doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
  long long mp  = (5 * doy + 2) / 153;
  int       d   = doy - (153 * mp + 2) / 5 + 1;
  int       m   = mp < 10 ? mp + 3 : mp - 9;
  y             = y + (m <= 2);

  return {y, m, d, hours, minutes, seconds, static_cast<int>(leftoverMills)};
}

DateTime::date DateTime::dateFromIso(const string& iso) {
  std::regex r{
      "^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})[tT ]"
      "([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2})\\.?([0-9]{1,3})?"};
  std::smatch match;
  if (!std::regex_search(iso, match, r)) {
    throw std::invalid_argument("invalid date string [" + iso + "]");
  }
  if (match.size() < 8) {
    throw std::invalid_argument("invalid date string [" + iso + "]");
  }

  date d{stoi(match[1]),
         stoi(match[2]),
         stoi(match[3]),
         stoi(match[4]),
         stoi(match[5]),
         stoi(match[6]),
         0};

  if (match[7] != "") {
    d.millisecond = stoi(match[7]);
  }

  return d;
}

std::chrono::duration<long long, std::milli> DateTime::durationFromDate(
    const DateTime::date& date) {
  long long year        = date.year;
  long long month       = date.month;
  long long day         = date.day;
  long long hour        = date.hour;
  long long minute      = date.minute;
  long long second      = date.second;
  long long millisecond = date.millisecond;

  year -= month <= 2;
  long long era = (year >= 0 ? year : year - 399) / 400;
  long long yoe = static_cast<unsigned>(year - era * 400);
  long long doy = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;
  long long doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  long long epocDays = era * 146097 + static_cast<long long>(doe) - 719468;

  long long epocMills = epocDays * DAY_MILLS;
  epocMills += hour * HOUR_MILLS;
  epocMills += minute * MINUTE_MILLS;
  epocMills += second * SECOND_MILLS;
  epocMills += millisecond;

  return std::chrono::duration<long long, std::milli>(epocMills);
}

}  // namespace yutil
