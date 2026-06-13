#ifndef _H_LIBERATIONARMY_H_
#define _H_LIBERATIONARMY_H_

#include "Army.h"
// Class cho quân đội giải phóng LiberationArmy
class LiberationArmy : public Army
{
private:
    Unit **unitArray;       // For temporary
    //int size_V = 0;         // For temporary: vehicle count
    // int size_I = 0;         // For temporary: infantry count
    int findNearestFibonacci(int value);
    // Dùng phương thức kế thừa protected cho một tổ hợp 
    // vector<Unit*> knapsack(vector<Unit*> units, int maxScore);  // Hàm tìm ra tổ hợp trả về 
    // Unit* cloneUnit(Unit* unit); Đã viết ở phần Army có thể sử dụng kế thừa của Army 
    vector <Unit*> setOfInfantry, setOfVehicle,A,B;
public:
    LiberationArmy(Unit **unitArray, int size, string name);
    void fight(Army *enemy, bool defense) override;
    string str() const override;
    ~LiberationArmy();

    // Phương thức xóa tổ hợp khỏi danh sách 
    // Ý tưởng sẽ trả về các tổ hợp infantry và vehicle của quân ta và kẻ thù trả về tổ hợp phù hợp 
    void upload (UnitList*) override;  // Cập nhật lại các chỉ số cho kịp thời cho Quân Giair phóng 
    void eraseInvalidCombo(vector<Unit*>&);
    void clearVector(vector<Unit*>&); // Hàm hỗ trợ cho việc xóa các vector cho lệnh xóa các tổ hợp trên 
};

#endif