// 2022/09/05 10:18:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Grid/Grid.h"
#include "Display/Display.h"


Grid *Grid::self = nullptr;


Grid *Grid::Create(wxWindow *parent, const wxSize &size)
{
    self = new Grid(parent, size);

    return self;
}


Grid::Grid(wxWindow *parent, const wxSize &size) :
    wxGrid(parent, wxID_ANY, { 0, 0 }, size)
{
    CreateGrid(0, 0);

    AppendRows(1);
    AppendCols(6);

    EnableEditing(false);

    DisableCellEditControl();

    SetRowLabelSize(0);

    SetColLabelValue(0, "ID");

    for (int meas = 0; meas < TypeMeasure::Count; meas++)
    {
        SetColLabelValue(meas + 1, wxString(TypeMeasure::GetTitle((TypeMeasure::E)meas)) +
            wxString("\n") + wxString(TypeMeasure::GetUnits((TypeMeasure::E)meas)));
    }

    wxScrollHelperBase::SetScrollbars(20, 20, 5, 5);
}


void Grid::SetID(uint id)
{
    SetCellValue(0, 0, wxString::Format("%d", id));
}


void Grid::SetParameter(uint8 type, float value)
{
    SetCellValue(0, type + 1, wxString::Format("%10.2f", value));
}
