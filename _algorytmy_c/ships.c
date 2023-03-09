#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE_OF_X 10
#define SIZE_OF_Y 21
#define NUMBER_OF_PLAYERS 3
#define NUMBER_OF_SHIP_TYPES 4
#define MAX_FLEET_SIZE 10
#define COMMAND_SIZE 20
#define SHIP_ID 6 // 5 is max index of ship ID
#define CAR_ID 5
#define BAT_ID 4
#define CRU_ID 3
#define DES_ID 2
#define REEF_SIGN '#'
#define SHOT_SIGN 'x'
#define SPY_SIGN '$'
#define SHIP_CONDITION  13
#define SHIP_NUMBER 10
#define COORDINATES 4
#define PART_CONDITION 7
#define SHIP_NAME 4

enum PLAYER_t {
    PLAYER_A,
    PLAYER_B,
    NO_PLAYER
};
enum SHIP_PLACE_CONDITION_t {
    NOT_AVAIBLE,
    AVAIBLE,
    ALREADY_PLACED
};
enum SHIP_NAME_t{
    CAR,
    BAT,
    CRU,
    DES
};
enum DIRECTION_t{
    N,
    E,
    S,
    W
};
enum BOARD_MODE_t{
    SET_DEFAULT,
    CUSTOMIZE,
    CLEAR,
    RESET
};
enum SHIP_CONDITION_t{
    PLACED,
    X_POSITION,
    Y_POSITION,
    DIRECTION,
    MOVES_LEFT,
    X_CANNON,
    Y_CANNON,
    CANNON_CONDITION,
    X_ENGINE,
    Y_ENGINE,
    ENGINE_CONDITION,
    RADAR_CONDITION,
    SHOOTS_LEFT
};
enum EQUIPMENT_CONDITION_t{
    DESTROYED,
    UNDESTROYED
};
enum COORDINATES_t{
    X1,
    X2,
    Y1,
    Y2
};
enum SHOT_MODE_t{
    DEFAULT,
    EXTENDED
};
struct BOARD_t{
    char **adress;
    int size_of_x, size_of_y;
};
struct REMAINING_PARTS_t{
    int playerA, playerB;
};


int PLACE_SHIP(struct BOARD_t *board, char ship_name[SHIP_NAME], enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char SHIP_SIGN[NUMBER_OF_PLAYERS]);
int SET_FLEET(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]);
int REEF(struct BOARD_t *board);
int SHOOT(struct BOARD_t *board, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], struct REMAINING_PARTS_t *remaining_parts, char SHIP_SIGN[NUMBER_OF_PLAYERS]);
int ALL_SHIPS_SET(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]);
int CHECK_PLACE_CONDITION(int x, int y, int i, char direction, int length, struct BOARD_t *board, enum PLAYER_t ACTIVE_PLAYER, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char SHIP_SIGN[NUMBER_OF_PLAYERS]);
int SHIP(struct BOARD_t *board, char ship_name[SHIP_NAME], struct REMAINING_PARTS_t *remaining_parts, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char part_condition[PART_CONDITION],char SHIP_SIGN[NUMBER_OF_PLAYERS]);
int MOVE(struct BOARD_t *board, char ship_name[SHIP_NAME], int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, char SHIP_SIGN[NUMBER_OF_PLAYERS]);
int CONVERT_SHIP_NAME(char ship_name[SHIP_NAME]);
int CONVERT_DIRECTION(char direction);
int CHECK_DISTANCE(struct BOARD_t *board, char SHIP_SIGN[NUMBER_OF_PLAYERS],int x, int y, int length, char direction);
int CHECK_REEF(struct BOARD_t *board, int x, int y, int length, char direction);
int EXTENDED_SHOOTING(struct BOARD_t *board, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts, char SHIP_SIGN[NUMBER_OF_PLAYERS], char ship_name[SHIP_NAME]);
int SPY(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, struct BOARD_t *spyA, struct BOARD_t *spyB);
int INT_LENGHT(int number);
int DESCIPTION_X_VALUE(int x, int y, int z);
int DESCIPTION_Y_VALUE(int x, int y, int z);
void PRINT(struct BOARD_t *board, enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts, char SHIP_SIGN[NUMBER_OF_PLAYERS],int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], struct BOARD_t *spyA, struct BOARD_t *spyB);
void NEXT_PLAYER(enum PLAYER_t* PLAYER_NEXT);
void DEFAULT_SHIP_STATE(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]);
void BOARD_SIZE(struct BOARD_t *board, struct BOARD_t *spyA, struct BOARD_t *spyB, enum BOARD_MODE_t mode, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES]);
void INIT_POSITION(int mode, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], struct BOARD_t *board);
void RESET_MOVES(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]);
void INCREASE_REMAINING_PARTS(enum PLAYER_t ACTIVE_PLAYER, int number, struct REMAINING_PARTS_t *remaining_parts);
void SET_SHIP(char direction, struct BOARD_t *board, int x, int y, enum PLAYER_t ACTIVE_PLAYER, char SHIP_SIGN[NUMBER_OF_PLAYERS], int ship_length);
void SET_CANNON_AND_ENGINE_POSITION(enum PLAYER_t ACTIVE_PLAYER, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], char direction, int length, int i, int x, int y);
void RESET_SHOOTS(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]);
void SAVE(struct BOARD_t *board, enum PLAYER_t PLAYER_NEXT, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], char ship_name[SHIP_NAME], char part_condition[PART_CONDITION], enum SHOT_MODE_t shot_mode);
void CLEAR_BOARD(char **board_name, int size);
char **CREATE_NEW_BOARD_TAB(int x, int y);
int CHECK_IF_IT_IS_EMPTY(struct BOARD_t *board);

int main(){

    struct BOARD_t board, spyA, spyB;
    struct REMAINING_PARTS_t remaining_parts;
    enum PLAYER_t ACTIVE_PLAYER;
    enum SHOT_MODE_t shot_mode;
    int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION];
    int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES];
    int error;
    char ship_name[SHIP_NAME];
    char part_condition[PART_CONDITION];
    char SHIP_SIGN[NUMBER_OF_PLAYERS];
    char command[COMMAND_SIZE];

    SHIP_SIGN[PLAYER_A]='A';
    SHIP_SIGN[PLAYER_B]='B';
    remaining_parts.playerA=0;
    remaining_parts.playerB=0;
    error= 0;

    ACTIVE_PLAYER = PLAYER_A;
    shot_mode=DEFAULT;

    BOARD_SIZE(&board, &spyA, &spyB, SET_DEFAULT, INIT_POSITION_tab);
    INIT_POSITION(SET_DEFAULT, INIT_POSITION_tab, &board);
    DEFAULT_SHIP_STATE(SHIP_STATE);
    RESET_MOVES(SHIP_STATE);
    RESET_SHOOTS(SHIP_STATE);

    while (scanf("%s", command) != EOF) {

        if (!strcmp(command, "[state]")) {
            do {
                scanf("%s", command);
                if (!strcmp(command, "PRINT"))PRINT(&board, NO_PLAYER, &remaining_parts, SHIP_SIGN, SHIP_STATE, &spyA, &spyB);
                else if (!strcmp(command, "SET_FLEET")) error=SET_FLEET(SHIP_STATE);
                else if (!strcmp(command, "NEXT_PLAYER")) NEXT_PLAYER(&ACTIVE_PLAYER);
                else if (!strcmp(command, "BOARD_SIZE")) BOARD_SIZE(&board, &spyA, &spyB, CUSTOMIZE, INIT_POSITION_tab);
                else if (!strcmp(command, "INIT_POSITION")) INIT_POSITION(CUSTOMIZE, INIT_POSITION_tab, &board);
                else if (!strcmp(command, "REEF")) error=REEF(&board);
                else if (!strcmp(command, "SHIP")) error=SHIP(&board, ship_name, &remaining_parts, SHIP_STATE, INIT_POSITION_tab, part_condition, SHIP_SIGN);
                else if (!strcmp(command, "EXTENDED_SHIPS")) shot_mode=EXTENDED;
                else if (!strcmp(command, "SET_AI_PLAYER"));
                else if (!strcmp(command, "SRAND"));
                else if (!strcmp(command, "SAVE")) SAVE(&board, ACTIVE_PLAYER, INIT_POSITION_tab, SHIP_STATE, ship_name, part_condition, shot_mode);
                else if (!strcmp(command, "AUTO_SHOOTING"));
                else if (!strcmp(command, "INFORMATION"));
                else;
                if (error == 1) break;
            } while (strcmp(command, "[state]"));
        }

        else if (!strcmp(command, "[playerA]")|| !strcmp(command, "[playerB]")) {
            do {
                if ((!strcmp(command, "[playerA]")&& ACTIVE_PLAYER == PLAYER_B) || (!strcmp(command, "[playerB]")&& ACTIVE_PLAYER == PLAYER_A) ){
                    printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED", command);
                        error=1;
                        break;
                    }
                scanf("%s", command);
                if (!strcmp(command, "PLACE_SHIP")) error = PLACE_SHIP(&board, ship_name, ACTIVE_PLAYER, &remaining_parts, SHIP_STATE, INIT_POSITION_tab, SHIP_SIGN);
                else if (!strcmp(command, "SHOOT")) {
                    if(shot_mode==DEFAULT) error = SHOOT(&board, SHIP_STATE, &remaining_parts, SHIP_SIGN);
                    else error=EXTENDED_SHOOTING(&board, SHIP_STATE, ACTIVE_PLAYER, &remaining_parts, SHIP_SIGN, ship_name);
                }
                else if (!strcmp(command, "MOVE")) error= MOVE(&board, ship_name, SHIP_STATE, ACTIVE_PLAYER, SHIP_SIGN);
                else if (!strcmp(command, "SPY")) error=SPY(SHIP_STATE, ACTIVE_PLAYER, &spyA, &spyB);
                else if (!strcmp(command, "PRINT")) PRINT(&board, ACTIVE_PLAYER, &remaining_parts, SHIP_SIGN, SHIP_STATE, &spyA, &spyB);
                else if ((ACTIVE_PLAYER == PLAYER_A) && (!strcmp(command, "[playerB]"))) printf("INVALID OPERATION COMMAND SPECIFIED: END WITH TAG [playerA]\n");
                else if ((ACTIVE_PLAYER == PLAYER_B) && (!strcmp(command, "[playerA]"))) printf("INVALID OPERATION COMMAND SPECIFIED: END WITH TAG [playerB]\n");
                else;
            } while (((ACTIVE_PLAYER == PLAYER_A) && (strcmp(command, "[playerA]"))) || ((ACTIVE_PLAYER == PLAYER_B) && (strcmp(command, "[playerB]"))));

            if (ACTIVE_PLAYER == PLAYER_A) ACTIVE_PLAYER = PLAYER_B;
            else ACTIVE_PLAYER = PLAYER_A;

            RESET_MOVES(SHIP_STATE);
            RESET_SHOOTS(SHIP_STATE);
        }

        if (error == 1) break;

        if (remaining_parts.playerA == 0 && ALL_SHIPS_SET(SHIP_STATE)) {
            printf("B won");
            break;
        }
        if (remaining_parts.playerB == 0 && ALL_SHIPS_SET(SHIP_STATE)) {
            printf("A won");
            break;
        }
    }
    BOARD_SIZE(&board, &spyA, &spyB, CLEAR, INIT_POSITION_tab);
    return 0;
}

int CONVERT_SHIP_NAME(char ship_name[SHIP_NAME]){

    int ship_int;
    if (!strcmp(ship_name, "CAR")) ship_int = CAR_ID;
    else if (!strcmp(ship_name, "BAT")) ship_int = BAT_ID;
    else if (!strcmp(ship_name, "CRU")) ship_int = CRU_ID;
    else if (!strcmp(ship_name, "DES")) ship_int = DES_ID;
    else ship_int = -1;
    return ship_int;

}

int CONVERT_DIRECTION(char direction){

    int direction_int;
    if (direction=='N') direction_int=N;
    else if (direction=='S') direction_int=S;
    else if (direction=='E') direction_int=E;
    else if (direction=='W') direction_int=W;
    else direction_int=-1;
    return direction_int;

}

int CHECK_DISTANCE(struct BOARD_t *board, char SHIP_SIGN[NUMBER_OF_PLAYERS],int x, int y, int length, char direction){

    switch (direction){
        case 'N':{
            for(int j=y-1; j<y+length+1;j++){
                for(int p=x-1; p<x+2; p++){
                    if(j>=0&&j<board->size_of_y&&p>=0&&p<board->size_of_x){
                        if(board->adress[p][j]==SHIP_SIGN[PLAYER_A]||board->adress[p][j]==SHIP_SIGN[PLAYER_B])return 1;
                }
            }
            }
        } break;
        case 'E':{
            for(int j=y-1; j<y+2;j++){
                for(int p=x-length; p<x+2; p++){
                    if(j>=0&&j<board->size_of_y&&p>=0&&p<board->size_of_x) {
                        if(board->adress[p][j]==SHIP_SIGN[PLAYER_A]||board->adress[p][j]==SHIP_SIGN[PLAYER_B]) return 1;

                    }
                }
            }
        } break;
        case 'S':{
            for(int j=y-length; j<y+2;j++){
                for(int p=x-1; p<x+2; p++){
                    if(j>=0&&j<board->size_of_y&&p>=0&&p<board->size_of_x){
                        if(board->adress[p][j]==SHIP_SIGN[PLAYER_A]||board->adress[p][j]==SHIP_SIGN[PLAYER_B]) return 1;
                    }
                }
            }

        } break;
        case 'W':{
            for(int j=y-1; j<y+2;j++){
                for(int p=x-1; p<x+length+1; p++){
                    if(j>=0&&j<board->size_of_y&&p>=0&&p<board->size_of_x) {
                        if(board->adress[p][j]==SHIP_SIGN[PLAYER_A]||board->adress[p][j]==SHIP_SIGN[PLAYER_B]) return 1;

                    }
                }
            }

        } break;
    }
    return 0;

}

int CHECK_REEF(struct BOARD_t *board, int x, int y, int length, char direction){

    switch (direction) {
    case 'N': for (int p = 0; p < length; p++) {
        if (board->adress[x][y + p] == REEF_SIGN) {
            return 1;
        }
    } break;
    case 'E': for (int p = 0; p < length; p++) {
        if(board->adress[x - p][y] == REEF_SIGN) {
            return 1;
        }
    } break;
    case 'S': for (int p = 0; p < length; p++) {
        if(board->adress[x][y - p] == REEF_SIGN) {
        return 1;
        }
    } break;
    case 'W': for (int p = 0; p < length; p++) {
       if( board->adress[x + p][y] == REEF_SIGN) {
        return 1;
       }
    } break;
    }
    return 0;

}

int PLACE_SHIP(struct BOARD_t *board, char ship_name[SHIP_NAME], enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char SHIP_SIGN[NUMBER_OF_PLAYERS]) {

    int x, y, i, length,direction_int;
    char direction;
    scanf("%d %d %c %d %s", &y, &x, &direction, &i, ship_name);

    length=CONVERT_SHIP_NAME(ship_name);
    direction_int=CONVERT_DIRECTION(direction);

    int error=CHECK_PLACE_CONDITION(x,y,i, direction, length, board, ACTIVE_PLAYER, SHIP_STATE, INIT_POSITION_tab, SHIP_SIGN);
    if(error){
        switch (error){
            case 1: printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": SHIP ALREADY PRESENT", y, x, direction, i, ship_name);
                break;
            case 2: printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET", y, x, direction, i, ship_name);
                break;
            case 3: printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": NOT IN STARTING POSITION", y, x, direction, i, ship_name);
                break;
            case 4: printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": PLACING SHIP TOO CLOSE TO OTHER SHIP", y, x, direction, i, ship_name);
                break;
            case 5:  printf("INVALID OPERATION \"PLACE_SHIP %d %d %c %d %s\": PLACING SHIP ON REEF", y, x, direction, i, ship_name);
                break;
        }
        return 1;
    }

    //FUNCTION
    SET_CANNON_AND_ENGINE_POSITION(ACTIVE_PLAYER, SHIP_STATE, direction, length, i, x, y);
    INCREASE_REMAINING_PARTS(ACTIVE_PLAYER, length, remaining_parts);
    SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=UNDESTROYED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=UNDESTROYED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][PLACED] = ALREADY_PLACED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION] = x;
    SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION] = y;
    SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION] = direction_int;
    SHIP_STATE[ACTIVE_PLAYER][length][i][RADAR_CONDITION]=UNDESTROYED;
    SET_SHIP(direction, board, x, y, ACTIVE_PLAYER, SHIP_SIGN, length);
    return 0;

}

int CHECK_PLACE_CONDITION(int x, int y, int i, char direction, int length, struct BOARD_t *board, enum PLAYER_t ACTIVE_PLAYER, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char SHIP_SIGN[NUMBER_OF_PLAYERS]){

    int tmp=0;

    //CHECK IF SHIP IS ALREADY PRESENT
    if (SHIP_STATE[ACTIVE_PLAYER][length][i][PLACED] == ALREADY_PLACED) return 1;

    //CHECK IF SHIP IS AVAIBLE TO SET
    for (int j = 0; j < MAX_FLEET_SIZE; j++) {
        if (SHIP_STATE[ACTIVE_PLAYER][length][i][PLACED] == AVAIBLE) {
            tmp = 1;
            break;
        }
    }
    if(tmp!=1) return 2;
    tmp = 0;

    //CHECK IF IT THERES SPACE FOR IT
    if (x<INIT_POSITION_tab[ACTIVE_PLAYER][X1] || y<INIT_POSITION_tab[ACTIVE_PLAYER][Y1] || x>INIT_POSITION_tab[ACTIVE_PLAYER][X2] || y>INIT_POSITION_tab[ACTIVE_PLAYER][Y2] ) tmp++;
            switch (direction) {
                case 'N': if (y + length-1 > INIT_POSITION_tab[ACTIVE_PLAYER][Y2]) tmp++;
                break;
            case 'E': if (x - length+1< INIT_POSITION_tab[ACTIVE_PLAYER][X1]) tmp++;
                break;
            case 'S': if (y - length+1< INIT_POSITION_tab[ACTIVE_PLAYER][Y1]) tmp++;
                break;
                case 'W': if (x + length-1 > INIT_POSITION_tab[ACTIVE_PLAYER][X2]) tmp++;
                break;
            }
    if (tmp != 0) return 3;

    if (CHECK_DISTANCE(board, SHIP_SIGN, x, y, length, direction)) return 4;

    if (CHECK_REEF(board, x, y, length, direction)) return 5;

    return 0;

}

int DESCIPTION_X_VALUE(int x, int y, int z){

    if(y==z) return x%10;
    else {int tmp=1;
        for (
        int j=0; j<(z-y);j++) tmp=10*tmp;
        return(x/tmp)%10;
    }

}

int DESCIPTION_Y_VALUE(int x, int y, int z){

    if(x==z) return y%10;
    else {int tmp=1;
        for (
        int j=0; j<(z-x);j++) tmp=10*tmp;
        return(y/tmp)%10;
    }

}

int SHIP(struct BOARD_t *board, char ship_name[SHIP_NAME], struct REMAINING_PARTS_t *remaining_parts, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], char part_condition[PART_CONDITION], char SHIP_SIGN[NUMBER_OF_PLAYERS]){

    int x, y, i, length,part = 0,direction_int;
    char player_char;
    char direction;
    enum PLAYER_t ACTIVE_PLAYER=NO_PLAYER;
    scanf(" %c %d %d %c %d %s %s", &player_char, &y, &x, &direction, &i, ship_name, part_condition);

    switch (player_char){
        case 'A': ACTIVE_PLAYER=PLAYER_A;
            break;
        case 'B': ACTIVE_PLAYER=PLAYER_B;
            break;
    }

    length=CONVERT_SHIP_NAME(ship_name);
    direction_int=CONVERT_DIRECTION(direction);

    int error= CHECK_PLACE_CONDITION(x,y,i, direction, length, board, ACTIVE_PLAYER, SHIP_STATE, INIT_POSITION_tab, SHIP_SIGN);
    if(error){
        switch (error){
            case 1: printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": SHIP ALREADY PRESENT", player_char, y, x, direction, i, ship_name, part_condition);
                break;
            case 2: printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": ALL SHIPS OF THE CLASS ALREADY SET", player_char ,y, x, direction, i, ship_name, part_condition);
                break;
            case 3: printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": NOT IN STARTING POSITION", player_char, y, x, direction, i, ship_name, part_condition);
                break;
            case 4: printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": PLACING SHIP TOO CLOSE TO OTHER SHIP", player_char, y, x, direction, i, ship_name, part_condition);
                break;
            case 5: printf("INVALID OPERATION \"SHIP %c %d %d %c %d %s %s\": PLACING SHIP ON REEF", player_char, y, x, direction, i, ship_name, part_condition);
                break;
        }
        return 1;
    }

    //FUNCTION
    SET_CANNON_AND_ENGINE_POSITION(ACTIVE_PLAYER, SHIP_STATE, direction, length, i, x, y);
    SHIP_STATE[ACTIVE_PLAYER][length][i][PLACED] = ALREADY_PLACED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION] = x;
    SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION] = y;
    SHIP_STATE[ACTIVE_PLAYER][length][i][RADAR_CONDITION]=UNDESTROYED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=UNDESTROYED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=UNDESTROYED;
    SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]=direction_int;

    switch (ACTIVE_PLAYER) {
    case PLAYER_A: {
        part=remaining_parts->playerA;
    }
                 break;
    case PLAYER_B: {
        part=remaining_parts->playerB;
    }
                 break;
        case NO_PLAYER:;
            break;
    }

    switch (direction) {
    case 'N': for (int p = 0; p < length; p++) {
        if(part_condition[p]=='1') {
            board->adress[x][y + p] = SHIP_SIGN[ACTIVE_PLAYER];
            part++;
        }
       else board->adress[x][y + p] = SHOT_SIGN;
    } break;
    case 'E': for (int p = 0; p < length; p++) {
        if(part_condition[p]=='1'){
            board->adress[x - p][y] = SHIP_SIGN[ACTIVE_PLAYER];
            part++;
        }
        else board->adress[x - p][y] = SHOT_SIGN;
    } break;
    case 'S': for (int p = 0; p < length; p++) {
        if(part_condition[p]=='1') {
            board->adress[x][y - p] = SHIP_SIGN[ACTIVE_PLAYER];
            part++;
        }
        else board->adress[x][y - p] = SHOT_SIGN;
    } break;
    case 'W': for (int p = 0; p < length; p++) {
        if(part_condition[p]=='1') {
            board->adress[x + p][y] = SHIP_SIGN[ACTIVE_PLAYER];
            part++;
        }
        else board->adress[x + p][y] = SHOT_SIGN;;
    } break;
    }

    if(board->adress[x][y]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][RADAR_CONDITION]=DESTROYED;
    switch(direction){
        case 'N':{
            if(board->adress[x][y+1]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=DESTROYED;
            if(board->adress[x][y+length-1]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=DESTROYED;
        } break;
        case 'E':{
            if(board->adress[x-1][y]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=DESTROYED;
            if(board->adress[x-length+1][y]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=DESTROYED;
        } break;
        case 'S':{
            if(board->adress[x][y-1]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=DESTROYED;
            if(board->adress[x][y-length+1]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=DESTROYED;
        } break;
        case 'W':{
            if(board->adress[x+1][y]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]=DESTROYED;
            if(board->adress[x+length-1][y]==SHOT_SIGN) SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]=DESTROYED;
        } break;
    }

    switch (ACTIVE_PLAYER) {
    case PLAYER_A: {
        remaining_parts->playerA =part;
    }
                 break;
    case PLAYER_B: {
        remaining_parts->playerB =part;
    } break;
    case NO_PLAYER:;
        break;
    }
    return 0;

}

int MOVE(struct BOARD_t *board, char ship_name[SHIP_NAME], int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, char SHIP_SIGN[NUMBER_OF_PLAYERS]){

    int i,length,x,y, tmpx, tmpy, move_direction_int,tmp=0;
    char direction, move_direction = '\0';
    scanf("%d %s %c", &i, ship_name, &direction);

    length=CONVERT_SHIP_NAME(ship_name);

    if(ALL_SHIPS_SET(SHIP_STATE)==0){
        printf("INVALID OPERATION \"MOVE %d %s %c\": NOT ALL SHIPS PLACED",  i, ship_name, direction);
        return 1;
    }
    if(SHIP_STATE[ACTIVE_PLAYER][length][i][ENGINE_CONDITION]==DESTROYED){
        printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE",  i, ship_name, direction);
        return 1;
    }

    //EREASE SHIP
    tmpx=SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION];
    tmpy=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION];
    switch (SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]) {
    case N: for (int p = 0; p < length; p++) {
        board->adress[tmpx][tmpy + p] = ' ';
    } break;
    case E: for (int p = 0; p < length; p++) {
        board->adress[tmpx - p][tmpy] = ' ';
    } break;
    case S: for (int p = 0; p < length; p++) {
        board->adress[tmpx][tmpy - p] = ' ';
    } break;
    case W: for (int p = 0; p < length; p++) {
        board->adress[tmpx + p][tmpy] = ' ';
    } break;
    }

    //SET NEW MOVE DIRECTION
    switch (direction){
        case 'F': {
            if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==N) move_direction='N';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==E) move_direction='E';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==S) move_direction='S';
            else move_direction='W';
        }
            break;
        case 'R':{
            if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==N) move_direction='W';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==E) move_direction='N';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==S) move_direction='E';
            else move_direction='S';
        }
            break;
        case 'L':{
            if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==N) move_direction='E';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==E) move_direction='S';
            else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==S) move_direction='W';
            else move_direction='N';
        }
            break;
    }

    //SET NEW STARTING POSITION
    if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==N){
        x=SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION];
        y=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION]-1;
    }
    else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==E){
        x=SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION]+1;
        y=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION];
    }
    else if(SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION]==W){
        x=SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION]-1;
        y=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION];
    }
    else{
        x=SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION];
        y=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION]+1;
    }
    move_direction_int=CONVERT_DIRECTION(move_direction);

    //VALIDATION
    if (x<0 || y<0 || x>board->size_of_x  || y>board->size_of_y ) tmp++;
            switch (direction) {
                case 'N': if (y + length > board->size_of_y) tmp++;
                break;
            case 'E': if (x - length + 1< 0) tmp++;
                break;
            case 'S': if (y - length + 1< 0) tmp++;
                break;
                case 'W': if (x + length > board->size_of_x) tmp++;
                break;
            }
    if(tmp!=0){
        printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD",  i, ship_name, direction);
        return 1;
    }
    if(CHECK_DISTANCE(board, SHIP_SIGN, x, y, length, move_direction)){
        printf("INVALID OPERATION \"MOVE %d %s %c\": PLACING SHIP TOO CLOSE TO OTHER SHIP",  i, ship_name, direction);
        return 1;
    }
    if(CHECK_REEF(board, x, y, length, move_direction)){
        printf("INVALID OPERATION \"MOVE %d %s %c \": PLACING SHIP ON REEF", i, ship_name, direction);
        return 1;
    }
    if(SHIP_STATE[ACTIVE_PLAYER][length][i][MOVES_LEFT]==0) {
        printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY",  i, ship_name, direction);
        return 1;
    }

    //FUNCTION
    SHIP_STATE[ACTIVE_PLAYER][length][i][X_POSITION] = x;
    SHIP_STATE[ACTIVE_PLAYER][length][i][Y_POSITION] = y;
    SHIP_STATE[ACTIVE_PLAYER][length][i][DIRECTION] = move_direction_int;
    SHIP_STATE[ACTIVE_PLAYER][length][i][MOVES_LEFT]--;
    SET_CANNON_AND_ENGINE_POSITION(ACTIVE_PLAYER, SHIP_STATE, move_direction, length, i, x, y);
    SET_SHIP(move_direction, board, x, y, ACTIVE_PLAYER, SHIP_SIGN, length);
    return 0;

}

int ALL_SHIPS_SET(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]) {

    for (int i = 0; i < SHIP_ID; i++) {
        for (int j = 0; j < MAX_FLEET_SIZE; j++) {
            if (SHIP_STATE[PLAYER_A][i][j][PLACED] == AVAIBLE || SHIP_STATE[PLAYER_B][i][j][PLACED] == AVAIBLE) return 0;
        }
    }
    return 1;

}

int REEF(struct BOARD_t *board) {

    int x, y;
    scanf("%d%d", &y, &x);

    if(x<0||y<0||x>board->size_of_x||y>board->size_of_y){
        printf("INVALID OPERATION \"REEF %d %d\": REEF IS NOT PLACED ON BOARD",  y, x);
        return 1;
    }

    board->adress[x][y] = REEF_SIGN;

    return 0;

}

int SHOOT(struct BOARD_t *board, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], struct REMAINING_PARTS_t *remaining_parts, char SHIP_SIGN[NUMBER_OF_PLAYERS]) {

    int x, y;
    scanf(" %d %d", &y, &x);

    if (x<0 || y<0 || x>board->size_of_x || y>board->size_of_y) {
        printf("INVALID OPERATION \"SHOOT %d %d\": FIELD DOES NOT EXIST", y, x);
        return 1;
    }

    if (ALL_SHIPS_SET(SHIP_STATE)==0) {
        printf("INVALID OPERATION \"SHOOT %d %d\": NOT ALL SHIPS PLACED", y, x);
        return 1;
    }

    if (board->adress[x][y] == SHIP_SIGN[PLAYER_A]) {
             remaining_parts->playerA--;
        board->adress[x][y] = SHOT_SIGN;
    }
    if (board->adress[x][y] == SHIP_SIGN[PLAYER_B]) {
             remaining_parts->playerB--;
        board->adress[x][y] = SHOT_SIGN;
    }
    return 0;

}

int SET_FLEET(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]) {

    int a, b, c, d;
    char player_id;
    enum PLAYER_t PLAYER=NO_PLAYER;
    scanf(" %c %d %d %d %d", &player_id, &a, &b, &c, &d);

    if (a + b + c + d > MAX_FLEET_SIZE || a > MAX_FLEET_SIZE || b > MAX_FLEET_SIZE || c > MAX_FLEET_SIZE || d > MAX_FLEET_SIZE) {
        printf("INVALID OPERATION SET_FLEET SPECIFIED: TOO MANY SHIPS");
        return 1;
    }

    switch (player_id) {
    case 'A': PLAYER = PLAYER_A;
        break;
    case 'B':PLAYER = PLAYER_B;
        break;
    }

    for (int i = 0; i < MAX_FLEET_SIZE; i++) {
        for (int j = 0; j < SHIP_ID; j++) SHIP_STATE[PLAYER][DES_ID + j][i][PLACED] = NOT_AVAIBLE;
    }
    for (int i = 0; i < a; i++) SHIP_STATE[PLAYER][CAR_ID][i][PLACED] = AVAIBLE;
    for (int i = 0; i < b; i++) SHIP_STATE[PLAYER][BAT_ID][i][PLACED] = AVAIBLE;
    for (int i = 0; i < c; i++) SHIP_STATE[PLAYER][CRU_ID][i][PLACED] = AVAIBLE;
    for (int i = 0; i < d; i++) SHIP_STATE[PLAYER][DES_ID][i][PLACED] = AVAIBLE;
    return 0;

    }

int EXTENDED_SHOOTING(struct BOARD_t *board, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts, char SHIP_SIGN[NUMBER_OF_PLAYERS], char ship_name[SHIP_NAME]){

    int x, y, i, length, x_can, y_can;
    enum PLAYER_t shooten_player=NO_PLAYER;
    scanf(" %d %s %d %d",&i, ship_name, &y, &x);

    length=CONVERT_SHIP_NAME(ship_name);
    x_can=SHIP_STATE[ACTIVE_PLAYER][length][i][X_CANNON];
    y_can=SHIP_STATE[ACTIVE_PLAYER][length][i][Y_CANNON];

    if (x<0 || y<0 || x>board->size_of_x || y>board->size_of_y) {
        printf("INVALID OPERATION \"SHOOT %d %d\": FIELD DOES NOT EXIST", y, x);
        return 1;
    }

    if (ALL_SHIPS_SET(SHIP_STATE)==0) {
        printf("INVALID OPERATION \"SHOOT %d %d\": NOT ALL SHIPS PLACED", y, x);
        return 1;
    }

    if(SHIP_STATE[ACTIVE_PLAYER][length][i][SHOOTS_LEFT]==0){
            printf("INVALID OPERATION \"SHOOT %d %s %d %d\": TOO MANY SHOOTS", i, ship_name, y, x);
            return 1;
    }

    if(SHIP_STATE[ACTIVE_PLAYER][length][i][CANNON_CONDITION]==DESTROYED){
            printf("INVALID OPERATION \"SHOOT %d %s %d %d\": SHIP CANNOT SHOOT", i, ship_name, y, x);
            return 1;
    }

    if(length!=CAR_ID&&(length*length<(x-x_can)*(x-x_can)+(y-y_can)*(y-y_can))){
            printf("INVALID OPERATION \"SHOOT %d %s %d %d\": SHOOTING TOO FAR", i, ship_name, y, x);
            return 1;
    }

    if (board->adress[x][y] == SHIP_SIGN[PLAYER_A]) {
             remaining_parts->playerA--;
        board->adress[x][y] = SHOT_SIGN;
        shooten_player=PLAYER_A;
    }
    if (board->adress[x][y] == SHIP_SIGN[PLAYER_B]) {
             remaining_parts->playerB--;
        board->adress[x][y] = SHOT_SIGN;
        shooten_player=PLAYER_B;
    }

    SHIP_STATE[ACTIVE_PLAYER][length][i][SHOOTS_LEFT]--;

    for(int j=DES_ID; j<=CAR_ID; j++){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            if(x==SHIP_STATE[shooten_player][j][p][X_CANNON]&&y==SHIP_STATE[shooten_player][j][p][Y_CANNON]) SHIP_STATE[shooten_player][j][p][CANNON_CONDITION]=DESTROYED;
            if(x==SHIP_STATE[shooten_player][j][p][X_ENGINE]&&y==SHIP_STATE[shooten_player][j][p][Y_ENGINE]) SHIP_STATE[shooten_player][j][p][ENGINE_CONDITION]=DESTROYED;
            if(x==SHIP_STATE[shooten_player][j][p][X_POSITION]&&y==SHIP_STATE[shooten_player][j][p][Y_POSITION]) SHIP_STATE[shooten_player][j][p][RADAR_CONDITION]=DESTROYED;
        }
    }

    return 0;

}

int SPY(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], enum PLAYER_t ACTIVE_PLAYER, struct BOARD_t *spyA, struct BOARD_t *spyB){

    int i,y,x;
    scanf(" %d %d %d", &i, &y, &x);

    if(SHIP_STATE[ACTIVE_PLAYER][CAR_ID][i][CANNON_CONDITION]==DESTROYED){
            printf("INVALID OPERATION \"SPY %d %d %d\": CANNOT SEND PLANE)",i, y, x);
            return 1;
    }
    if(SHIP_STATE[ACTIVE_PLAYER][CAR_ID][i][SHOOTS_LEFT]==0){
        printf("INVALID OPERATION \"SPY %d %d %d\": ALL PLANES SENT)",i, y, x);
        return 1;
    }
    if(x<0||y<0||x>spyA->size_of_x-1||y>spyA->size_of_y){
        printf("INVALID OPERATION \"SPY %d %d %d\": POSITION OVER BOARD)",i, y, x);
        return 1;
    }

    switch (ACTIVE_PLAYER){
        case PLAYER_A: spyA->adress[x][y]=SPY_SIGN;
            break;
        case PLAYER_B: spyB->adress[x][y]=SPY_SIGN;
            break;
        case NO_PLAYER:;
            break;
    }

    SHIP_STATE[ACTIVE_PLAYER][CAR_ID][i][SHOOTS_LEFT]--;
    return 0;

}

int INT_LENGHT(int number){

    int count=0;

    while(number){
    number/=10;
    count++;
    }
    return count;

}

void DEFAULT_SHIP_STATE(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]){

    for (int i = 0; i < SHIP_ID; i++) {
        for (int j = 0; j < MAX_FLEET_SIZE; j++) {
            SHIP_STATE[PLAYER_A][i][j][PLACED] = NOT_AVAIBLE;
            SHIP_STATE[PLAYER_B][i][j][PLACED] = NOT_AVAIBLE;
        }
    }
    for (int i = DES_ID; i < SHIP_ID; i++) {
        for (int j = 0; j < SHIP_ID-i; j++) {
            SHIP_STATE[PLAYER_A][i][j][PLACED] = AVAIBLE;
            SHIP_STATE[PLAYER_B][i][j][PLACED] = AVAIBLE;
        }
    }

}

void INCREASE_REMAINING_PARTS(enum PLAYER_t ACTIVE_PLAYER, int number, struct REMAINING_PARTS_t *remaining_parts){

    switch (ACTIVE_PLAYER) {
    case PLAYER_A: {
        remaining_parts->playerA += number;
    }
                 break;
    case PLAYER_B: {
        remaining_parts->playerB += number;
    }
                 break;
        case NO_PLAYER:
            break;
    }
}

void SET_SHIP(char direction, struct BOARD_t *board, int x, int y, enum PLAYER_t ACTIVE_PLAYER, char SHIP_SIGN[NUMBER_OF_PLAYERS], int ship_length){

    switch (direction) {
    case 'N': for (int p = 0; p < ship_length; p++) {
        board->adress[x][y + p] = SHIP_SIGN[ACTIVE_PLAYER];
    } break;
    case 'E': for (int p = 0; p < ship_length; p++) {
        board->adress[x - p][y] = SHIP_SIGN[ACTIVE_PLAYER];
    } break;
    case 'S': for (int p = 0; p < ship_length; p++) {
        board->adress[x][y - p] = SHIP_SIGN[ACTIVE_PLAYER];
    } break;
    case 'W': for (int p = 0; p < ship_length; p++) {
        board->adress[x + p][y] = SHIP_SIGN[ACTIVE_PLAYER];
    } break;
    }
}

void PRINT(struct BOARD_t *board, enum PLAYER_t ACTIVE_PLAYER, struct REMAINING_PARTS_t *remaining_parts,char SHIP_SIGN[NUMBER_OF_PLAYERS],int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], struct BOARD_t *spyA, struct BOARD_t *spyB) {

    int x,y,tmp,mode;
    char **player_board = NULL, **active_board=board->adress;
    scanf("%d", &mode);

    if(ACTIVE_PLAYER!=NO_PLAYER){
        player_board=(char**)malloc(board->size_of_x*sizeof(char*));
        for(int j=0; j<board->size_of_x;j++){
            player_board[j]=(char*)malloc((board->size_of_y+1)*sizeof(char));
        }
        for(int j=0; j<board->size_of_y;j++){
            for(int p=0; p<board->size_of_x;p++){
                if(board->adress[p][j]==REEF_SIGN) player_board[p][j]=REEF_SIGN;
                else player_board[p][j]='?';
            }
        }
        for(int j=DES_ID; j<=CAR_ID; j++){
            for(int p=0; p<MAX_FLEET_SIZE; p++){
                if(SHIP_STATE[ACTIVE_PLAYER][j][p][PLACED]==ALREADY_PLACED){
                x=SHIP_STATE[ACTIVE_PLAYER][j][p][X_POSITION];
                y=SHIP_STATE[ACTIVE_PLAYER][j][p][Y_POSITION];
                for(int m=0; m<board->size_of_y; m++){
                    for(int n=0; n<board->size_of_x; n++){
                        if((ACTIVE_PLAYER==PLAYER_A&&spyA->adress[n][m]==SPY_SIGN)||(ACTIVE_PLAYER==PLAYER_B&&spyB->adress[n][m]==SPY_SIGN)){
                            player_board[n][m]=board->adress[n][m];
                            if(m!=0) player_board[n][m-1]=board->adress[n][m-1];
                            if(m!=0&&n!=0) player_board[n-1][m-1]=board->adress[n-1][m-1];
                            if(n!=0) player_board[n-1][m]=board->adress[n-1][m];
                            if(n!=0&&m!=board->size_of_y-1) player_board[n-1][m+1]=board->adress[n-1][m+1];
                            if(m!=board->size_of_y-1) player_board[n][m+1]=board->adress[n][m+1];
                            if(m!=board->size_of_y-1&&n!=board->size_of_x-1) player_board[n+1][m+1]=board->adress[n+1][m+1];
                            if(n!=board->size_of_x-1) player_board[n+1][m]=board->adress[n+1][m];
                            if(m!=0&&n!=board->size_of_x-1) player_board[n+1][m-1]=board->adress[n+1][m-1];
                        }
                        else if(SHIP_STATE[ACTIVE_PLAYER][j][p][RADAR_CONDITION]==UNDESTROYED&&j*j>=(m-y)*(m-y)+(n-x)*(n-x))  player_board[n][m]=board->adress[n][m];
                        else if ((SHIP_STATE[ACTIVE_PLAYER][j][p][RADAR_CONDITION]==DESTROYED&&1>=(m-y)*(m-y)+(n-x)*(n-x))||board->adress[n][m]==SHIP_SIGN[ACTIVE_PLAYER])  player_board[n][m]=board->adress[n][m];
                        else;
                    }
                }
                }
            }
        }
        active_board=player_board;
    }

    if (mode == 0) {
        for (int y = 0; y < board->size_of_y; y++) {
            for (int x = 0; x < board->size_of_x; x++) {
                if(active_board[x][y]==SHIP_SIGN[PLAYER_A]||active_board[x][y]==SHIP_SIGN[PLAYER_B]) printf("+");
                else printf("%c", active_board[x][y]);
            }
            printf("\n");
        }
    }
    else{
        int descriptionCollumns=INT_LENGHT(board->size_of_y-1), descriptionRows=INT_LENGHT(board->size_of_x-1);
        for (int y = 0; y < board->size_of_y+descriptionRows; y++) {
            for (int x = 0; x < board->size_of_x+descriptionCollumns; x++) {
                if(y<descriptionRows&&x<descriptionCollumns) printf(" ");
                else if(y<descriptionRows&&x>descriptionCollumns-1)printf("%d", DESCIPTION_X_VALUE(x-descriptionCollumns, y, descriptionRows-1));
                else if(y>=descriptionRows&&x<descriptionCollumns) printf("%d", DESCIPTION_Y_VALUE(x, y-descriptionRows, descriptionCollumns-1));
               else if(active_board[x-descriptionCollumns][y-descriptionRows]==SHIP_SIGN[PLAYER_A]||active_board[x-descriptionCollumns][y-descriptionRows]==SHIP_SIGN[PLAYER_B]){
                    tmp=1;
                   for(int j=DES_ID; j<=CAR_ID; j++){
                    for(int p=0; p<MAX_FLEET_SIZE; p++){
                        if((SHIP_STATE[PLAYER_A][j][p][X_ENGINE]==x-descriptionCollumns&&SHIP_STATE[PLAYER_A][j][p][Y_ENGINE]==y-descriptionRows)||(SHIP_STATE[PLAYER_B][j][p][X_ENGINE]==x-descriptionCollumns&&SHIP_STATE[PLAYER_B][j][p][Y_ENGINE]==y-descriptionRows)){
                            printf("%c", '%');
                            tmp=0;
                        }
                       else if((SHIP_STATE[PLAYER_A][j][p][X_CANNON]==x-descriptionCollumns&&SHIP_STATE[PLAYER_A][j][p][Y_CANNON]==y-descriptionRows)||(SHIP_STATE[PLAYER_B][j][p][X_CANNON]==x-descriptionCollumns&&SHIP_STATE[PLAYER_B][j][p][Y_CANNON]==y-descriptionRows)){
                            printf("!");
                            tmp=0;
                        }
                        else if((SHIP_STATE[PLAYER_A][j][p][X_ENGINE]==x-descriptionCollumns&&SHIP_STATE[PLAYER_A][j][p][Y_ENGINE]==y-descriptionRows)||(SHIP_STATE[PLAYER_B][j][p][X_ENGINE]==x-descriptionCollumns&&SHIP_STATE[PLAYER_B][j][p][Y_ENGINE]==y-descriptionRows)){
                            printf("%c", '%');
                            tmp=0;
                        }
                        else if((SHIP_STATE[PLAYER_A][j][p][X_POSITION]==x-descriptionCollumns&&SHIP_STATE[PLAYER_A][j][p][Y_POSITION]==y-descriptionRows)||(SHIP_STATE[PLAYER_B][j][p][X_POSITION]==x-descriptionCollumns&&SHIP_STATE[PLAYER_B][j][p][Y_POSITION]==y-descriptionRows)) {
                            printf("%c", '@');
                            tmp=0;
                        }
                    }

                }
                    if(tmp==1) printf("+");
                }
                else if(active_board[x-descriptionCollumns][y-descriptionRows]==SHOT_SIGN) printf("x");
                else if(active_board[x-descriptionCollumns][y-descriptionRows]==REEF_SIGN) printf("#");
                else printf("%c", active_board[x-descriptionCollumns][y-descriptionRows]);
    }
            printf("\n");
}
    }
    if(ACTIVE_PLAYER!=NO_PLAYER){
        for(int j=0; j<board->size_of_x;j++){
            free(player_board[j]);
        }
        free(player_board);
    }
    else printf("PARTS REMAINING:: A : %d B : %d\n", remaining_parts->playerA, remaining_parts->playerB);

}

void RESET_MOVES(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]){

    for(int j=0; j<MAX_FLEET_SIZE; j++){
        SHIP_STATE[PLAYER_A][CAR_ID][j][MOVES_LEFT]=2;
        SHIP_STATE[PLAYER_A][CRU_ID][j][MOVES_LEFT]=3;
        SHIP_STATE[PLAYER_A][DES_ID][j][MOVES_LEFT]=3;
        SHIP_STATE[PLAYER_A][BAT_ID][j][MOVES_LEFT]=3;
        SHIP_STATE[PLAYER_B][CAR_ID][j][MOVES_LEFT]=2;
        SHIP_STATE[PLAYER_B][CRU_ID][j][MOVES_LEFT]=3;
        SHIP_STATE[PLAYER_B][DES_ID][j][MOVES_LEFT]=3;
        SHIP_STATE[PLAYER_B][BAT_ID][j][MOVES_LEFT]=3;
    }

}

void INIT_POSITION(int mode, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], struct BOARD_t *board){

    if(mode==CUSTOMIZE){
        enum PLAYER_t player;
        int x1,x2,y1,y2;
        char player_char;
        scanf(" %c %d %d %d %d", &player_char, &y1 , &x1 , &y2, &x2);
        switch (player_char){
            case 'A': player=PLAYER_A;
                break;
            case 'B': player=PLAYER_B;
                break;
            default: return;
        }
        INIT_POSITION_tab[player][X1]=x1;
        INIT_POSITION_tab[player][X2]=x2;
        INIT_POSITION_tab[player][Y1]=y1;
        INIT_POSITION_tab[player][Y2]=y2;
    }
    else if (mode==RESET){
        INIT_POSITION_tab[PLAYER_A][X1]=0;
        INIT_POSITION_tab[PLAYER_A][X2]=board->size_of_x-1;
        INIT_POSITION_tab[PLAYER_A][Y1]=0;
        INIT_POSITION_tab[PLAYER_A][Y2]=board->size_of_y-1;
        INIT_POSITION_tab[PLAYER_B][X1]=0;
        INIT_POSITION_tab[PLAYER_B][X2]=board->size_of_x-1;
        INIT_POSITION_tab[PLAYER_B][Y1]=0;
        INIT_POSITION_tab[PLAYER_B][Y2]=board->size_of_y-1;
    }
    else{
        INIT_POSITION_tab[PLAYER_A][X1]=0;
        INIT_POSITION_tab[PLAYER_A][X2]=board->size_of_x-1;
        INIT_POSITION_tab[PLAYER_A][Y1]=0;
        INIT_POSITION_tab[PLAYER_A][Y2]=(board->size_of_y-1)/2-1;
        INIT_POSITION_tab[PLAYER_B][X1]=0;
        INIT_POSITION_tab[PLAYER_B][X2]=board->size_of_x-1;
        INIT_POSITION_tab[PLAYER_B][Y1]=(board->size_of_y+1)/2;
        INIT_POSITION_tab[PLAYER_B][Y2]=board->size_of_y-1;
    }

}

void BOARD_SIZE(struct BOARD_t *board, struct BOARD_t *spyA, struct BOARD_t *spyB, enum BOARD_MODE_t mode, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES]) {

    if(mode!=CLEAR){
        int sizeinx,sizeiny;
        struct BOARD_t new_board, new_spyA, new_spyB;
        if(mode==CUSTOMIZE){
            scanf(" %d %d",&sizeinx,&sizeiny);
        }
        else{
            sizeinx=SIZE_OF_X;
            sizeiny=SIZE_OF_Y;
        }
        new_board.adress=CREATE_NEW_BOARD_TAB(sizeinx, sizeiny+1);
        new_spyA.adress=CREATE_NEW_BOARD_TAB(sizeinx, sizeiny+1);
        new_spyB.adress=CREATE_NEW_BOARD_TAB(sizeinx, sizeiny+1);

            if(mode==CUSTOMIZE&&(!CHECK_IF_IT_IS_EMPTY(board))){
            for(int y = 0; y < board->size_of_y; y++){
                for (int x = 0; x < board->size_of_x ;x++) {
                    new_board.adress[x][y] = board->adress[x][y];
                    new_spyA.adress[x][y] = spyA->adress[x][y];
                    new_spyB.adress[x][y] = spyB->adress[x][y];
                }
            }
            }

        board->adress=new_board.adress;
        board->size_of_x=sizeinx;
        board->size_of_y=sizeiny;

        spyA->adress=new_spyA.adress;
        spyA->size_of_x=sizeinx;
        spyA->size_of_y=sizeiny;

        spyB->adress=new_spyB.adress;
        spyB->size_of_x=sizeinx;
        spyB->size_of_y=sizeiny;

        if(mode==CUSTOMIZE){
            INIT_POSITION(RESET, INIT_POSITION_tab, board);
        }
    }
    else{
        CLEAR_BOARD(board->adress, board->size_of_x);
        CLEAR_BOARD(spyA->adress, spyA->size_of_x);
        CLEAR_BOARD(spyB->adress, spyB->size_of_x);
    }

}

void NEXT_PLAYER(enum PLAYER_t* PLAYER_NEXT) {

    char PLAYER_ID;
    scanf(" %c", &PLAYER_ID);
    if (PLAYER_ID == 'A') *PLAYER_NEXT = PLAYER_A;
    else*PLAYER_NEXT = PLAYER_B;

}

void SET_CANNON_AND_ENGINE_POSITION(enum PLAYER_t ACTIVE_PLAYER, int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], char direction, int length, int i, int x, int y){

    switch (direction){
        case 'N':{
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_CANNON] = x;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_CANNON] = y+1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_ENGINE] = x;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_ENGINE] = y+length-1;

        }
            break;
        case 'E':{
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_CANNON] = x-1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_CANNON] = y;
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_ENGINE] = x-length+1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_ENGINE] = y;

        }
            break;
        case 'S':{
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_CANNON] = x+1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_CANNON] = y;
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_ENGINE] = x;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_ENGINE] = y-length+1;

        }
            break;
        case 'W':{
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_CANNON] = x+1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_CANNON] = y;
            SHIP_STATE[ACTIVE_PLAYER][length][i][X_ENGINE] = x+length-1;
            SHIP_STATE[ACTIVE_PLAYER][length][i][Y_ENGINE] = y;

        }
            break;
    }

}

void RESET_SHOOTS(int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION]){

    for(int j=DES_ID; j<=CAR_ID; j++){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            SHIP_STATE[PLAYER_A][j][p][SHOOTS_LEFT]=j;
            SHIP_STATE[PLAYER_B][j][p][SHOOTS_LEFT]=j;
        }
    }

}

void SAVE(struct BOARD_t *board, enum PLAYER_t PLAYER_NEXT, int INIT_POSITION_tab[NUMBER_OF_PLAYERS][COORDINATES], int SHIP_STATE[NUMBER_OF_PLAYERS][SHIP_ID][SHIP_NUMBER][SHIP_CONDITION], char ship_name[SHIP_NAME], char part_condition[PART_CONDITION], enum SHOT_MODE_t shot_mode){

    char player=0, direction = '\0';
    int car = 0, cru=0,des = 0,bat = 0,tmp=0,x,y;
    printf("[state]\n");
    printf("BOARD_SIZE %d %d\n", board->size_of_y, board->size_of_x);

    switch (PLAYER_NEXT){
        case PLAYER_A: player = 'A';
            break;
        case PLAYER_B: player = 'B';
            break;
        case NO_PLAYER:;
            break;
    }
    for(int p=0; p<board->size_of_y; p++){
        for(int k=0; k<board->size_of_x; k++){
            if(board->adress[k][p]==REEF_SIGN) printf("REEF %d %d\n", p,k);
        }
    }
    if(shot_mode==EXTENDED) printf("EXTENDED_SHIPS\n");
    printf("NEXT_PLAYER %c\n", player);
    printf("INIT_POSITION A %d %d %d %d\n", INIT_POSITION_tab[PLAYER_A][Y1],INIT_POSITION_tab[PLAYER_A][X1],INIT_POSITION_tab[PLAYER_A][Y2],INIT_POSITION_tab[PLAYER_A][X2]);
    for(int j=DES_ID; j<=CAR_ID; j++){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            if(SHIP_STATE[PLAYER_A][j][p][PLACED]!=NOT_AVAIBLE) tmp++;
            }
        switch (j){
            case DES_ID: des=tmp;
                break;
            case CRU_ID: cru=tmp;
                break;
            case BAT_ID: bat=tmp;
                break;
            case CAR_ID: car=tmp;
                break;
        }
        tmp=0;
    }
    printf("SET_FLEET A %d %d %d %d\n", car, bat, cru, des);
    for(int j=CAR_ID; j>=DES_ID; j--){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            if(SHIP_STATE[PLAYER_A][j][p][PLACED]==ALREADY_PLACED){
                x=SHIP_STATE[PLAYER_A][j][p][X_POSITION];
                y=SHIP_STATE[PLAYER_A][j][p][Y_POSITION];
                switch (j){
                    case DES_ID: strcpy(ship_name, "DES");
                        break;
                    case CRU_ID: strcpy(ship_name, "CRU");
                        break;
                    case BAT_ID: strcpy(ship_name, "BAT");
                        break;
                    case CAR_ID: strcpy(ship_name, "CAR");
                        break;
                }
                switch(SHIP_STATE[PLAYER_A][j][p][DIRECTION]){
                    case N: {
                        direction='N';
                        for(int k=0; k<j; k++){
                            if(board->adress[x][y+k]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case E: {
                        direction='E';
                        for(int k=0; k<j; k++){
                            if(board->adress[x-k][y]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case S: {
                        direction='S';
                        for(int k=0; k<j; k++){
                            if(board->adress[x][y-k]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case W: {
                        direction='W';
                        for(int k=0; k<j; k++){
                            if(board->adress[x+k][y]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                }
                part_condition[j]='\0';
                printf("SHIP A %d %d %c %d %s %s\n", SHIP_STATE[PLAYER_A][j][p][Y_POSITION], SHIP_STATE[PLAYER_A][j][p][X_POSITION], direction, p, ship_name, part_condition);
            }
        }
    }
    printf("INIT_POSITION B %d %d %d %d\n", INIT_POSITION_tab[PLAYER_B][Y1],INIT_POSITION_tab[PLAYER_B][X1],INIT_POSITION_tab[PLAYER_B][Y2],INIT_POSITION_tab[PLAYER_B][X2]);
    for(int j=DES_ID; j<=CAR_ID; j++){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            if(SHIP_STATE[PLAYER_B][j][p][PLACED]!=NOT_AVAIBLE) tmp++;
            }
        switch (j){
            case DES_ID: des=tmp;
                break;
            case CRU_ID: cru=tmp;
                break;
            case BAT_ID: bat=tmp;
                break;
            case CAR_ID: car=tmp;
                break;
        }
        tmp=0;
    }
    printf("SET_FLEET B %d %d %d %d\n", car, bat, cru, des);
    for(int j=CAR_ID; j>=DES_ID; j--){
        for(int p=0; p<MAX_FLEET_SIZE; p++){
            if(SHIP_STATE[PLAYER_B][j][p][PLACED]==ALREADY_PLACED){
                x=SHIP_STATE[PLAYER_B][j][p][X_POSITION];
                y=SHIP_STATE[PLAYER_B][j][p][Y_POSITION];
                switch (j){
                    case DES_ID: strcpy(ship_name, "DES");
                        break;
                    case CRU_ID: strcpy(ship_name, "CRU");
                        break;
                    case BAT_ID: strcpy(ship_name, "BAT");
                        break;
                    case CAR_ID: strcpy(ship_name, "CAR");
                        break;
                }
                switch(SHIP_STATE[PLAYER_B][j][p][DIRECTION]){
                    case N: {
                        direction='N';
                        for(int k=0; k<j; k++){
                            if(board->adress[x][y+k]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case E: {
                        direction='E';
                        for(int k=0; k<j; k++){
                            if(board->adress[x-k][y]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case S: {
                        direction='S';
                        for(int k=0; k<j; k++){
                            if(board->adress[x][y-k]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                    case W: {
                        direction='W';
                        for(int k=0; k<j; k++){
                            if(board->adress[x+k][y]==SHOT_SIGN) part_condition[k]='0';
                            else part_condition[k]='1';
                        }
                    }
                        break;
                }
                part_condition[j]='\0';
                printf("SHIP B %d %d %c %d %s %s\n", SHIP_STATE[PLAYER_B][j][p][Y_POSITION], SHIP_STATE[PLAYER_B][j][p][X_POSITION], direction, p, ship_name, part_condition);
            }
        }
    }
    printf("[state]\n");
}

void CLEAR_BOARD(char **board_name, int size){
    for (int i=0; i<size; i++)free(board_name[i]);
    free(board_name);
}

char **CREATE_NEW_BOARD_TAB(int x, int y){

    char **new_board;
    new_board=(char**)malloc(x*sizeof(char*));
    for (int i = 0; i < x; i++) {
        new_board[i]=(char*)malloc(y*sizeof(char));
    }
    for(int i=0; i< y; i++){
    for (int j = 0; j < x; j++) {
        new_board[j][i] = ' ';
    }
    }
    return new_board;

}

int CHECK_IF_IT_IS_EMPTY(struct BOARD_t *board){
    for(int i=0; i<board->size_of_y; i++){
        for(int j=0; j<board->size_of_x;j++){
            if(board->adress[j][i]!=' ') return 0;
        }
    }
    return 1;
}
