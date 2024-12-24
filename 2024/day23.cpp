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
#include "mcqd.h"

namespace day23 {
std::string part1(std::istream& input)
{
    std::string line;
    std::set<std::string> computer_set;
    std::set<std::pair<std::string, std::string>> links;
    std::map<std::string, std::set<std::string>> neighbors;
    while (std::getline(input, line)) {
        auto a = line.substr(0, 2);
        auto b = line.substr(3);
        links.insert(std::minmax(a, b));
        computer_set.insert(a);
        computer_set.insert(b);
        neighbors[a].insert(b);
        neighbors[b].insert(a);
    }
    std::vector<std::string> computers(computer_set.begin(), computer_set.end());
    std::partition(computers.begin(), computers.end(), [](auto& c) { return c[0] == 't'; });

    std::set<std::array<std::string, 3>> paths;

    for (auto& a : computers) {
        if (a[0] != 't') {
            break;
        }
        for (auto it_b = neighbors[a].begin(); it_b != neighbors[a].end(); ++it_b) {
            auto& b = *it_b;
            for (auto it_c = std::next(it_b); it_c != neighbors[a].end(); ++it_c) {
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
    std::string line;
    std::set<std::string> computer_set;
    std::map<std::string, std::set<std::string>> neighbors;
    while (std::getline(input, line)) {
        auto a = line.substr(0, 2);
        auto b = line.substr(3);
        computer_set.insert(a);
        computer_set.insert(b);
        neighbors[a].insert(b);
        neighbors[b].insert(a);
    }

    std::vector<std::string> computers(computer_set.begin(), computer_set.end());

    bool** conn = new bool*[computers.size()];
    for (size_t i = 0; i < computers.size(); i++) {
        conn[i] = new bool[computers.size()];
        for (size_t j = 0; j < computers.size(); j++) {
            conn[i][j] = neighbors[computers[i]].contains(computers[j]);
        }
    }

    Maxclique m(conn, static_cast<int>(computers.size()));
    int* qmax;
    int qmaxsize = 0;
    m.mcq(qmax, qmaxsize);

    std::set<std::string> qmaxset;
    for (int i = 0; i < qmaxsize; i++) {
        qmaxset.insert(computers[qmax[i]]);
    }

    std::string result;
    for (auto& s : qmaxset) {
        result += s;
        result += ",";
    }
    result.pop_back();

    return result;
}
}

DayDescription Day23::description()
{
    DayDescription description { 23, 2024 };
    description.part1 = day23::part1;
    description.part2 = day23::part2;
    description.part1_test_result = "7";
    description.part2_test_result = "co,de,ka,ta";
    description.test_input = "kh-tc\nqp-kh\nde-cg\nka-co\nyn-aq\nqp-ub\ncg-tb\nvc-aq\ntb-ka\nwh-tc\nyn-cg\nkh-ub\nta-co\nde-co\ntc-td\ntb-wq\nwh-td\nta-ka\ntd-qp\naq-cg\nwq-ub\nub-vc\nde-ta\nwq-aq\nwq-vc\nwh-yn\nka-de\nkh-ta\nco-tc\nwh-qp\ntb-vc\ntd-yn";
    return description;
}
