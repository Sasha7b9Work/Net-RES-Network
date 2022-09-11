// 2022/09/05 10:18:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Grid : public wxGrid
{
public:

    static Grid *Create(wxWindow *, const wxSize &);

    static Grid *self;

    void SetID(uint);

    void SetParameter(uint8, float);

    // Периодическое задание
    void UpdateArea();

private:

    Grid(wxWindow *, const wxSize &);
};