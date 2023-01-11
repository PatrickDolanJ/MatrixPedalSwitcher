#ifndef FLASH
#define FLASH

#include <Arduino.h>


static String readStringFromFlash(const char *str)
{
    char c;
    String wordString;
    unsigned int index = 0;
    if (!str)
        return;
    while ((c = pgm_read_byte(str++)))
    {
        wordString += c;
        index++;
    }
    return wordString;
}
#endif // !FLASH