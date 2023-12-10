// 2022/09/05 10:18:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Grid/Grid.h"
#include "Data/Sensors.h"


using namespace std;


Grid *Grid::self = nullptr;


Grid *Grid::Create(wxWindow *parent, const wxSize &size)
{
    self = new Grid(parent, size);

    return self;
}


Grid::Grid(wxWindow *parent, const wxSize &size) :
    wxGrid(parent, wxID_ANY, { 0, 0 }, size)
{
    create_width = size.x;

    CreateGrid(0, 0);

    AppendCols(TypeMeasure::NumMeasures() + 1);

    EnableEditing(false);

    DisableCellEditControl();

    SetRowLabelSize(0);

    SetColLabelValue(0, "ID");

    for (int meas = 0; meas < TypeMeasure::Count; meas++)
    {
        int col = TypeMeasure::NumColumn((TypeMeasure::E)meas);

        if (col >= 0)
        {
            SetColLabelValue(TypeMeasure::NumColumn((TypeMeasure::E)meas), wxString(TypeMeasure::GetTitle((TypeMeasure::E)meas)) +
                wxString("\n") + wxString(TypeMeasure::GetUnits((TypeMeasure::E)meas)));
        }
    }

    StretchColumns();

//    wxScrollHelperBase::SetScrollbars(20, 20, 5, 5);
}


void Grid::StretchColumns()
{
    int width = GetSize().x;

    int size = width / TypeMeasure::NumMeasures();

    for (int i = 0; i < TypeMeasure::NumMeasures(); i++)
    {
        SetColSize(i, size);
    }
}


void Grid::SetMeasure(uint id, const wxColour &color, uint8 type, float value)
{
    if (id == 0)
    {
        return;
    }

    auto row = rows.find(id);

    if (row == rows.end()) 
    {
        AppendRows(1);

        rows.emplace(pair<uint, int>(id, GetNumberRows() - 1));

        SetCellValue(GetNumberRows() - 1, 0, (int)id, color);
    }

    row = rows.find(id);

    TypeMeasure::E type_meas = (TypeMeasure::E)type;

    SetCellValue(row->second, TypeMeasure::NumColumn(type_meas), (float)value, color);
}


void Grid::SetCellValue(int row, int col, float value, const wxColour &color)
{
    if (col >= 0)
    {
        SetCellTextColour(row, col, color);

        wxGrid::SetCellValue(row, col, wxString::Format("%10.2f", value));
    }
}


void Grid::SetCellValue(int row, int col, int value, const wxColour &color)
{
    if (col >= 0)
    {
        SetCellTextColour(row, col, color);

        wxGrid::SetCellValue(row, col, wxString::Format("%08X", value));
    }
}


void Grid::StretchEntireFrame()
{
    wxSize size = GetParent()->GetClientSize();

    SetMinSize(size);
    SetMaxSize(size);

    SetSize(size);

    StretchColumns();
}
