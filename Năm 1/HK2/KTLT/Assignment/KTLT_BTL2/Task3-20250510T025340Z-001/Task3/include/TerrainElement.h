#ifndef _H_TERRAIN_ELEMENT_H_
#define _H_TERRAIN_ELEMENT_H_

class Army; // Forward declaration

#include "Army.h"

//-----------------------------------------------------
// CLASS TerrainElement và các lớp dẫn xuất
//-----------------------------------------------------
class TerrainElement {
protected:
    Position pos; // Vị trí của yếu tố địa hình
    // Phương thức tính khoảng cách giữa hai vị trí
    double calDistance(const Position& pos1, const Position& pos2) {
        int rowLine = pos1.getRow() - pos2.getRow();
        int colLine = pos1.getCol() - pos2.getCol();
        return (sqrt(double(rowLine * rowLine + colLine * colLine)));
    }
    // Phương thức làm tròn 1 cách an toàn 
    int safeCeil(double value) {
        double dis = abs(value - round(value));
        return (dis < 1e-9) ? round(value) : ceil(value);
    }
public:
    TerrainElement(Position);
    virtual ~TerrainElement();
    // Phương thức thuần ảo: áp dụng hiệu ứng của yếu tố địa hình lên các quân đội.
    // (Chú ý: dùng tham số kiểu Army** theo đề bài.)
    virtual void getEffect(Army *army) = 0;
};

class Road : public TerrainElement {  // Lớp Road ĐƯỜNG MÒN
public:
    Road(Position pos) : TerrainElement(pos) {}
    // Đường mòn không có hiệu ứng
    ~Road() override;
    void getEffect(Army *army) override;
};

class Mountain : public TerrainElement { // Lớp rừng núi
public:
    Mountain(Position pos) : TerrainElement(pos) {}
    // Rừng núi: hiệu ứng áp dụng (stub) – áp dụng tác động đối với cả các đơn vị bộ binh và phương tiện
    void getEffect(Army *army) override;
    ~Mountain() override;
    void MountainEffect(double&addSum, double&minusSum,double &addIndex, double &minusIndex,UnitList *list,double &r);
};

class River : public TerrainElement {   // Lơp sống sâu 
public:
    River(Position pos) : TerrainElement(pos) {}
    // Sông: hiệu ứng giảm EXP 10% cho lực lượng bộ binh nếu nằm trong bán kính 2 đơn vị (stub)
    void getEffect(Army *army) override;
    ~River () override;
};

class Urban : public TerrainElement {   // Lớp khu dân cư 
public:
    Urban(Position pos) : TerrainElement(pos) {}
    // Khu dân cư: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
    ~Urban() override;
};

class Fortification : public TerrainElement {     // Lớp chiến hào 
public:
    Fortification(Position pos) : TerrainElement(pos) {}
    // Chiến hào: hiệu ứng (stub) – áp dụng theo mô tả đề bài
    void getEffect(Army *army) override;
    ~Fortification () override;
};

class SpecialZone : public TerrainElement {   // Lớp khu vực phi quân sự 
public:
    SpecialZone(Position pos) : TerrainElement(pos) {}
    // Khu vực phi quân sự: hiệu ứng (stub) – đặt attackScore của các đơn vị xung quanh về 0
    void getEffect(Army *army) override;
    ~SpecialZone() override; // Hủy để tránh thất thoát tài nguyên
};

#endif