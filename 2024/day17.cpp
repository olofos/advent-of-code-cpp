#include <algorithm>
#include <iostream>
#include <istream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "days.h"

namespace day17 {
bool expect(std::istream& input, std::string_view expected)
{
    auto old_width = input.width();
    input.width(expected.size());
    std::string actual;
    if (input >> actual) {
        input.width(old_width);
        if (actual != expected) {
            throw std::runtime_error("Parse error. Expected '" + std::string(expected) + "' but got '" + actual + "'");
        }
        return true;
    } else {
        return false;
    }
}

struct CPU {
    uint64_t a, b, c, init_a, init_b, init_c;
    uint8_t pc = 0;
    std::vector<uint8_t> program;
    std::string program_string;
    std::string output;

    void run();
    uint64_t get_combo(uint8_t) const;
    void reset()
    {
        a = init_a;
        b = init_b;
        c = init_c;
        pc = 0;
        output.clear();
    }
};

uint64_t CPU::get_combo(uint8_t operand) const
{
    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
        return operand;
    case 4:
        return a;
    case 5:
        return b;
    case 6:
        return c;
    }
    throw std::runtime_error("invalid operand");
}

void CPU::run()
{
    while (pc < program.size() - 1) {
        auto instr = program[pc++];
        auto operand = program[pc++];

        switch (instr) {
        case 0: // adv
            a = a >> get_combo(operand);
            break;

        case 1: // bxl
            b = b ^ operand;
            break;

        case 2: // bst
            b = get_combo(operand) % 8;
            break;

        case 3: // jnz
            if (a != 0) {
                pc = operand;
            }
            break;

        case 4: // bxc
            b = b ^ c;
            break;

        case 5: // out
            if (!output.empty()) {
                output += ",";
            }
            output += std::to_string(get_combo(operand) % 8);
            break;

        case 6: // bdv
            b = a >> get_combo(operand);
            break;

        case 7: // cdv
            c = a >> get_combo(operand);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const CPU& cpu)
{
    os << "Register A: " << cpu.a << std::endl;
    os << "Register B: " << cpu.b << std::endl;
    os << "Register C: " << cpu.c << std::endl;
    os << "Program: ";
    for (auto& value : cpu.program) {
        os << value << " ";
    }
    return os;
}

CPU parse(std::istream& input)
{
    CPU cpu;
    expect(input, "Register");
    expect(input, "A:");
    input >> cpu.init_a;

    expect(input, "Register");
    expect(input, "B:");
    input >> cpu.init_b;

    expect(input, "Register");
    expect(input, "C:");
    input >> cpu.init_c;

    expect(input, "Program:");
    input >> cpu.program_string;

    for (std::size_t i = 0; i < cpu.program_string.size(); i += 2) {
        cpu.program.push_back(cpu.program_string[i] - '0');
    }

    cpu.reset();
    return cpu;
}

std::string part1(std::istream& input)
{
    auto cpu = parse(input);
    cpu.run();
    return cpu.output;
}

std::string part2(std::istream& input)
{
    throw std::runtime_error("not implemented");
}
}

DayDescription Day17::description()
{
    DayDescription description { 17, 2024 };
    description.part1 = day17::part1;
    description.part2 = day17::part2;
    description.part1_test_result = "5,7,3,0";
    // description.part2_test_result = "117440";
    description.test_input = "Register A: 2024\nRegister B: 0\nRegister C: 0\n\nProgram: 0,3,5,4,3,0";
    return description;
}
