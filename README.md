<h2>To Run</h2>
Open main.cpp in vscode and press f5\n
If that doesn't work follow https://code.visualstudio.com/docs/cpp/config-clang-mac\n
Just don't change task.json or launch.json\n

<h2>Header overview</h2>
Honestly i'm still figuing out how to use them heres what I figured out\n
    - at the top of each header put\n
        #ifndef FILENAME_H_\n
        #define FILENAME_H_\n
    - at the bottom put\n
        #endif\n
    - between those declare any functions you want to access from another file like\n
        unsigned long createRGB(int, int, int);\n
        with a semicolon instead of { }\n
        then declare the function as normal in the file the header is named after\n
    - For <b>Global Variables</b> place them in global.h with extern at the front\n
        i.e. extern std::vector<int> prevCoords;\n
        then declare the variable in main.cpp as per normal\n

