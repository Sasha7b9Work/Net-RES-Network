// 2023/06/01 09:44:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


#define DEF_GOVERNOR_MIN(_name, page_self, _min, _max, type) \
DEF_GOVERNOR(_name, "Предел мин", *page_self, nullptr, _min, _max, gset.measures.limit_min[type])

#define DEF_GOVERNOR_MAX(_name, page_self, _min, _max, type)    \
DEF_GOVERNOR(_name, "Предел макс", *page_self, nullptr, _min, _max, gset.measures.limit_max[type])

#define DEF_STATE_MIN(_name, page_self, type)   \
DEF_STATE(_name, "Значение мин", *page_self, nullptr, nullptr, type, true)

#define DEF_STATE_MAX(_name, page_self, type)   \
DEF_STATE(_name, "Значение макс", *page_self, nullptr, nullptr, type, false)


extern const DPage pageMain;


//-------------------------------------------------------------------------------------
void ClosePageTemperature(bool)
{
    PageMeasures::Temperature::self->Close();
}

DEF_BUTTON(bClosePageTemperature,
    "Закрыть",
    *PageMeasures::Temperature::self,
    ClosePageTemperature,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chTemperature,
    "Показывать",
    *PageMeasures::Temperature::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Нет", "Да"
)


DEF_GOVERNOR_MIN(gTemperatureLimitMin, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature);

DEF_GOVERNOR_MAX(gTemperatureLimitMax, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature);

DEF_STATE_MIN(sTemperatureValueMin, PageMeasures::Temperature::self, TypeMeasure::Temperature);

DEF_STATE_MAX(sTemperatureValueMax, PageMeasures::Temperature::self, TypeMeasure::Temperature);


DEF_PAGE_6(pageTemperature,
    "ТЕМПЕРАТУРА",
    *PageMeasures::self,
    nullptr,
    nullptr,
    chTemperature,
    gTemperatureLimitMin,
    gTemperatureLimitMax,
    sTemperatureValueMin,
    sTemperatureValueMax,
    bClosePageTemperature
)


//------------------------------------------------------------------------------------
void ClosePagePressure(bool)
{
    PageMeasures::Pressure::self->Close();
}

DEF_BUTTON(bClosePagePressure,
    "Закрыть",
    *PageMeasures::Pressure::self,
    ClosePagePressure,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chPressure,
    "Давление",
    *PageMeasures::Pressure::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Откл", "Вкл"
)

DEF_GOVERNOR_MIN(gPressureMin, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_GOVERNOR_MAX(gPressureMax, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_PAGE_4(pagePressure,
    "ДАВЛЕНИЕ",
    *PageMeasures::self,
    nullptr,
    nullptr,
    chPressure,
    gPressureMin,
    gPressureMax,
    bClosePagePressure
)


//-------------------------------------------------------------------------------------
void ClosePageHumidity(bool)
{
    PageMeasures::Humidity::self->Close();
}

DEF_BUTTON(bClosePageHumidity,
    "Закрыть",
    *PageMeasures::Humidity::self,
    ClosePageHumidity,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chHumidity,
    "Влажность",
    *PageMeasures::Humidity::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Нет", "Да"
)

DEF_GOVERNOR_MIN(gHumidityMin, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_GOVERNOR_MAX(gHumidityMax, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_PAGE_4(pageHumidity,
    "ВЛАЖНОСТЬ",
    *PageMeasures::self,
    nullptr,
    nullptr,
    chHumidity,
    gHumidityMin,
    gHumidityMax,
    bClosePageHumidity
)


//------------------------------------------------------------------------------------
void ClosePageDewPoint(bool)
{
    PageMeasures::DewPoint::self->Close();
}

DEF_BUTTON(bClosePageDewPoint,
    "Закрыть",
    *PageMeasures::DewPoint::self,
    ClosePageDewPoint,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chDewPoint,
    "Точка росы",
    *PageMeasures::DewPoint::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::DewPoint],
    "Откл", "Вкл"
)

DEF_GOVERNOR_MIN(gDewPointMin, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_GOVERNOR_MAX(gDewPointMax, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_PAGE_4(pageDewPoint,
    "ТОЧКА РОСЫ",
    *PageMeasures::self,
    nullptr,
    nullptr,
    chDewPoint,
    gDewPointMin,
    gDewPointMax,
    bClosePageDewPoint
)


static void CloseMeasures(bool)
{
    PageMeasures::self->Close();
};

DEF_BUTTON(bCloseMeasures,
    "Закрыть",
    *PageMeasures::self,
    CloseMeasures,
    nullptr,
    nullptr
)

DEF_PAGE_5(pageMeasures, //-V1027
    "ИЗМЕРЕНИЯ",
    pageMain,
    nullptr,
    nullptr,
    pageTemperature,
    pagePressure,
    pageHumidity,
    pageDewPoint,
    bCloseMeasures
)

const Page *const PageMeasures::self = (const Page *)&pageMeasures;
const Page *const PageMeasures::Temperature::self = (const Page *)&pageTemperature;
const Page *const PageMeasures::Pressure::self = (const Page *)&pagePressure;
const Page *const PageMeasures::Humidity::self = (const Page *)&pageHumidity;
const Page *const PageMeasures::DewPoint::self = (const Page *)&pageDewPoint;
