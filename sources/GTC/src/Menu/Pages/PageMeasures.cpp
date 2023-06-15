// 2023/06/01 09:44:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


#define DEF_GOVERNOR_MIN(_name, page_self, _min, _max, type) \
DEF_GOVERNOR(_name, "Ïğåäåë ìèí", *page_self, nullptr, _min, _max, gset.measures.min[type])

#define DEF_GOVERNOR_MAX(_name, page_self, _min, _max, type)    \
DEF_GOVERNOR(_name, "Ïğåäåë ìàêñ", *page_self, nullptr, _min, _max, gset.measures.max[type])


extern const DPage pageMain;


//-------------------------------------------------------------------------------------
void ClosePageTemperature(bool)
{
    PageMeasures::Temperature::self->Close();
}

DEF_BUTTN(bClosePageTemperature,
    "Çàêğûòü",
    *PageMeasures::Temperature::self,
    ClosePageTemperature,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chTemperature,
    "Ïîêàçûâàòü",
    *PageMeasures::Temperature::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Íåò", "Äà"
)


DEF_GOVERNOR_MIN(gTemperatureMin, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature)

DEF_GOVERNOR_MAX(gTemperatureMax, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature);


DEF_PAGE_4(pageTemperature,
    "ÒÅÌÏÅĞÀÒÓĞÀ",
    *PageMeasures::self,
    nullptr,
    nullptr,
    chTemperature,
    gTemperatureMin,
    gTemperatureMax,
    bClosePageTemperature
)


//------------------------------------------------------------------------------------
void ClosePagePressure(bool)
{
    PageMeasures::Pressure::self->Close();
}

DEF_BUTTN(bClosePagePressure,
    "Çàêğûòü",
    *PageMeasures::Pressure::self,
    ClosePagePressure,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chPressure,
    "Äàâëåíèå",
    *PageMeasures::Pressure::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Îòêë", "Âêë"
)

DEF_GOVERNOR_MIN(gPressureMin, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_GOVERNOR_MAX(gPressureMax, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_PAGE_4(pagePressure,
    "ÄÀÂËÅÍÈÅ",
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

DEF_BUTTN(bClosePageHumidity,
    "Çàêğûòü",
    *PageMeasures::Humidity::self,
    ClosePageHumidity,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chHumidity,
    "Âëàæíîñòü",
    *PageMeasures::Humidity::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Íåò", "Äà"
)

DEF_GOVERNOR_MIN(gHumidityMin, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_GOVERNOR_MAX(gHumidityMax, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_PAGE_4(pageHumidity,
    "ÂËÀÆÍÎÑÒÜ",
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

DEF_BUTTN(bClosePageDewPoint,
    "Çàêğûòü",
    *PageMeasures::DewPoint::self,
    ClosePageDewPoint,
    nullptr,
    nullptr
)

DEF_CHOICE_2(chDewPoint,
    "Òî÷êà ğîñû",
    *PageMeasures::DewPoint::self,
    nullptr,
    nullptr,
    gset.display.show_measure[TypeMeasure::DewPoint],
    "Îòêë", "Âêë"
)

DEF_GOVERNOR_MIN(gDewPointMin, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_GOVERNOR_MAX(gDewPointMax, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_PAGE_4(pageDewPoint,
    "ÒÎ×ÊÀ ĞÎÑÛ",
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

DEF_BUTTN(bCloseMeasures,
    "Çàêğûòü",
    *PageMeasures::self,
    CloseMeasures,
    nullptr,
    nullptr
)

DEF_PAGE_5(pageMeasures, //-V1027
    "ÈÇÌÅĞÅÍÈß",
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
