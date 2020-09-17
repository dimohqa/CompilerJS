#include "gtest/gtest.h"
#include "../../Lexer/Lexer.h"
#include "../Parser.h"
#include <iostream>
#include <string>

using namespace std;

class TestParser: public ::testing::Test {
protected:
    TestParser() {}
    ~TestParser() {}
};

TEST(TestParser, oneOpPlus) {
    EXPECT_EQ(1, 1);
    std::cout << "lol";
}

/*int main(int argc, char** argv) {
    string filepath = "/home/nitro/university/CompilerJS/js/substr.js";
    ifstream file = ifstream(filepath);
    Lexer lexer(file);
    Parser parser(lexer);

    unique_ptr<bool> fatalError(new bool(false));
    parser.parse(fatalError);
    //executable_file
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/