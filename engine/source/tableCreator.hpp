#pragma once

#include <string>
#include <vector>
#include <podofo/podofo.h>

struct Cell
{
    std::string text;
    double width{0.};
    double height{0.};
};

class Table
{
public:
    //explicit Table();
    explicit Table(double x, double y, double width = 0.0, double height = 0.0);

    void SetColWidth();

private:
    double MmToDot(double mm);
    double tableX{0.};
    double tableY{0.};
    double tableWidth{0.};
    double tableHeight{0.};

    std::vector<std::vector<Cell>> rows;
};