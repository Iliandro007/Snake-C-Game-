#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED
#include <windows.h>
#include <random>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const WORD redText = FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD greenText = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

 void Set_ConsoleText_Color(WORD culoare){

 SetConsoleTextAttribute(hConsole, culoare);

}
int Random(int a,int b){

 int min =a;
    int max = b;

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a distribution for the range
    std::uniform_int_distribution<int> distribution(min, max);

    // Generate a random number within the specified range
    int randomNum = distribution(gen);

    // Output the random number
   return randomNum;


}

 void Set_ConsoleText_White(){
SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

#endif // CONSOLE_H_INCLUDED
