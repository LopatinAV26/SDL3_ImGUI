#include "tableCreator.hpp"

Table::Table(double x, double y, double width, double height)
    : tableX{x}, tableY{y}, tableWidth{width}, tableHeight{height}
{
    
}

double Table::MmToDot(double mm)
{
    constexpr double dot = 25.4 / 72.0; // 0.3528 mm
    return mm / dot;
}
