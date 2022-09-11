// 2022/09/05 10:18:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Grid : public wxGrid
{
public:

    Grid(wxWindow *, const wxPoint &, const wxSize &);

    void SetID(uint);

    void SetParameter(uint8, float);

private:
};