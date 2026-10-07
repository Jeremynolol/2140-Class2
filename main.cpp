/*
 * Full Name:     Jeremy Calle  
 * Student ID:    002581809
 * Course:        EECE 2140 - Computing Fundamentals for Engineers
 * Section:       Mon, Wed - 2:50-4:30
 * Semester:      Fall 2026
 * Assignment:    Homework 2 - Calendar Toolkit
 * Compilation:   g++ -std=c++11 main.cpp -o main
 * Description:   A menu-driven calendar toolkit that validates dates, finds
 *                the day of the week for any date from 1900 through 2100,
 *                counts the days between two dates, and runs a seeded
 *                weekday quiz.
 */

#include <iostream>
#include <cstdlib>   // rand, srand
#include <cassert>   // assert

// ---------------------------------------------------------------------
// Types and global named constants — do not modify
// ---------------------------------------------------------------------
enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

const int MIN_YEAR = 1900;   // earliest year the toolkit supports
const int MAX_YEAR = 2100;   // latest year the toolkit supports

// ---------------------------------------------------------------------
// Function declarations — do not modify these interfaces.
// The full contract of each function is in the TODO comment at its
// definition below main(). You may add your own helper functions.
// ---------------------------------------------------------------------
bool isLeapYear(int year);
int daysInMonth(int month, int year);
bool isValidDate(int day, int month, int year);
int daysSince1900(int day, int month, int year);
Weekday dayOfWeek(int day, int month, int year);
void printWeekdayName(Weekday weekday, bool abbreviated = false);
void printDate(int day, int month, int year);
int daysBetween(int day1, int month1, int year1, int day2, int month2, int year2);
int randomInRange(int low, int high);
void randomDate(int& day, int& month, int& year, int minYear, int maxYear);

// ---------------------------------------------------------------------
// main() — provided verbatim from the assignment. Do NOT modify it.
// ---------------------------------------------------------------------
int main()
{
    int choice = 0;

    std::cout << "=== EECE 2140 Calendar Toolkit ===" << std::endl;

    do
    {
        std::cout << std::endl
                  << "1) Day of the week for a date" << std::endl
                  << "2) Days between two dates" << std::endl
                  << "3) Weekday quiz" << std::endl
                  << "4) Exit" << std::endl
                  << "Enter your choice: ";

        if (!(std::cin >> choice))
        {
            choice = 4;   // end of input (or unreadable input) acts as Exit
        }

        switch (choice)
        {
            case 1:
            {
                int day = 0, month = 0, year = 0;
                std::cout << "Enter a date (day month year): ";
                std::cin >> day >> month >> year;
                if (!isValidDate(day, month, year))
                {
                    std::cout << "Invalid date." << std::endl;
                    break;
                }
                printDate(day, month, year);
                std::cout << " is a ";
                printWeekdayName(dayOfWeek(day, month, year));
                std::cout << "." << std::endl;
                break;
            }
            case 2:
            {
                int day1 = 0, month1 = 0, year1 = 0;
                int day2 = 0, month2 = 0, year2 = 0;
                std::cout << "Enter the first date (day month year): ";
                std::cin >> day1 >> month1 >> year1;
                std::cout << "Enter the second date (day month year): ";
                std::cin >> day2 >> month2 >> year2;
                if (!isValidDate(day1, month1, year1) || !isValidDate(day2, month2, year2))
                {
                    std::cout << "Invalid date." << std::endl;
                    break;
                }

                std::cout << "From ";
                printWeekdayName(dayOfWeek(day1, month1, year1), true);
                std::cout << " ";
                printDate(day1, month1, year1);
                std::cout << " to ";
                printWeekdayName(dayOfWeek(day2, month2, year2), true);
                std::cout << " ";
                printDate(day2, month2, year2);
                int difference = daysBetween(day1, month1, year1, day2, month2, year2);
                std::cout << ": " << difference
                          << ((difference == 1 || difference == -1) ? " day" : " days") << std::endl;
                break;
            }
            case 3:
            {
                unsigned int seed = 0;
                int numQuestions = 0, correct = 0;
                std::cout << "Random seed: ";
                std::cin >> seed;
                std::cout << "Number of questions: ";
                std::cin >> numQuestions;
                if (numQuestions < 1)
                {
                    std::cout << "Number of questions must be at least 1." << std::endl;
                    break;
                }

                std::srand(seed);   // seed ONCE, before any random numbers are drawn
                for (int question = 1; question <= numQuestions; ++question)
                {
                    int day = 0, month = 0, year = 0, guess = -1;
                    randomDate(day, month, year, MIN_YEAR, MAX_YEAR);

                    std::cout << "Question " << question << ": what day of the week was ";
                    printDate(day, month, year);
                    std::cout << "? (0=Sun 1=Mon 2=Tue 3=Wed 4=Thu 5=Fri 6=Sat): ";
                    std::cin >> guess;

                    Weekday answer = dayOfWeek(day, month, year);
                    if (guess == static_cast<int>(answer))
                    {
                        ++correct;
                        std::cout << "Correct!" << std::endl;
                    }
                    else
                    {
                        std::cout << "Not quite -- it was a ";
                        printWeekdayName(answer);
                        std::cout << "." << std::endl;
                    }
                }
                std::cout << "Quiz score: " << correct << " of " << numQuestions
                          << "." << std::endl;
                break;
            }
            case 4:
                std::cout << "Goodbye." << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

// =====================================================================
// Function definitions — complete each TODO.
// Each body below is a placeholder that lets the template compile;
// replace it with your own implementation.
// =====================================================================

// TODO: isLeapYear
//   Parameter: year - a year in the Gregorian calendar.
//   Returns:   true if year is a leap year and false otherwise. A year is
//              a leap year when it is divisible by 4, except that a year
//              divisible by 100 is a leap year only if it is also
//              divisible by 400 (2000 and 2024 are leap years; 1900 and
//              2100 are not).
bool isLeapYear(int year)  //century leap years are leap years only when divisible by 400
{
    if (year % 400 == 0)
    {
        return true;
    }
    else if (year % 100 == 0)
    {
        return false;
    }
    else if (year % 4 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TODO: daysInMonth
//   Parameters:   month - a month number (1 = January ... 12 = December);
//                 year - the year the month belongs to.
//   Precondition: 1 <= month <= 12. Enforce this precondition with assert.
//   Returns:      the number of days in that month of that year (28 or 29
//                 for February, depending on whether year is a leap year).
int daysInMonth(int month, int year)
{
    assert(month >= 1 && month <= 12); // group months by their num of days, feb is seperate

    switch (month)
{
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    case 2:
        if (isLeapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        } 
    }
    return 0;
}



// TODO: isValidDate
//   Parameters: day, month, year - a candidate date (any int values).
//   Returns:    true if MIN_YEAR <= year <= MAX_YEAR, 1 <= month <= 12,
//               and 1 <= day <= the number of days in that month of that
//               year; false otherwise. Must not violate the precondition
//               of any function it calls, for ANY input values.
//   Constraint: use daysInMonth for the number of days in the month.
bool isValidDate(int day, int month, int year) //check year and month before using daysinmonth
{
    if (year < MIN_YEAR || year > MAX_YEAR)
    {
    return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > daysInMonth(month, year))
    {
        return false;
    }
    return true;
}

// TODO: daysSince1900
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year). Enforce this with assert.
//   Returns:      the number of days from 1 January 1900 to the given date
//                 (0 for 1 January 1900, 1 for 2 January 1900, 31 for
//                 1 February 1900, and so on).
int daysSince1900(int day, int month, int year)
{
    assert(isValidDate(day, month, year));

    int totalDays = 0;

    //adding days for the complete year before target

    for (int currentYear = MIN_YEAR; currentYear < year; currentYear++)
    {
        if (isLeapYear(currentYear))
    {
        totalDays = totalDays + 366;
    }
    else
    {
        totalDays = totalDays + 365;
    }
}

for (int currentMonth = 1; currentMonth < month; currentMonth++)
{
    totalDays = totalDays + daysInMonth(currentMonth, year);
}

totalDays = totalDays + day - 1;

return totalDays;
}





// TODO: dayOfWeek
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year). Enforce this with assert.
//   Returns:      the Weekday on which the date falls. (1 January 1900 was
//                 a Monday.)
//   Constraint:   use daysSince1900.
Weekday dayOfWeek(int day, int month, int year)
{
    assert(isValidDate(day, month, year));

    int days = daysSince1900(day, month, year);

    int weekdayNumber = (days + 1) % 7;

    return static_cast<Weekday>(weekdayNumber);
}

// TODO: printWeekdayName
//   Parameters: weekday - any Weekday value;
//               abbreviated - selects the form of the name (default false).
//   Behavior:   prints the weekday's name to std::cout: the full name
//               (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday,
//               Saturday) when abbreviated is false, or the three-letter
//               form (Sun, Mon, Tue, Wed, Thu, Fri, Sat) when it is true.
//               No spaces and no newline before or after the name.
//   Returns:    nothing.
void printWeekdayName(Weekday weekday, bool abbreviated)
{
    if (abbreviated)
    {
        switch (weekday)
        {
            case Weekday::Sunday:
            std::cout << "Sun";
            break;

            case Weekday::Monday:
            std::cout << "Mon";
            break;
            
            case Weekday::Tuesday:
            std::cout << "Tue";
            break;
            
            case Weekday::Wednesday:
            std::cout << "Wed";
            break;
           
            case Weekday::Thursday:
            std::cout << "Thu";
            break;
            
            case Weekday::Friday:
            std::cout << "Fri";
            break;
            
            case Weekday::Saturday:
            std::cout << "Sat";
            break;
        }
    }
    else
    {
        switch (weekday)
        {
            case Weekday::Sunday:
            std::cout << "Sunday";
            break;
            
            case Weekday::Monday:
            std::cout << "Monday";
            break;
            
            case Weekday::Tuesday:
            std::cout << "Tuesday";
            break;
            
            case Weekday::Wednesday:
            std::cout << "Wednesday";
            break;
            
            case Weekday::Thursday:
            std::cout << "Thursday";
            break;
            
            case Weekday::Friday:
            std::cout << "Friday";
            break;
            
            case Weekday::Saturday:
            std::cout << "Saturday";
            break;
        }
    }
}


// TODO: printDate
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year).
//   Behavior:     prints the date to std::cout in the form YYYY-MM-DD, with
//                 the month and the day always printed as two digits
//                 (for example, 2026-09-05). No spaces and no newline.
//   Returns:      nothing.
void printDate(int day, int month, int year)
{
    assert(isValidDate(day, month, year));

    std::cout << year << "-";

    if (month < 10)
    {
        std::cout << "0";
    }
    std::cout << month << "-";

    if (day < 10)
    {
        std::cout << "0";
    }
    std::cout << day;
}

// TODO: daysBetween
//   Parameters:   day1, month1, year1 - the first date;
//                 day2, month2, year2 - the second date.
//   Precondition: both dates are valid.
//   Returns:      the number of days from the first date to the second:
//                 positive when the second date is later, negative when it
//                 is earlier, and 0 when the dates are the same.
//   Constraint:   use daysSince1900.
int daysBetween(int day1, int month1, int year1, int day2, int month2, int year2)
{
    assert(isValidDate(day1, month1, year1));
    assert(isValidDate(day2, month2, year2));

    return daysSince1900(day2, month2, year2)
    - daysSince1900(day1, month1, year1);
}

// TODO: randomInRange
//   Parameters:   low, high - the bounds of the range.
//   Precondition: low <= high and (high - low) <= RAND_MAX.
//   Returns:      a pseudorandom integer between low and high, inclusive,
//                 obtained from rand(). Every value in the range must be
//                 possible.
//   Constraint:   do not call srand in this function.
int randomInRange(int low, int high)
{
    assert(low <= high);
    assert(high - low <= RAND_MAX);

    return ( rand() % (high - low + 1)) + low;

}

// TODO: randomDate
//   Parameters:    day, month, year - output parameters (call-by-reference);
//                  minYear, maxYear - the range of years to draw from.
//   Precondition:  MIN_YEAR <= minYear <= maxYear <= MAX_YEAR; the random
//                  number generator has already been seeded by main().
//   Postcondition: day, month, and year hold a pseudorandom valid date
//                  with minYear <= year <= maxYear, drawn in exactly this
//                  order, each by its own call to randomInRange:
//                    1. year  from randomInRange(minYear, maxYear)
//                    2. month from randomInRange(1, 12)
//                    3. day   from randomInRange(1, number of days in that
//                             month of that year)
//                  No other random numbers are drawn.
//   Constraint:   do not call srand in this function.
void randomDate(int& day, int& month, int& year, int minYear, int maxYear)
{
    assert(minYear >= MIN_YEAR);
    assert(minYear <= maxYear);
    assert(maxYear <= MAX_YEAR);

    year = randomInRange(minYear, maxYear);
    month = randomInRange(1, 12);
    day = randomInRange(1, daysInMonth(month, year));
    
}
