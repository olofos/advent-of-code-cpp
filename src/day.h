#include <iostream>
#include <optional>
#include <string>

class Day {
public:
    virtual std::string part1(std::istream& input) = 0;
    virtual std::string part2(std::istream& input) = 0;
    virtual int day() = 0;
    virtual ~Day() {};

    virtual std::optional<std::string> part1_test_result() { return std::nullopt; };
    virtual std::optional<std::string> part2_test_result() { return std::nullopt; };
    virtual std::optional<std::string> test_input() { return std::nullopt; };

    std::string test();
    std::string run();
};

class Day1 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 1; }

    std::optional<std::string> part1_test_result() override { return "11"; };
    std::optional<std::string> part2_test_result() override { return "31"; };
    std::optional<std::string> test_input() override
    {
        return "3   4\n4   3\n2   5\n1   3\n3   9\n3   3";
    }
};

class Day2 : public Day {
public:
    std::string part1(std::istream& input) override;
    std::string part2(std::istream& input) override;
    int day() override { return 2; }

    std::optional<std::string> part1_test_result() override { return "2"; };
    std::optional<std::string> part2_test_result() override { return "4"; };
    std::optional<std::string> test_input() override
    {
        return "7 6 4 2 1\n1 2 7 8 9\n9 7 6 2 1\n1 3 2 4 5\n8 6 4 4 1\n1 3 6 7 9";
    }
};