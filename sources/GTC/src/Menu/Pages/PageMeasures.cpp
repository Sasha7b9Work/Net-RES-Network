// 2023/06/01 09:44:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


#define DEF_GOVERNOR_MIN(_name, page_self, _min, _max, type) \
DEF_GOVERNOR(_name, "Ïğåäåë ìèí", *page_self, EmptyFuncOpenClose, _min, _max, gset.measures.min[type])

#define DEF_GOVERNOR_MAX(_name, page_self, _min, _max, type)    \
DEF_GOVERNOR(_name, "Ïğåäåë ìàêñ", *page_self, EmptyFuncOpenClose, _min, _max, gset.measures.max[type])


extern const DPage pageMain;


//-------------------------------------------------------------------------------------
void ClosePageTemperature()
{
    PageMeasures::Temperature::self->Close();
}

DEF_BUTTN(bClosePageTemperature,
    "Çàêğûòü",
    *PageMeasures::Temperature::self,
    EmptyFuncOpenClose,
    ClosePageTemperature
)

DEF_CHOICE_2(chTemperature,
    "Ïîêàçûâàòü",
    *PageMeasures::Temperature::self,
    EmptyFuncOpenClose,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Íåò", "Äà"
)


DEF_GOVERNOR_MIN(gTemperatureMin, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature)

DEF_GOVERNOR_MAX(gTemperatureMax, PageMeasures::Temperature::self, -30, 60, TypeMeasure::Temperature);


DEF_PAGE_4(pageTemperature,
    "ÒÅÌÏÅĞÀÒÓĞÀ",
    *PageMeasures::self,
    EmptyFuncOpenClose,
    chTemperature,
    gTemperatureMin,
    gTemperatureMax,
    bClosePageTemperature
)


//------------------------------------------------------------------------------------
void ClosePagePressure()
{
    PageMeasures::Pressure::self->Close();
}

DEF_BUTTN(bClosePagePressure,
    "Çàêğûòü",
    *PageMeasures::Pressure::self,
    EmptyFuncOpenClose,
    ClosePagePressure
)

DEF_CHOICE_2(chPressure,
    "Äàâëåíèå",
    *PageMeasures::Pressure::self,
    EmptyFuncOpenClose,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Îòêë", "Âêë"
)

DEF_GOVERNOR_MIN(gPressureMin, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_GOVERNOR_MAX(gPressureMax, PageMeasures::Pressure::self, 225, 825, TypeMeasure::Pressure);

DEF_PAGE_4(pagePressure,
    "ÄÀÂËÅÍÈÅ",
    *PageMeasures::self,
    EmptyFuncOpenClose,
    chPressure,
    gPressureMin,
    gPressureMax,
    bClosePagePressure
)


//-------------------------------------------------------------------------------------
void ClosePageHumidity()
{
    PageMeasures::Humidity::self->Close();
}

DEF_BUTTN(bClosePageHumidity,
    "Çàêğûòü",
    *PageMeasures::Humidity::self,
    EmptyFuncOpenClose,
    ClosePageHumidity
)

DEF_CHOICE_2(chHumidity,
    "Âëàæíîñòü",
    *PageMeasures::Humidity::self,
    EmptyFuncOpenClose,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Íåò", "Äà"
)

DEF_GOVERNOR_MIN(gHumidityMin, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_GOVERNOR_MAX(gHumidityMax, PageMeasures::Humidity::self, 10, 98, TypeMeasure::Humidity);

DEF_PAGE_4(pageHumidity,
    "ÂËÀÆÍÎÑÒÜ",
    *PageMeasures::self,
    EmptyFuncOpenClose,
    chHumidity,
    gHumidityMin,
    gHumidityMax,
    bClosePageHumidity
)


//------------------------------------------------------------------------------------
void ClosePageDewPoint()
{
    PageMeasures::DewPoint::self->Close();
}

DEF_BUTTN(bClosePageDewPoint,
    "Çàêğûòü",
    *PageMeasures::DewPoint::self,
    EmptyFuncOpenClose,
    ClosePageDewPoint
)

DEF_CHOICE_2(chDewPoint,
    "Òî÷êà ğîñû",
    *PageMeasures::DewPoint::self,
    EmptyFuncOpenClose,
    gset.display.show_measure[TypeMeasure::DewPoint],
    "Îòêë", "Âêë"
)

DEF_GOVERNOR_MIN(gDewPointMin, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_GOVERNOR_MAX(gDewPointMax, PageMeasures::DewPoint::self, -100, 100, TypeMeasure::DewPoint);

DEF_PAGE_4(pageDewPoint,
    "ÒÎ×ÊÀ ĞÎÑÛ",
    *PageMeasures::self,
    EmptyFuncOpenClose,
    chDewPoint,
    gDewPointMin,
    gDewPointMax,
    bClosePageDewPoint
)


static void CloseMeasures()
{
    PageMeasures::self->Close();
};

DEF_BUTTN(bCloseMeasures,
    "Çàêğûòü",
    *PageMeasures::self,
    EmptyFuncOpenClose,
    CloseMeasures
)

DEF_PAGE_5(pageMeasures, //-V1027
    "ÈÇÌÅĞÅÍÈß",
    pageMain,
    EmptyFuncOpenClose,
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
