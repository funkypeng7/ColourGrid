#include "functions.h"

unsigned long createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

std::string createHexString(unsigned long hexValue)
{
    const unsigned red = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
    const unsigned green = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
    const unsigned blue = ((hexValue) & 0xFF);  
    char hexcol[16];

    snprintf(hexcol, sizeof hexcol, "%02x%02x%02x", red, green, blue);
    return hexcol;
}

