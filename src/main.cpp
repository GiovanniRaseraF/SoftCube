#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <array>
#include <ncurses.h>

#define TRI 3
#define INIT(c){{{(c), (c), (c)}, {(c), (c), (c)}, {(c), (c), (c)}}} 

#define CWHITE      1
#define CYELLOW     2
#define CGREEN      3
#define CBLUE       4
#define CRED        5
#define CORANGE     6

enum colors{
    WHITE,   // top
    YELLOW,  // bottom
    GREEN,   // left
    BLUE,    // right
    RED,     // front
    ORANGE,  // posterior
};

void toString(const enum colors c){
    switch(c){
    case WHITE:     
        attron(COLOR_PAIR(CWHITE));
        printw("W");
        attroff(COLOR_PAIR(CWHITE));
        break;
    case YELLOW:
        attron(COLOR_PAIR(CYELLOW));
        printw("Y");
        attroff(COLOR_PAIR(CYELLOW));
        break;
    case GREEN:
        attron(COLOR_PAIR(CGREEN));
        printw("G");
        attroff(COLOR_PAIR(CGREEN));
        break;
    case BLUE:
        attron(COLOR_PAIR(CBLUE));
        printw("B");
        attroff(COLOR_PAIR(CBLUE));
        break;
    case RED:
        attron(COLOR_PAIR(CRED));
        printw("R");
        attroff(COLOR_PAIR(CRED));
        break;
    case ORANGE:
        attron(COLOR_PAIR(CORANGE));
        printw("O");
        attroff(COLOR_PAIR(CORANGE));
        break;
    default: break;
    }
}


typedef std::array<std::array<colors, TRI>, TRI> face; 
face 
    T INIT(WHITE), 
    B INIT(YELLOW),
    L INIT(GREEN),
    R INIT(BLUE),
    F INIT(RED),
    P INIT(ORANGE);

/**
Display the cube and additional informations
 */ 
void display(){
    // top
    for(int i = 0; i < TRI; i++){
        printw("       |");
        for(int j = 0; j < TRI; j++){
            (toString(T[i][j])); printw(j==TRI-1? "|": " ");
        }
        printw("\n");
    }
    printw("\n");

    // left front right posterior
    auto printLayer = [&](int layer){
        printw("|");
        for(int j = 0; j < TRI; j++){
            (toString(L[layer][j])); printw(j==TRI-1?"|": " ");
        }
        printw("|");
        for(int j = 0; j < TRI; j++){
            (toString(F[layer][j])); printw(j==TRI-1?"|": " ");
        }
        printw("|");
        for(int j = 0; j < TRI; j++){
            (toString(R[layer][j])); printw(j==TRI-1?"|": " ");
        }
        printw("|");
        for(int j = 0; j < TRI; j++){
            (toString(P[layer][j])); printw(j==TRI-1?"|": " ");
        }
        printw("\n");
    };

    for(int i = 0; i < TRI; i++){
        printLayer(i);
    }
    printw("\n");

    // bottom
    for(int i = 0; i < TRI; i++){
        printw("       |");
        for(int j = 0; j < TRI; j++){
            (toString(B[i][j])); printw(j==TRI-1?"|": " ");
        }
        printw("\n");
    }

    printw("\n\n");
}

// Right Move
void RMove(){
    // save
    enum colors posterior_2_2 = P[2][2];
    enum colors posterior_1_2 = P[1][2];
    enum colors posterior_0_2 = P[0][2];

    P[2][2] = B[2][2];
    P[1][2] = B[1][2];
    P[0][2] = B[0][2];

    B[2][2] = F[2][2];
    B[1][2] = F[1][2];
    B[0][2] = F[0][2];

    F[2][2] = T[2][2];
    F[1][2] = T[1][2];
    F[0][2] = T[0][2];
    
    T[2][2] = posterior_2_2;
    T[1][2] = posterior_1_2;
    T[0][2] = posterior_0_2;
}

// Middle Move
void MMove(){
    // save
    enum colors posterior_2_1 = P[2][1];
    enum colors posterior_1_1 = P[1][1];
    enum colors posterior_0_1 = P[0][1];

    P[2][1] = B[2][1];
    P[1][1] = B[1][1];
    P[0][1] = B[0][1];

    B[2][1] = F[2][1];
    B[1][1] = F[1][1];
    B[0][1] = F[0][1];

    F[2][1] = T[2][1];
    F[1][1] = T[1][1];
    F[0][1] = T[0][1];
    
    T[2][1] = posterior_2_1;
    T[1][1] = posterior_1_1;
    T[0][1] = posterior_0_1;
}

// Left Move
void LMove(){
    // moving face
    enum colors posterior_2_0 = P[2][0];
    enum colors posterior_1_0 = P[1][0];
    enum colors posterior_0_0 = P[0][0];

    P[2][0] = B[2][0];
    P[1][0] = B[1][0];
    P[0][0] = B[0][0];

    B[2][0] = F[2][0];
    B[1][0] = F[1][0];
    B[0][0] = F[0][0];

    F[2][0] = T[2][0];
    F[1][0] = T[1][0];
    F[0][0] = T[0][0];
    
    T[2][0] = posterior_2_0;
    T[1][0] = posterior_1_0;
    T[0][0] = posterior_0_0;

    // rotating left face
    face LCopy;
    LCopy = L;
    L[0][2] = LCopy[0][0]; L[1][2] = LCopy[0][1]; L[2][2] = LCopy[0][2];
    L[2][1] = LCopy[1][2];
    L[2][0] = LCopy[2][2]; L[1][0] = LCopy[2][1]; L[0][0] = LCopy[2][0];
    L[0][1] = LCopy[1][0]; 
}

void TMove(){
    // moving face
    enum colors posterior_2_0 = P[2][0];
    enum colors posterior_1_0 = P[1][0];
    enum colors posterior_0_0 = P[0][0];
}

char key_read(){
    return getch();
}

void move(char key){
    switch(key){
    case 'j': LMove(); break;
    case 'k': MMove(); break;
    case 'l': RMove(); break;


    default: break;
    }
}

int main(){
    initscr();                 /* Start curses mode     */
    start_color();

    // colors init
    init_pair(CWHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(CYELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(CGREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(CBLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(CRED, COLOR_BLACK, COLOR_RED);
    init_pair(CORANGE, COLOR_BLACK, COLOR_MAGENTA);

    // game loop
    while(true){
        clear();

        display();
        refresh();

        char key = key_read(); 
        move(key);
    }

    endwin();                  /* End curses mode    */
}