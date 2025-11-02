#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main() {
    boost::gregorian::date national_college_entrance_exam =
        boost::gregorian::from_string("2026-6-7");
    boost::gregorian::date endfield_posible_open_test_date =
        national_college_entrance_exam - boost::gregorian::days(100);
    std::cout << "终末地可能公测日期: "
              << boost::gregorian::to_iso_extended_string(endfield_posible_open_test_date) << "\n";

    boost::gregorian::date now = boost::gregorian::day_clock::local_day();
    std::cout << "距终末地公测还有: " << endfield_posible_open_test_date - now << " 天\n";
}