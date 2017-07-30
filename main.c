#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define HUPLAYER 88
#define AIPLAYER 79

#define TRUE  1
#define FALSE 0

//Global Vars
int openS[9] = {1,2,3,4,5,6,7,8,9};
int tempS[9] = {1,2,3,4,5,6,7,8,9};
int status = 9;

//Prototyped functions
void buildB();
void getInput();
void ai();
int checkWin(int player,int b[9]);
int alphaBeta(int depth,int board[9],int mM);


int main() {
    //generate random number 1 or 2 and decide who goes first
    srand(time(NULL));
    int r = rand() % 2;
    if(r == 1){printf("Player goes first.\n");}else{printf("AI goes First.\n");}

    //Main Game loop
    while(status != 0) {
        if(r == 1) {
            //Player Move
            buildB();
            getInput();
            if (status == 0) {
                printf("No more moves\n");
                break;
            }
            buildB();

            //AI Move
            ai();
            printf("AI MOVES!!!!!\n\n\n");
            if (status == 0) {
                printf("No more moves\n");
                break;
            }
        }else{
            //AI Move
            ai();
            printf("AI MOVES!!!!!\n\n\n");
            if (status == 0) {
                printf("No more moves\n");
                break;
            }
            buildB();

            //Player Move
            getInput();
            if (status == 0) {
                printf("No more moves\n");
                break;
            }
            buildB();
        }
    }
}
void buildB(){
    for(int i = 0;i<9;i++){
        if(i == 2 || i == 5 || i == 8){
            if(openS[i] == 88){
                printf(" %c \n",'X');
            }else if(openS[i] == 79){
                printf(" %c \n",'O');
            }else{
                printf(" %d \n",openS[i]);
            }
            if(i == 2 || i == 5){
                printf("============\n");
            }
        }else{
            if(openS[i] == 88){
                printf(" %c |",'X');
            }else if(openS[i] == 79){
                printf(" %c |",'O');
            }else{
                printf(" %d |",openS[i]);
            }
        }
    }
}
void getInput(){
    int i,j;
    printf("make your selection!");
    scanf("%d",&i);
    openS[i-1] = 88;
    tempS[i-1] = 88;
    status -=1;
    j = checkWin(HUPLAYER,openS);
    if(j == 1){status = 0;printf("Holy Hell you beat the AI!\n");}
}
int checkWin(int player,int b[9]) {
    if (b[0] == player && b[1] == player && b[2] == player ||
        b[3] == player && b[4] == player && b[5] == player ||
        b[6] == player && b[7] == player && b[8] == player ||
        b[0] == player && b[3] == player && b[6] == player ||
        b[1] == player && b[4] == player && b[7] == player ||
        b[2] == player && b[5] == player && b[8] == player ||
        b[0] == player && b[4] == player && b[8] == player ||
        b[2] == player && b[4] == player && b[6] == player)
    {
        return TRUE;
    }else{
        return FALSE;
    }
}
void ai(){
    int j,tS,wC;
    int bS = -1;
    int bM;
    for(int i = 0;i<9;i++){
        if(openS[i] != 88 && openS[i] != 79){
            tempS[i] = 79;
            wC = checkWin(AIPLAYER,tempS);
            if(wC == TRUE){
                bM = i;
                break;
            }
            tS = alphaBeta(status-1,tempS,88);
            if(tS>bS){bM = i;bS=tS;}
            tempS[i] = i;
        }
    }
    openS[bM] = 79;
    tempS[bM] = 79;
    status -= 1;
    j = checkWin(AIPLAYER,openS);
    if(j == TRUE){status = 0;printf("HA! The AI won and you lost\n");}
}
int alphaBeta(int depth, int board[9],int mM){
    int bV = 0;
    int j = checkWin(mM,board);

    //Terminal State Checker. Will check for terminal states in game and return value for it.
    if(j == TRUE) {
        if (mM == HUPLAYER) {
            return -10;
        } else {
            return 10;
        }
    }
    if(depth == 0)return 0;
    //If terminal state is not found we will recurse Alpha Beta until we find a winning or losing combo
    for(int i = 0;i<9;i++){
        if(board[i] != 88 && board[i] != 79) {
                            //AI player Loop
            if (mM == AIPLAYER) {
                board[i] = 79;
                bV += alphaBeta(depth - 1, board, 88);
                board[i] = i;
                if(bV > 0)return bV;
            }else{          //Human player check.
                board[i] = 88;
                bV += alphaBeta(depth - 1, board, 79);
                board[i] = i;
                if(bV < 0)return bV;
                board[i] = i;
            }
        }
    }
    return bV;
}