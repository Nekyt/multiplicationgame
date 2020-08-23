#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "curses.h"
#include "string.h"



char *genProgBar();
void populateProgBar();
void readySetGO();
int centerPosition(int strLEN);
bool getIfNumber(int *number);
void waitFor(double sec);
void clearBeforeNextStage();
void UpdateMiddlePosition(char * text,short color);
int getonum();
int progress=0;
char progressBarComp[200];
void runStage(int stageNumber);
void betweenStages();
void runStages();
void endGame();
void Update();

int numberChosen,amountOfStages;
int numbersArr[]={1,2,3,4,5,6,7,8,9,10};int secondNumber;
char currentMult[20];
int answer;
int expectedAnswer;
bool useProgressBar=true;

char upperPosition[20],calcPosition[20], middlePosition[200],downPosition[200];
int main() {
    srand(time(0));


    initscr();

    start_here();

    endwin();

	return 0;

}


void start_here(){
    printw("Welcome!What do you want?\n");
    bool choiceMade=false;
    char choice[10];
    char st[]="start";

    while(!choiceMade){
    refresh();
    scanw("%s",choice);

    if(strcmp(choice,st)==0){
        printw("You chose game start!\n The game will start soon\n");
        choiceMade=true;
        game_start();
    }
    else{
        printw("sorry not understood\nPlease make a valid choice\n");
    }
    }
}


void populateProgBar(){
    int oneUnit=(int) 120/10;
    int progressBarV=progress*oneUnit;
    strcpy(progressBarComp,"");
    for(int i=0;i<progressBarV;i++){
         strcat(progressBarComp," ");
    }



}
void chooseNumber(){
    printw("Please enter the number you want to practice!\n");
    while(!getIfNumber(&numberChosen)){
        printw("Please enter a number !\n");
    }
    printw("You chose %d, AMAZING!\n",numberChosen);
    printw("Now choose the amount of stages:\n");

     while(!getIfNumber(&amountOfStages)){
        printw("Please enter a number !\n");
    }


}
bool getIfNumber(int *number){
    char tramp[10];
    scanw("%s",tramp);
    if(!(atoi(tramp)==0)){
         *number=atoi(tramp);
         return true;
    }
    else{
        return false;
    }


}

void game_start(){
    clear();
    refresh();
    chooseNumber();
    clear();refresh();

    runStages();
}

int centerPosition(int strLEN){
     int posl=60-(strLEN/2);
     return posl;
}
int gemtx(){
    int x,y;
    getyx(stdscr,y,x);
    return x;
}
int gemty(){
    int x,y;
    getyx(stdscr,y,x);
    return y;
}
void Update(){
    clear();
    //update position up
    move(2,centerPosition(strlen(upperPosition)));
    printw("%s",upperPosition); refresh();

    move(4,centerPosition(strlen(calcPosition)));
    printw("%s",calcPosition);refresh();




    //update the progress bar
    if(useProgressBar){
    populateProgBar();
    strcpy(downPosition,progressBarComp);
    }
    move(10,0);
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_WHITE);
    attron(COLOR_PAIR(1));
    printw("%s",downPosition);
    attroff(COLOR_PAIR(1));
    refresh();


}
void UpdateMiddlePosition(char * text,short color){
    /* 0 BLACK
    white 7
    COLOR_GREEN 2
    RED 4*/
    move(5,0);clrtoeol();

    strcpy(middlePosition,text);
    init_pair(3,color,0);
    attron(COLOR_PAIR(3));
    move(5,centerPosition(strlen(middlePosition)));
    printw("%s",middlePosition);refresh();
    attroff(COLOR_PAIR(3));
    refresh();

}
void informAboutAnswer(bool inform){
     if(inform==true){
        UpdateMiddlePosition("Amazing!",2);
        Sleep(700);
        move(5,0);clrtoeol();
     }
     else{
        UpdateMiddlePosition("YOU CAN DO BETTER!",4);
        Sleep(700);
        move(5,0);clrtoeol();
     }
}

void readySetGO(){
     UpdateMiddlePosition("Ready",7);
     Sleep(1000);

     UpdateMiddlePosition("SET?",7);
     Sleep(1000);

     init_pair(2,COLOR_GREEN,COLOR_WHITE);
     attron(COLOR_PAIR(2));
     for(int klm=0;klm<4;klm++){
        move(5,0);clrtoeol();
        refresh();
        Sleep(150);
        mvprintw(5,58,"GO!");
        refresh();
        Sleep(250);

     }

     attroff(COLOR_PAIR(2));

     UpdateMiddlePosition("",0);

}





void waitFor(double sec){
    clock_t start,current;
    start=clock();
    long diff=0;
    long secToWait=(long) (sec*CLOCKS_PER_SEC);
    while(diff<secToWait){
        current=clock();
        diff=(long) (current-start);
    }

}

int getonum(){
     int rr;
     do {
        rr=rand()%10;
     }
     while(numbersArr[rr]==-1);

    return numbersArr[rr];

}
void clearBeforeNextStage(){
    for(int m=1;m<=10;m++){
        numbersArr[m-1]=m;
    }
    progress=0;
}


//the actual game
void runStages(){
    for(int km=1;km<=amountOfStages;km++){
        runStage(km);
        betweenStages();
    }

    endGame();
}


void runStage(int stageNumber){
    clock_t timeToAnswer=((65-stageNumber*10)*CLOCKS_PER_SEC)/10;
    clock_t tnumberShown,tnumberGiv;
    char informStage[20];
    sprintf(informStage,"Stage %d",stageNumber);
    strcpy(upperPosition,informStage);Update();

    readySetGO();

    while(progress<10){
         secondNumber=getonum();
         expectedAnswer=secondNumber*numberChosen;
         sprintf(currentMult,"%d x %d",numberChosen,secondNumber);

         strcpy(calcPosition,currentMult);Update();
         tnumberShown=clock();

         move(6,59);
         if(!getIfNumber(&answer)){
            informAboutAnswer(false);
            continue;
         }
         tnumberGiv=clock();

         if((expectedAnswer!=answer)||((tnumberGiv-tnumberShown)>timeToAnswer)){
            informAboutAnswer(false);
            continue;
         }
         //answer right
         progress=progress+1;Update();

         informAboutAnswer(true);

         numbersArr[secondNumber-1]=-1;
    }
    clearBeforeNextStage();


}

void betweenStages(){
    /* for(in kz=0;kz<200;kz++){
        printw("Amazing")
     }*/
     strcpy(upperPosition,"");
     strcpy(middlePosition,"");
     strcpy(calcPosition,"");
     strcpy(downPosition,"");
     Update();
     mvprintw(0,0,"Press any key to continue...\n");

     getch();
}
//establish the certificate

void endGame(){
    clear();
    printw("Congratulations, you won the game!\n");
    printw("in order to get your certificate please enter the form below:\n");

    char name[15];
    char birthDate[15];
    clear();
    printw("please enter your name \n");
    scanw("%s",name);
    printw("please enter your birth date\n");
    scanw("%s",birthDate);

    //file creation
    FILE *fl=fopen("certificate.txt","w");
    fprintf(fl,"              Certificate\n\n"
            "This certificate along with the required legal documents\n"
            "Certifies that %s born the %s \n"
            "knows the multiplication table of %d\n\n",name,birthDate,numberChosen);

     time_t t = time(0);
     struct tm tm = *localtime(&t);
     fprintf(fl,"Established the %02d/%02d/%02d at %02d:%02d:%02d\n",tm.tm_mday,tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
     fclose(fl);
     exit(0);

}


