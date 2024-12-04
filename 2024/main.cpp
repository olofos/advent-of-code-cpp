#include <memory>
#include <vector>

#include "day.h"
#include "days.h"

int main()
{
    std::unique_ptr<Day> init[] { std::make_unique<Day1>(), std::make_unique<Day2>(), std::make_unique<Day3>(), std::make_unique<Day4>() };

    std::vector<std::unique_ptr<Day>> days { std::make_move_iterator(std::begin(init)), std::make_move_iterator(std::end(init)) };

    if (run_all(days)) {
        return 0;
    } else {
        return 1;
    }
}
