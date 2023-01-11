#ifndef YUTIL_SRC_DATE_TIME_H_
#define YUTIL_SRC_DATE_TIME_H_
#include <chrono>
#include <ratio>
#include <string>

namespace yutil {

using std::string;

class DateTime {
 public:
  DateTime();
  DateTime(const string& iso);

  string toISO() const;

 private:
  std::chrono::duration<long long, std::milli> mills;

  struct date {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
  };

  static date dateFromDuration(
      std::chrono::duration<long long, std::milli> duration);

  static date dateFromIso(const string& iso);

  static std::chrono::duration<long long, std::milli> durationFromDate(
      const date& date);
};

}  // namespace yutil

#endif  // !YUTIL_SRC_DATE_TIME_H_
