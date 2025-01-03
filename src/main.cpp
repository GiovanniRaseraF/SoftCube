#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <array>

#define TRI 3


#define INIT(c){{{(c), (c), (c)}, {(c), (c), (c)}, {(c), (c), (c)}}} 

enum colors{
    WHITE,   // top
    YELLOW,  // bottom
    GREEN,   // left
    BLUE,    // right
    RED,     // front
    ORANGE,  // posterior
};

std::string toString(enum colors c){
    switch(c){
    //printf("\x1B[93mYTexting\033[0m\n");
    case WHITE:     return "\x1B[1;37;37mW\033[0m";
    case YELLOW:    return "\x1B[1;93;93mY\033[0m";
    case GREEN:     return "\x1B[1;32;32mG\033[0m";
    case BLUE:      return "\x1B[1;34;34mB\033[0m";
    case RED:       return "\x1B[1;31;31mR\033[0m";
    case ORANGE:    return "\x1B[1;95;95mO\033[0m";
    default: return " ";
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
        std::cout << "       |";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(T[i][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // left front right posterior
    auto printLayer = [&](int layer){
        std::cout << "|";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(L[layer][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << "|";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(F[layer][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << "|";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(R[layer][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << "|";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(P[layer][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << std::endl;
    };

    for(int i = 0; i < TRI; i++){
        printLayer(i);
    }
    std::cout << std::endl;

    // bottom
    for(int i = 0; i < TRI; i++){
        std::cout << "       |";
        for(int j = 0; j < TRI; j++){
            std::cout << toString(B[i][j]) << (j==TRI-1?"|": " ");
        }
        std::cout << std::endl;
    }
}

int main(){
    display();
}