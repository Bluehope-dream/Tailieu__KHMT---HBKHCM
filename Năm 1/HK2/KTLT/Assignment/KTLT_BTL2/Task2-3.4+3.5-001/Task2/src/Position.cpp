#include "../include/Position.h"

Position::Position(int r, int c) : r(r), c(c)
{
    // TODO: implement

}

Position::Position(const string &str_pos)  // định dạng đọc thông tin  có dạng chuẩn là pos(r,c)
{
    // TODO: implement
    istringstream iss(str_pos);
    char ch;
    int row, col;
    iss>>ch>>row>>ch>>col>>ch;
    r = row;
    c= col;
}

int Position::getRow() const { return r; }

int Position::getCol() const { return c; }

void Position::setRow(int r)
{ // TODO: implement
    this ->r =r;
}

void Position::setCol(int c)
{
    // TODO: implement
    this -> c =c;
}

string Position::str() const
{
    // TODO: implement
    return "("+ to_string(r)+","+to_string(c)+")";
}