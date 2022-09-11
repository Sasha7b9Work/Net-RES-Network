// 2022/09/05 10:18:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Grid/Grid.h"
#include "Display/Display.h"


Grid::Grid(wxWindow *parent, wxWindowID id, const wxPoint &position, const wxSize &size) :
    wxGrid(parent, id, position, size)
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
