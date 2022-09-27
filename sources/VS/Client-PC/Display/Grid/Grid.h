// 2022/09/05 10:18:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <map>


class Grid : public wxGrid
{
public:

    static Grid *Create(wxWindow *, const wxSize &);

    static Grid *self;

    void SetMeasure(uint id, const wxColour color, uint8 type, float value);

private:

    Grid(wxWindow *, const wxSize &);

    //     <id, num_row>
    std::map<uint, int> rows;

    void SetCellValue(int row, int col, float, wxColor color);
    void SetCellValue(int row, int col, int, wxColor color);
};