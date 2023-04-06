// 2023/04/04 08:29:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/NEO-M8N/NEO-M8N.h"
#include <cstring>


namespace NEO_M8N
{
    static void Parse(char *);

    static char buffer[100] = { '\0' };

    char *GetData() { return buffer; }
}


void NEO_M8N::Init()
{

}


void NEO_M8N::ReceiveNewSymbolHandler(char symbol)
{
    static bool in_mode_receive = false;                // Если true, то находимся в режиме приёма данных

    if (in_mode_receive)
    {
        static char data[256];
        static int pointer = 0;

        if (symbol == 0x0d)
        {
            data[pointer] = '\0';
            Parse(data);
            in_mode_receive = false;
            pointer = 0;
        }
        else
        {
            data[pointer++] = symbol;
        }
    }
    else
    {
        static const char *request = "$GPGGA";

        static int ptr = 0;

        if (symbol == request[ptr])
        {
            ptr++;
            
            if (ptr == (int)std::strlen(request))
            {
                ptr = 0;
                in_mode_receive = true;
            }
        }
    }
}


void NEO_M8N::Parse(char *data)
{
#define MAX_LENGTH 20

    uint length = std::strlen(data);

    if (length > MAX_LENGTH)
    {
        data += (length - MAX_LENGTH);
    }

    std::strcpy(buffer, (length == 0) ? "NONE" : data);
}
