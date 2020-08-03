// 22.2.2019
//******************

// math constants
#define _USE_MATH_DEFINES

// for Visual C++
#define _CRT_SECURE_NO_DEPRECATE

// arena
#define ARENA_W 70 // without border
#define ARENA_H 16 // without border

// symbols
#define P_MONSTER '+'
#define P_HUNTER 'H'

// steps
#define MONSTER_S 3
#define HUNTER_S 5

// PROXIMITY
#define MONSTER_PROXIMITY 4


// macros for clearing console window and sleeping
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif

// headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// function declarations
void print_arena(float x_H, float y_H, float x_M, float y_M);

float get_new_x(float old_x, int uhol, int dist) { //New x

    float radian = M_PI / 180;
    float new_x = old_x + (dist * cos(uhol*radian));
    return new_x;
}

float get_new_y(float old_y, int uhol, int dist) { //New y

    float radian = M_PI / 180;
    float new_y = old_y + (dist * sin(uhol*radian));
    return new_y;
}

float distance(float x_1, float y_1, float x_2, float y_2) { // Dist between

    float distance = sqrt(pow(((x_2) - (x_1)), 2) + pow(((y_2) - (y_1)), 2));
    return distance;
}

int main()
{
    float x_H, y_H; //Hunter
    float x_M, y_M; //Monster
    float D;
    int corner_H, corner_M;
    char smer_H;
    int pocitadlo = 0;
    int x_h, y_h, x_m, y_m;

    // seed rand
    srand(time(NULL));

        //Cyklus pre generaciu vzdialenosti medzi Hunterom a Monstrom
        while(1==1){
            x_H = rand()%ARENA_W;
            y_H = rand()%ARENA_H;
            //grneracia uhla pre Huntera
            corner_H = 0 + rand()%(360 - 0 + 1);

            x_M = rand()%ARENA_W;
            y_M = rand()%ARENA_H;
            //grneracia uhla pre Monstra
            corner_M = 0 + rand()%(360 - 0 + 1);
            D = distance(x_H, y_H, x_M, y_M);
            if(D >= 7){
                break;
            }
        }

        while(D > MONSTER_PROXIMITY){
            pocitadlo++;
            // Vypis areny na obrazovku
            x_h = x_H;
            y_h = y_H;
            x_m = x_M;
            y_m = y_M;
            print_arena(x_h,y_h,x_m,y_m);
            //getchar();

            // Zapis smeru graficky
            printf("\n");
            if(corner_H >= 335 && corner_H <= 361){printf(" o"); printf("-");} // o-
            else if(corner_H <= 24){printf(" o"); printf("-");} // o-
            else if(corner_H >= 25 && corner_H <= 66){printf(" /\n");printf(" o");} // o/
            else if(corner_H >= 67 && corner_H <= 116){printf(" |\n");printf(" o");} // o|
            else if(corner_H >= 117 && corner_H <= 166){printf(" \\ ");printf("\n o");} // \o
            else if(corner_H >= 167 && corner_H <= 216){printf("-");printf(" o");} // -o
            else if(corner_H >= 217 && corner_H <= 266){printf(" o\n");printf(" /");} // /o
            else if(corner_H >= 267 && corner_H <= 316){printf(" o\n");printf(" |");} // o|
            else if(corner_H >= 317 && corner_H <= 334){printf(" o \n");printf(" \\");} // o..
            printf("\n\n");


            printf("//////////////////////////////////\n");
            printf("Monster(x, y): (%.2f, %.2f). Uhol = %d\n", x_M, y_M, corner_M);
            printf("Hunter(x, y): (%.2f, %.2f). Uhol = %d\n", x_H, y_H, corner_H);
            printf("Vzdialenost medzi Hunterom a Monstrom je: %.2f\n", D);

            printf("\n%d\n", pocitadlo);
            printf("Pohyb Huntera.\n");
            printf("\tL -> dolava;\n\tR -> rovno;\n\tD -> doprava;\n");


            printf("Zadaj smer Huntera: ");
            scanf("%c", &smer_H);
            printf("\n");

            // Vyber smeru a korekcia uhla pre Huntera
                if (smer_H == 'L') {
                    corner_H += 30;
                    if(corner_H > 360){
                        corner_H = corner_H - 360;
                    } else if(corner_H < 0){
                        corner_H = 360 + corner_H;
                    }
                } else if (smer_H == 'R') {
                    corner_H += 0;
                } else if (smer_H == 'D') {
                    corner_H -= 30;
                    if(corner_H > 360){
                        corner_H = corner_H - 360;
                    } else if(corner_H < 0){
                        corner_H = 360 + corner_H;
                    }
                }

            //grneracia uhla pre Monstra
            corner_M = 0 + rand()%(360 - 0 + 1);
            //printf("Novy Corner_M = %d\n", corner_M);


            // pre Monstra prechod cez steny
            x_M = get_new_x(x_M, corner_M, MONSTER_S);
            if(x_M > ARENA_W){
                x_M -= ARENA_W;
            }else if(x_M < 0){
                x_M += ARENA_W;
            }

            y_M = get_new_y(y_M, corner_M, MONSTER_S);
            if(y_M > ARENA_H){
                y_M -= ARENA_H;
            }else if(y_M < 0){
                y_M += ARENA_H;
            }

            printf("Nove suradnice pre Monstra(x, y) = (%.2f, %.2f). Novy Corner_M = %d\n", x_M, y_M, corner_M);

            // pre Huntera prechod cez steny
            x_H = get_new_x(x_H, corner_H, HUNTER_S);
            if(x_H > ARENA_W){
                x_H -= ARENA_W;
            }else if(x_H < 0){
                x_H += ARENA_W;
            }

            y_H = get_new_y(y_H, corner_H, HUNTER_S);
            if(y_H > ARENA_H){
                y_H -= ARENA_H;
            }else if(y_H < 0){
                y_H += ARENA_H;
            }

            printf("Nove suradnice pre Huntera(x, y) = (%.2f, %.2f). Novy Corner_H = %d\n", x_H, y_H, corner_H);

            D = distance(x_H, y_H, x_M, y_M);
            printf("Nova vzdialenost medzi Hunterom a Monstrom je: %.2f\n", D);
            printf("//////////////////////////////////\n");
            getchar();
            getchar();
            CLEAR_SCREEN(); // clearing screen
        }

        x_h = x_H;
        y_h = y_H;
        x_m = x_M;
        y_m = y_M;
        print_arena(x_h,y_h,x_m,y_m);

        printf("\n\t\t\t\bYou Win\n\n");
        printf("\tHra sa skoncila cez %d tahou.\n", pocitadlo);
        printf("\tHunter chytil Monstra ked bol v %.2f vzdialenosti od neho", D);

        getchar();
    return 0;
}

// function to print the contents of the arena
// IMPORTANT:
//   * use this function only for printing
//   * function does not print the character if it is located outside the arena
//   * you can modify this function
void print_arena(float x_H, float y_H, float x_M, float y_M)
{
    //CLEAR_SCREEN(); // clearing screen
    printf("\n\t\t\tARENA SIZE: %dx%d\n", ARENA_W, ARENA_H);
    printf("Hunter je reprezentovany tak: %c\n", P_HUNTER);
    printf("Monster je reprezentovany tak: %c\n", P_MONSTER);
    printf("\tKrok Huntera je: %d\n", HUNTER_S);
    printf("\tKrok Monstra je: %d\n", MONSTER_S);

    // inverting Y-axis for both hunter and monster
    y_H = ARENA_H-1-y_H;
    y_M = ARENA_H-1-y_M;

    int i,j,first_x,second_x;
    char first, second;
    printf("----------------------------------------------------------------------\n");
    for(i=0; i<ARENA_H; i++)
    {
        // row contains both hunter and monster
        if(i==y_H && i==y_M)
        {
            // hunter is closer to the left side
            if(x_H < x_M)
            {
                first = P_HUNTER;
                second = P_MONSTER;
                first_x = x_H;
                second_x = x_M;
            }
                // monster is closer to the left side
            else
            {
                first = P_MONSTER;
                second = P_HUNTER;
                first_x = x_M;
                second_x = x_H;
            }

            if(first_x<0 && (second_x>=0 && second_x<ARENA_W))
            {
                // printing spaces
                for(j=0; j<second_x; j++)
                {
                    printf(" ");
                }
                // printing second character
                printf("%c",second);
            }


            if((first_x>=0 && first_x<ARENA_W) && (second_x>=0 && second_x<ARENA_W))
            {
                // printing spaces
                for(j=0; j<first_x; j++)
                {
                    printf(" ");
                }
                // printing first character
                printf("%c",first);
                // printing spaces
                for(j=0; j<abs(second_x-first_x)-1; j++)
                {
                    printf(" ");
                }
                // printing second character
                printf("%c",second);

            }

            if((first_x>=0 && first_x<ARENA_W) && second_x>=ARENA_W)
            {
                // printing spaces
                for(j=0; j<first_x; j++)
                {
                    printf(" ");
                }
                // printing first character
                printf("%c",first);
            }

        }
            // row contains only hunter
        else if(i==y_H)
        {
            if(x_H<ARENA_W && x_H>=0)
            {
                // printing spaces
                for(j=0; j<x_H; j++)
                {
                    printf(" ");
                }
                // printing the hunter
                printf("%c",P_HUNTER);
            }
        }
            // row contains only monster
        else if(i==y_M)
        {
            if(x_M<ARENA_W && x_M>=0)
            {
                // printing spaces
                for(j=0; j<x_M; j++)
                {
                    printf(" ");
                }
                // printing the monster
                printf("%c",P_MONSTER);
            }
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------\n");
    //printf("Press ENTER to refresh the arena.");
    //getchar();
    //SLEEP(2000);
}
