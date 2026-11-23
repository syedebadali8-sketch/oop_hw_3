#include "canvas.hpp"
#include <iostream>
using namespace std;

Canvas :: Canvas(){
    clear();
}

void Canvas :: clear(){
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < 80; j++){
            board[i][j] = ' ';
        }
    }
}
