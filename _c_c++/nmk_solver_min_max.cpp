
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DISABLED -1
#define FREE_SPACE 0
#define PLAYER_1 1
#define PLAYER_2 2
#define NO_WIN 0
#define FIRST_PLAYER_WINS 1
#define SECOND_PLAYER_WINS -1
#define BOTH_PLAYERS_TIE 0

enum Mode{
    Normal,
    Cut,
    Extended,
};

enum Orientation{
    MIN,
    MAX,
};

inline void FreeMemoryNM(int **board, int &N, int &M){
    for(int i=0; i<N; i++)
        free(board[i]);
    free(board);
};

inline int **AlocateMemoryNM(int **board, int &N, int &M){
    static int n,m;
    if(n==N&&m==M)
        return board;
    if(board!=NULL){
        FreeMemoryNM(board, n, m);
    }
    board = (int**)malloc(N*sizeof(int*)); //N to Y // M to X
    for(int i=0; i<N; i++)
        board[i] = (int*)malloc(M*sizeof(int));
    n=N; m=M;
    return board;
}

inline void PrintBoard(int **board, int &N, int &M){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

//inline int CheckWinCondition(int **board, int &N, int &M, int &K){
//    int streak1=0, streak2=0;
//    for(int i=0; i<N; i++){
//        for(int j=0; j<M; j++){         //Horizontal
//            if(board[i][j]==PLAYER_1){
//                if(streak2)
//                    streak2=0;
//                streak1++;
//            }
//            else if(board[i][j]==PLAYER_2){
//                if(streak1)
//                    streak1=0;
//                streak2++;
//            }
//            else{
//                streak1=0;
//                streak2=0;
//            }
//            if(streak1>=K)
//                return PLAYER_1;
//            else if(streak2>=K)
//                return PLAYER_2;
//        }
//        streak1=0;
//        streak2=0;
//    }
//    for(int j=0; j<M; j++){
//        for(int i=0; i<N; i++){         //Vertical
//            if(board[i][j]==PLAYER_1){
//                if(streak2)
//                    streak2=0;
//                streak1++;
//            }
//            else if(board[i][j]==PLAYER_2){
//                if(streak1)
//                    streak1=0;
//                streak2++;
//            }
//            else{
//                streak1=0;
//                streak2=0;
//            }
//            if(streak1>=K)
//                return PLAYER_1;
//            else if(streak2>=K)
//                return PLAYER_2;
//        }
//        streak1=0;
//        streak2=0;
//    }
//    streak1=0;
//    streak2=0;
//    for(int i=0; i<N; i++){
//        for(int j=0; j<M; j++){         //Left Bevel
//            if(board[i][j]==PLAYER_1){
//                if(streak2)
//                    streak2=0;
//                while( i+streak1<N && j-streak1>=0){
//                    if(board[i+streak1][j-streak1]==PLAYER_1){
//                        streak1++;
//                    }
//                    else{
//                        if(streak1>=K)
//                            return PLAYER_1;
//                        else{
//                            streak1=0;
//                            break;
//                        }
//                    }
//                if(streak1>=K)
//                    return PLAYER_1;
//                }
//                streak1=0;
//            }
//            else if(board[i][j]==PLAYER_2){
//                if(streak1)
//                    streak1=0;
//                while( i+streak2<N && j-streak2>=0){
//                    if(board[i+streak2][j-streak2]==PLAYER_2)
//                        streak2++;
//                    else{
//                        if(streak2>=K)
//                            return PLAYER_2;
//                        else{
//                            streak2=0;
//                            break;
//                        }
//                    }
//                if(streak2>=K)
//                    return PLAYER_2;
//                }
//                streak2=0;
//            }
//        }
//    }
//    for(int i=0; i<N; i++){
//        for(int j=0; j<M; j++){        //Right Bevel
//            if(board[i][j]==PLAYER_1){
//                if(streak2)
//                    streak2=0;
//                while( i+streak1<N && j+streak1<M ){
//                    if(board[i+streak1][j+streak1]==PLAYER_1)
//                        streak1++;
//                    else{
//                        if(streak1>=K)
//                            return PLAYER_1;
//                        else{
//                            streak1=0;
//                            break;
//                        }
//                    }
//                if(streak1>=K)
//                    return PLAYER_1;
//                }
//                streak1=0;
//            }
//            else if(board[i][j]==PLAYER_2){
//                if(streak1)
//                    streak1=0;
//                while( i+streak2<N && j+streak2<M ){
//                    if(board[i+streak2][j+streak2]==PLAYER_2)
//                        streak2++;
//                    else{
//                        if(streak2>=K)
//                            return PLAYER_2;
//                        else{
//                            streak2=0;
//                            break;
//                        }
//                    }
//                if(streak2>=K)
//                    return PLAYER_2;
//                }
//                streak2=0;
//            }
//        }
//    }
//
//    return NO_WIN;
//}

inline int CheckWinConditionFast(int **board, int &N, int &M, int &K){
    int streak1=0, streak2=0, streak3=0, streak4=0, streak5=0, streak6=0, activePlayer;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){             //Horizontal
            if(board[i][j]==PLAYER_1){
                if(streak2)
                    streak2=0;
                streak1++;
            }
            else if(board[i][j]==PLAYER_2){
                if(streak1)
                    streak1=0;
                streak2++;
            }
            else{
                streak1=0;
                streak2=0;
            }
            if(streak1>=K)
                return true;
            else if(streak2>=K)
                return true;
            if(board[i][j]==PLAYER_1||board[i][j]==PLAYER_2){
                activePlayer=board[i][j];
                streak6=0;
                while( i+streak6<N && j+streak6<M ){                //Right Bevel
                    if(board[i+streak6][j+streak6]==activePlayer)
                        streak6++;
                    else{
                        if(streak6>=K)
                            return true;
                        else{
                            streak6=0;
                            break;
                        }
                    }
                if(streak6>=K)
                    return true;
                }
                streak6=0;
                activePlayer=board[i][j];
                streak5=0;
                while( i+streak5<N && j-streak5>=0){                //Left Bevel
                    if(board[i+streak5][j-streak5]==activePlayer){
                        streak5++;
                    }
                    else{
                        if(streak5>=K)
                            return true;
                        else{
                            streak5=0;
                            break;
                        }
                    }
                if(streak5>=K)
                    return true;
                }
                streak5=0;
            }
        }
        streak1=0;
        streak2=0;
    }
    for(int j=0; j<M; j++){
        for(int i=0; i<N; i++){                 //Vertical
            if(board[i][j]==PLAYER_1){
                if(streak3)
                    streak3=0;
                streak4++;
            }
            else if(board[i][j]==PLAYER_2){
                if(streak4)
                    streak4=0;
                streak3++;
            }
            else{
                streak4=0;
                streak3=0;
            }
            if(streak4>=K)
                return true;
            else if(streak3>=K)
                return true;
        }
        streak3=0;
        streak4=0;
    }

    return false;
}

inline int Win(int **board, int &N, int &M, int &K, int ACTIVE_PLAYER, Orientation orientation){
    int  playerA=0, playerB=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(board[i][j]==FREE_SPACE){
                board[i][j]=ACTIVE_PLAYER;
                if(CheckWinConditionFast(board, N, M, K)){
                    playerA++;
                }
                board[i][j]=(ACTIVE_PLAYER==PLAYER_1?PLAYER_2:PLAYER_1);
                if(CheckWinConditionFast(board, N, M, K)){
                    playerB++;
                }
                board[i][j]=FREE_SPACE;
                if(playerB){
                    if(CheckWinConditionFast(board, N, M, K)){
                        if(orientation==MAX)
                            return FIRST_PLAYER_WINS;
                        else
                            return SECOND_PLAYER_WINS;
                    }
                    return orientation==MAX?SECOND_PLAYER_WINS:FIRST_PLAYER_WINS;
                }
            }

        }
    }
    if (playerA>1) {
        return orientation==MAX?FIRST_PLAYER_WINS:SECOND_PLAYER_WINS;
    }
    return NO_WIN;
}

inline int InputBoard(int **board, int &N, int &M, int &K, int ACTIVE_PLAYER, int &emptyFields, int mode){
    int y=-1,x=-1;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            scanf("%d ", &(board[i][j]));
            if(board[i][j]==FREE_SPACE){
               emptyFields++;
                y=i;
                x=j;
            }
        }
    }
    if(x>=0&&y>=0&&mode==Extended){
        if(CheckWinConditionFast(board, N, M, K)){
            return SECOND_PLAYER_WINS;
        }
        if(emptyFields==1){
            board[y][x]=ACTIVE_PLAYER;
            if(CheckWinConditionFast(board, N, M, K)){
                board[y][x]=FREE_SPACE;
                return FIRST_PLAYER_WINS;
            }
            board[y][x]=FREE_SPACE;
        }
        else if (emptyFields>2)
            return Win(board, N, M, K, ACTIVE_PLAYER==PLAYER_1?PLAYER_2:PLAYER_1, MIN);
    }
    return NO_WIN;
}


inline void GEN_ALL_POS_MOV(int **board, int &N, int &M, int &K, int &ACTIVE_PLAYER, int &emptyFields, enum Mode mode){
    if(mode==Normal)
        if(CheckWinConditionFast(board, N, M, K))
           emptyFields=0;
        printf("%d\n", emptyFields);

    if(emptyFields){
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(board[i][j]==FREE_SPACE){
                    board[i][j]=ACTIVE_PLAYER;
                    PrintBoard(board, N, M);
                    board[i][j]=FREE_SPACE;
                }
            }
        }
    }
}

inline void GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(int **board, int &N, int &M, int &K, int &ACTIVE_PLAYER, int &emptyFields){
    bool exit=false;

    if(CheckWinConditionFast(board, N, M, K)||!emptyFields){
       emptyFields=0;
        printf("%d\n", emptyFields);
    }

    if(emptyFields){
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(board[i][j]==FREE_SPACE){
                    board[i][j]=ACTIVE_PLAYER;
                    if(CheckWinConditionFast(board, N, M, K)){
                        printf("1\n");
                        PrintBoard(board, N, M);
                        board[i][j]=FREE_SPACE;
                        exit=true;
                        break;
                    }
                    board[i][j]=FREE_SPACE;
                }
            }
            if(exit)
                break;
        }
        if(!exit)
            GEN_ALL_POS_MOV(board, N, M, K, ACTIVE_PLAYER, emptyFields, Cut);
    }

};

inline int Max(int first, int second){
        if(first==FIRST_PLAYER_WINS||second==FIRST_PLAYER_WINS)
            return FIRST_PLAYER_WINS;
        else if (first==BOTH_PLAYERS_TIE||second==BOTH_PLAYERS_TIE)
            return BOTH_PLAYERS_TIE;
        else
            return SECOND_PLAYER_WINS;

}
inline int Min(int first, int second){
        if(first==SECOND_PLAYER_WINS||second==SECOND_PLAYER_WINS)
            return SECOND_PLAYER_WINS;
        else if (first==BOTH_PLAYERS_TIE||second==BOTH_PLAYERS_TIE)
            return BOTH_PLAYERS_TIE;
        else
            return FIRST_PLAYER_WINS;
}

int SOLVE(int **board, int &N, int &M, int &K, int ACTIVE_PLAYER, enum Orientation orientation, int emptyFields){
    int condition = 0;
    int alreadyWon = NO_WIN;
    int max=SECOND_PLAYER_WINS, min=FIRST_PLAYER_WINS;

    if(CheckWinConditionFast(board, N, M, K)){
        if(orientation==MAX)
            return SECOND_PLAYER_WINS;
        else
            return FIRST_PLAYER_WINS;
    }
    if(!emptyFields)
        return BOTH_PLAYERS_TIE;

    for(int i=0; i<N; i++){
           for(int j=0; j<M; j++){
               if(board[i][j]==FREE_SPACE){
                   board[i][j]=ACTIVE_PLAYER;
                   alreadyWon=Win(board, N, M, K, ACTIVE_PLAYER, orientation);
                   if(alreadyWon){
                       condition = alreadyWon;     //Usprawnienie 2
                   }
                   else
                       condition=SOLVE(board, N, M, K, ((ACTIVE_PLAYER==PLAYER_1) ?  PLAYER_2: PLAYER_1 ), ((orientation==MAX)?MIN:MAX), emptyFields-1);
                   if(orientation==MAX){            //Usprawnienie 1
                       max=Max(condition, max);
                       if(max==FIRST_PLAYER_WINS){
                           board[i][j]=FREE_SPACE;
                           return FIRST_PLAYER_WINS;
                       }
                   }
                   else{
                       min=Min(condition, min);
                       if(min==SECOND_PLAYER_WINS){
                           board[i][j]=FREE_SPACE;
                           return SECOND_PLAYER_WINS;
                       }
                   }
                   board[i][j]=FREE_SPACE;
               }
           }
    }
    return ((orientation==MAX)?max:min);
}

inline void SOLVE_GAME_STATE(int **board, int &N, int &M, int &K, int &ACTIVE_PLAYER, int &emptyFields){

    int condition, alreadyWon;
    alreadyWon=InputBoard(board, N, M, K, ACTIVE_PLAYER, emptyFields, Extended);
    if(alreadyWon){
        condition = alreadyWon;     //Usprawnienie 2
    }
    else
    condition = SOLVE(board, N, M, K, ACTIVE_PLAYER, MAX, emptyFields);

    if(ACTIVE_PLAYER==PLAYER_1){
        if(condition==FIRST_PLAYER_WINS)
            printf("FIRST_PLAYER_WINS\n");
        else if (condition==SECOND_PLAYER_WINS)
            printf("SECOND_PLAYER_WINS\n");
        else
            printf("BOTH_PLAYERS_TIE\n");
    }
    else{
        if(condition==SECOND_PLAYER_WINS)
            printf("FIRST_PLAYER_WINS\n");
        else if (condition==FIRST_PLAYER_WINS)
            printf("SECOND_PLAYER_WINS\n");
        else
            printf("BOTH_PLAYERS_TIE\n");
    }
}

int main() {

    char q[100];
    int N=0, M=0, K=0, ACTIVE_PLAYER=0, emptyFields=0;
    int **board=NULL;

    while(true){

        emptyFields=0;
        scanf("%s",q);
        scanf("%d %d %d %d", &N, &M, &K, &ACTIVE_PLAYER);
        board = AlocateMemoryNM(board, N,M);

        if (!strcmp(q, "GEN_ALL_POS_MOV")){
            InputBoard(board, N, M, K, ACTIVE_PLAYER, emptyFields, Normal);
            GEN_ALL_POS_MOV(board, N, M, K, ACTIVE_PLAYER, emptyFields, Normal);
        }
        else if (!strcmp(q, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")){
            InputBoard(board, N, M, K, ACTIVE_PLAYER, emptyFields, Normal);
            GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(board, N, M, K, ACTIVE_PLAYER, emptyFields);
        }
        else if (!strcmp(q, "SOLVE_GAME_STATE")){
            SOLVE_GAME_STATE(board, N, M, K, ACTIVE_PLAYER, emptyFields);
        }
        if(feof(stdin)!=0)
            break;
        }

    FreeMemoryNM(board, N, M);
    return 0;
}
