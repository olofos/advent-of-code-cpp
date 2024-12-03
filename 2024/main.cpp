#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

int main()
{
    std::vector<std::shared_ptr<Day>> days = { std::make_shared<Day1>(), std::make_shared<Day2>(), std::make_shared<Day3>() };

    if (run_all(days)) {
        return 0;
    } else {
        return 1;
    }
}
