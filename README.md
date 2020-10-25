##To Run
Open main.cpp in vscode and press `f5`  
If that doesn't work follow https://code.visualstudio.com/docs/cpp/config-clang-mac  
Just don't change task.json or launch.json  

##Header overview
Honestly i'm still figuing out how to use them heres what I figured out  
- at the top of each header put  
  `#ifndef FILENAME_H_`  
  `#define FILENAME_H_`  
- at the bottom put  
  `#endif`  
- between those declare any functions you want to access from another file like  
    `unsigned long createRGB(int, int, int);`  
    but with a semicolon instead of a { }  
    then declare the function as normal in the file the header is named after  
- For <b>Global Variables</b> place them in global.h with extern at the front  
    i.e. extern std::vector<int> prevCoords;  
    then declare the variable in main.cpp as per normal  

