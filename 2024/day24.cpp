#include <algorithm>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day24 {
struct Rule {
    std::string src1;
    std::string src2;
    std::string dest;
    std::string op;
};

std::string part1(std::istream& input)
{
    std::map<std::string, uint8_t> values;
    std::vector<Rule> rules;

    std::string line;

    while (getline(input, line)) {
        if (line == "") {
            break;
        }
        std::stringstream ss(line);
        std::string name;
        ss >> name;
        name.pop_back();
        int value;
        ss >> value;
        values[name] = static_cast<uint8_t>(value);
    }
    while (getline(input, line)) {
        std::stringstream ss(line);
        std::string src1;
        ss >> src1;
        std::string op;
        ss >> op;
        std::string src2;
        ss >> src2;
        std::string delim;
        ss >> delim;
        std::string dest;
        ss >> dest;
        rules.push_back({ src1, src2, dest, op });
    }

    while (!rules.empty()) {
        decltype(rules) next_rules;
        for (auto& rule : rules) {
            if (values.contains(rule.src1) && values.contains(rule.src2)) {
                auto v1 = values[rule.src1];
                auto v2 = values[rule.src2];
                uint8_t result = 0;
                if (rule.op == "AND") {
                    result = v1 & v2;
                } else if (rule.op == "OR") {
                    result = v1 | v2;
                } else if (rule.op == "XOR") {
                    result = v1 ^ v2;
                } else {
                    throw std::runtime_error("invalid op " + rule.op);
                }
                values[rule.dest] = result;
            } else {
                next_rules.push_back(rule);
            }
        }
        rules = std::move(next_rules);
    }

    uint64_t result = 0;
    for (auto it = values.rbegin(); it != values.rend(); it++) {
        auto& [name, value] = *it;
        if (name.front() == 'z') {
            result = result << 1 | values[name];
        }
    }
    return std::to_string(result);
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day24::description()
{
    DayDescription description { 24, 2024 };
    description.part1 = day24::part1;
    description.part2 = day24::part2;
    description.part1_test_result = "2024";
    // description.part2_test_result = "";
    description.test_input = "x00: 1\nx01: 0\nx02: 1\nx03: 1\nx04: 0\ny00: 1\ny01: 1\ny02: 1\ny03: 1\ny04: 1\n\nntg XOR fgs -> mjb\ny02 OR x01 -> tnw\nkwq OR kpj -> z05\nx00 OR x03 -> fst\ntgd XOR rvg -> z01\nvdt OR tnw -> bfw\nbfw AND frj -> z10\nffh OR nrd -> bqk\ny00 AND y03 -> djm\ny03 OR y00 -> psh\nbqk OR frj -> z08\ntnw OR fst -> frj\ngnj AND tgd -> z11\nbfw XOR mjb -> z00\nx03 OR x00 -> vdt\ngnj AND wpb -> z02\nx04 AND y00 -> kjc\ndjm OR pbm -> qhw\nnrd AND vdt -> hwm\nkjc AND fst -> rvg\ny04 OR y02 -> fgs\ny01 AND x02 -> pbm\nntg OR kjc -> kwq\npsh XOR fgs -> tgd\nqhw XOR tgd -> z09\npbm OR djm -> kpj\nx03 XOR y03 -> ffh\nx00 XOR y04 -> ntg\nbfw OR bqk -> z06\nnrd XOR fgs -> wpb\nfrj XOR qhw -> z04\nbqk OR frj -> z07\ny03 OR x01 -> nrd\nhwm AND bqk -> z03\ntgd XOR rvg -> z12\ntnw OR pbm -> gnj";
    return description;
}
