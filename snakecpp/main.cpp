#include <iostream>
#include "console.h"//functi windows pt consola
#include <cstdlib>
#include <conio.h>
#include <thread>
#include <fstream>
#include <string>
using namespace std;
void  Algoritm();
void ManageCoordonates();
 bool stopG=false;
 int x=10,y=10;
 int lastx,lasty;
 int foodx,foody;
 int lungimeSarpe=2;
 int puncte,hiscore;
bool aminceput;

 bool print;
   int coadax[400],coaday[400];
 enum Direction{
     SUS,
     JOS,
     STG,//stanga
     DRP,//dreapta
     ZERO
 };
 Direction direction=ZERO;
bool CheckFoodSpawn(int fx,int fy){
    if(fx==x || fy==y)
        return false;
      for(int i=0;i<lungimeSarpe;i++)
      if(coadax[i]==fx || coaday[i]==fy)
      return false;
return true;
}
void SpawnFood(){
     do{
      foodx=Random(3,19);
      foody=Random(2,19);
     }while(!CheckFoodSpawn(foodx,foody));
}

void Draw(){

     for(int i=1;i<=22;i++)
    {Set_ConsoleText_Color(BACKGROUND_BLUE |BACKGROUND_GREEN);
            cout<<"--";

        }cout<<endl;
   for(int i=1;i<=20;i++)
   {for(int j=1;j<=20;j++)
   {
      if(j==1)
      {Set_ConsoleText_Color(BACKGROUND_BLUE |BACKGROUND_GREEN);
            cout<<" |";}

               if(i==y && j==x){
              Set_ConsoleText_Color(FOREGROUND_GREEN| BACKGROUND_BLUE |BACKGROUND_GREEN|BACKGROUND_RED);
                cout<<"O ";
                Set_ConsoleText_White();
                print=true;

                }

                else
              if(i==foody && j==foodx)
                    {Set_ConsoleText_Color(FOREGROUND_RED| BACKGROUND_BLUE |BACKGROUND_GREEN|BACKGROUND_RED);
                    cout<<"O ";print =true;}
                else
                {
                    print=false;
                    for(int k=0;k<lungimeSarpe ;k++)
                        {if(i==coaday[k]&& j==coadax[k])
                        {    Set_ConsoleText_Color(FOREGROUND_GREEN|FOREGROUND_INTENSITY | BACKGROUND_BLUE |BACKGROUND_GREEN|BACKGROUND_RED);
                            cout<<"o ";
                     print=true;}
                     if( k>1 && x==coadax[k] && y==coaday[k])
                         {stopG=true;}

                     }
                }
                if(!print)
                {Set_ConsoleText_Color(BACKGROUND_BLUE |BACKGROUND_GREEN|BACKGROUND_RED);
                cout<<"  ";}

         if(j==20)
         {
    Set_ConsoleText_Color(BACKGROUND_BLUE |BACKGROUND_GREEN);
            cout<<" |";
          }
        }

      if(foodx==x && foody==y)//cand colectam puncte
        {SpawnFood();
        lungimeSarpe++;
        puncte=lungimeSarpe-2;
        if(puncte>hiscore)
        {hiscore=puncte;ofstream f2("save.txt");f2<<hiscore;f2.close();}
        }


   cout<<endl;
   }
    for(int i=1;i<=22;i++)
    {Set_ConsoleText_Color(BACKGROUND_BLUE |BACKGROUND_GREEN);
            cout<<"--";

        }



   Set_ConsoleText_Color(BACKGROUND_INTENSITY |FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
    cout<<endl<<"  PUNCTE:"<<puncte<<endl;
      cout<<"  SCOR MAX:"<<hiscore;
Set_ConsoleText_Color(BACKGROUND_INTENSITY);

}

int Input(){

do

  {if (GetAsyncKeyState('W') & 0x8000 && direction!=JOS) {

          direction=SUS;
        }
         if (GetAsyncKeyState('A') & 0x8000&& direction!=DRP) {

           direction=STG;
        }
         if (GetAsyncKeyState('S') & 0x8000 && direction!=SUS) {

           direction=JOS;
        }
         if (GetAsyncKeyState('D') & 0x8000 && direction!=STG) {

           direction=DRP;
        }




        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            stopG=true;


        }}while(!stopG);

}


void ProcessInput(){

   switch (direction){

        case SUS:
       {y--;}break;
       case JOS:
       {y++;}break;
       case STG:
       {x--;}break;
       case DRP:
       {x++;}break;


   }

   ManageCoordonates();
   Algoritm();

}
void ManageCoordonates()
{
    if(x<0)
    x=22;
    if(x>22)
        x=0;
    if(y>20)
        y=0;
    if(y<0)
        y=20;
}
void Algoritm(){
    for(int i=lungimeSarpe-1;i>0;i--)
        coadax[i]=coadax[i-1];
        coadax[0]=x;
     for(int i=lungimeSarpe-1;i>0;i--)
        coaday[i]=coaday[i-1];
        coaday[0]=y;
}


bool InitGame(){

 ifstream f("save.txt");
    f>>hiscore;
 f.close();
cout<<"       Controlati sarpele folosind tastele WASD,'O' de culoare rosie reprezitna mancarea"<<endl<<"           Apasati orice tasta pentru a continua......";
while(true)
    if (_kbhit())   //asteapta apasarea unei taste
        return true;


}

int main()
{
 if(InitGame())

{
     SpawnFood();


thread t(Input);//citeste input ul intr un thread separat,evitarea delayului de la tastatura



   while (!stopG) {

      ProcessInput();
     Draw();


        Sleep(200);
        system("cls");

    }



t.join();
}
    return 0;
}
