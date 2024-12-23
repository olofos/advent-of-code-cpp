#include <algorithm>
#include <array>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day23 {
std::string part1(std::istream& input)
{
    std::string line;
    std::vector<std::string> computers;
    std::set<std::pair<std::string, std::string>> links;
    std::map<std::string, std::set<std::string>> links_from;
    while (std::getline(input, line)) {
        auto a = line.substr(0, 2);
        auto b = line.substr(3);
        links.insert(std::minmax(a, b));
        computers.push_back(a);
        computers.push_back(b);
        links_from[a].insert(b);
        links_from[b].insert(a);
    }
    std::partition(computers.begin(), computers.end(), [](auto& c) { return c[0] == 't'; });

    std::set<std::array<std::string, 3>> paths;

    for (auto& a : computers) {
        if (a[0] != 't') {
            break;
        }
        for (auto it_b = links_from[a].begin(); it_b != links_from[a].end(); ++it_b) {
            auto& b = *it_b;
            for (auto it_c = std::next(it_b); it_c != links_from[a].end(); ++it_c) {
                auto& c = *it_c;
                if (links.find(std::minmax(b, c)) != links.end()) {
                    std::array<std::string, 3> cs = { a, b, c };
                    std::sort(cs.begin(), cs.end());
                    paths.insert(cs);
                }
            }
        }
    }

    return std::to_string(paths.size());
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day23::description()
{
    DayDescription description { 23, 2024 };
    description.part1 = day23::part1;
    description.part2 = day23::part2;
    description.part1_test_result = "7";
    // description.part2_test_result = "";
    description.test_input = "kh-tc\nqp-kh\nde-cg\nka-co\nyn-aq\nqp-ub\ncg-tb\nvc-aq\ntb-ka\nwh-tc\nyn-cg\nkh-ub\nta-co\nde-co\ntc-td\ntb-wq\nwh-td\nta-ka\ntd-qp\naq-cg\nwq-ub\nub-vc\nde-ta\nwq-aq\nwq-vc\nwh-yn\nka-de\nkh-ta\nco-tc\nwh-qp\ntb-vc\ntd-yn";
    return description;
}
