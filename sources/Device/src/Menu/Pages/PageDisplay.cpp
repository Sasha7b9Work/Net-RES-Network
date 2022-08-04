// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;
extern const DPage pageDisplay;
extern const DPage pageMeasures;


DEF_CHOICE_2( chPressure,
    "Давление",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chIllumination,
    "Освещённость",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Illumination],
    "Откл", "Вкл"
)

#ifdef TYPE_1
DEF_CHOICE_2(chVelocity,
    "Скорость",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Velocity],
    "Откл", "Вкл"
)
#endif

DEF_CHOICE_2(chTemperature,
    "Температура",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Откл", "Вкл"
)

DEF_CHOICE_2(chHumidity,
    "Влажность",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Откл", "Вкл"
)

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};

DEF_BUTTN( bCloseMeasures,
    "Закрыть",
    pageMeasures,
    CloseMeasures
)

#ifdef TYPE_1
DEF_PAGE_6( pageMeasures,
    "ИЗМЕРЕНИЯ",
    pageDisplay,
    chPressure,
    chIllumination,
    chTemperature,
    chHumidity,
    chVelocity,
    bCloseMeasures
)
#endif

#ifdef TYPE_2
DEF_PAGE_5(pageMeasures,
    "ИЗМЕРЕНИЯ",
    pageDisplay,
    chPressure,
    chIllumination,
    chTemperature,
    chHumidity,
    bCloseMeasures
)
#endif


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}

DEF_BUTTN( bClosePageDisplay,
    "Закрыть",
    pageDisplay,
    ClosePageDisplay
)

DEF_PAGE_2(pageDisplay,
    "ДИСПЛЕЙ",
    pageMain,
    pageMeasures,
    bClosePageDisplay
)

const Page * const PageDisplay::self = (const Page *)&pageDisplay;
const Page * const PageDisplay::PageMeasures::self = (const Page *)&pageMeasures;
