#include "../unit_test_Task1.hpp"

bool UNIT_TEST_Task1::Task120()
{
    // Test Infantry MORTARSQUAD không điều chỉnh số lượng
    string name = "Task120";
    //! data ------------------------------------
    int quantity = 10;
    int weight = 25;
    Position pos(5, 5);
    InfantryType it =  SPECIALFORCES; // giá trị 2
    //! process ---------------------------------
    Infantry infantry(quantity, weight, pos, it);
    int score = infantry.getAttackScore();
    
    //! expect ----------------------------------
    // Base: 2*56 + 5*8 = 112 + 40 = 152, computeSingleDigit cho ra 3 -> không thay đổi.
    int expectedScore = 549;
    stringstream expectStream;
    expectStream << expectedScore;
    
    //! output ----------------------------------
    stringstream output;
    output << score;
    
    //! remove data -----------------------------
    
    //! result ----------------------------------
    return printResult(output.str(), expectStream.str(), name);
}
