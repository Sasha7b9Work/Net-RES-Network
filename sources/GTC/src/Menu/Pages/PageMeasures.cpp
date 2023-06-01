// 2023/06/01 09:44:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;


//-------------------------------------------------------------------------------------
void ClosePageTemperature()
{
    PageMeasures::Temperature::self->Close();
}

DEF_BUTTN(bClosePageTemperature,
    "Çàêğûòü",
    *PageMeasures::Temperature::self,
    EmptyVV,
    ClosePageTemperature
)

DEF_CHOICE_2(chTemperature,
    "Ïîêàçûâàòü",
    *PageMeasures::Temperature::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Temperature],
    "Íåò", "Äà"
)

int s_n;


DEF_GOVERNOR(gTemperatureMin,
    "Ïğåäåë ìèí",
    *PageMeasures::Temperature::self,
    EmptyVV,
    0, 100,
    gset.measures.min[TypeMeasure::Temperature]
)

DEF_GOVERNOR(gTemperatureMax,
    "Ïğåäåë ìàêñ",
    *PageMeasures::Temperature::self,
    EmptyVV,
    0, 100,
    gset.measures.min[TypeMeasure::Temperature]
)

DEF_PAGE_4(pageTemperature,
    "ÒÅÌÏÅĞÀÒÓĞÀ",
    *PageMeasures::self,
    EmptyVV,
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
    EmptyVV,
    ClosePagePressure
)

DEF_CHOICE_2(chPressure,
    "Äàâëåíèå",
    *PageMeasures::Pressure::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Pressure],
    "Îòêë", "Âêë"
)

DEF_PAGE_2(pagePressure,
    "ÄÀÂËÅÍÈÅ",
    *PageMeasures::self,
    EmptyVV,
    chPressure,
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
    EmptyVV,
    ClosePageHumidity
)

DEF_CHOICE_2(chHumidity,
    "Âëàæíîñòü",
    *PageMeasures::Humidity::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::Humidity],
    "Íåò", "Äà"
)

DEF_PAGE_2(pageHumidity,
    "ÂËÀÆÍÎÑÒÜ",
    *PageMeasures::self,
    EmptyVV,
    chHumidity,
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
    EmptyVV,
    ClosePageDewPoint
)

DEF_CHOICE_2(chDewPoint,
    "Òî÷êà ğîñû",
    *PageMeasures::DewPoint::self,
    EmptyVV,
    gset.display.show_measure[TypeMeasure::DewPoint],
    "Îòêë", "Âêë"
)

DEF_PAGE_2(pageDewPoint,
    "ÒÎ×ÊÀ ĞÎÑÛ",
    *PageMeasures::self,
    EmptyVV,
    chDewPoint,
    bClosePageDewPoint
)


static void CloseMeasures()
{
    PageMeasures::self->Close();
};

DEF_BUTTN(bCloseMeasures,
    "Çàêğûòü",
    *PageMeasures::self,
    EmptyVV,
    CloseMeasures
)

DEF_PAGE_5(pageMeasures, //-V1027
    "ÈÇÌÅĞÅÍÈß",
    pageMain,
    EmptyVV,
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
