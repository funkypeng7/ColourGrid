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


// int getTimeSince()
// {
    // using namespace std::this_thread; // sleep_for, sleep_until
    // using namespace std::chrono; // nanoseconds, system_clock, seconds
//     auto begin = chrono::high_resolution_clock::now();    
//     int x;
//     cin >> x;      // wait for user input
//     auto end = chrono::high_resolution_clock::now();    
//     auto dur = end - begin;
//     auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
//     return ms;
// }