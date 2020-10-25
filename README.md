## To Download
1. Open Terminal
2. Create and navigate to a directory called "Programming" using `mkdir Programming` 
   - use `ls` to see all directorys(folders) in current directory
   - use `cd directoryName` to navigate to a directory
   - I would recommend creating this directory in your home folder, which is where terminal first opens up
3. When inside (your terminal should say something like `MacBook-Pro:Programming username$`) use `git clone https://github.com/funkypeng7/ColourGrid.git` to make a local copy

## To Push
1. Stage changes with `git add .`
   - make sure you are inside your ColourGrid directory
2. Commit changes with `git commit` 
   - Set vscode as your default editor with `git config --global core.editor "code --wait"`
   - On the first line type the title, keep it short, max 50 char
   - Have one blank line
   - After that add as much information as you need, keep it shorter than 72 characters per line, there is a line to indicate max length
   - Close file to finish commit
3. Push changes with `git push`


## To Run
Open main.cpp in vscode and press `f5` this will run it in debug mode click the arrow at the top of vscode to start. You will need to run the simulator in debug mode.  
To run release version press `cmd shift B` while in main.cpp to build the executable, then in terminal locate the file and run `open main` as main is the name of the file.  
<!-- If that doesn't work follow https://code.visualstudio.com/docs/cpp/config-clang-mac  
- **Don't change the task.json or launch.json** -->

## Header overview
Honestly i'm still figuing out how to use them here's what i've figured out so far
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

