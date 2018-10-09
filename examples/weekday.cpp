#include <iostream>
#include <string>

#include "weekday.switch.hpp"

int main()
{
    std::string in;
    std::cin >> in;

    switch( weekday( in ) )
    {
    case weekday( "Monday" ):
    case weekday( "Tuesday" ):
    case weekday( "Wednesday" ):
    case weekday( "Thursday" ):
    case weekday( "Friday" ):
        std::cout << "Work\n";
        break;
    case weekday( "Saturday" ):
    case weekday( "Sunday" ):
        std::cout << "Home\n";
        break;
    default:
        std::cout << "Unknown\n";
    }

    return 0;
}
