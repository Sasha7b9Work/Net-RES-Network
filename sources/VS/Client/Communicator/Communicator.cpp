// 2022/04/29 13:56:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Communicator/Communicator.h"
#include "Communicator/USB/USB.h"
#include "Communicator/HC12/HC12.h"


void Communicator::Update()
{
    USB::Update();

    HC12::Update();
}
