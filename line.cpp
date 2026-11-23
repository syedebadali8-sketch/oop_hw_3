#include "line.hpp"
#include <iostream>
#include "angle.hpp"
#include <cmath>
using namespace std;

Line :: Line(int id, Point a, Point b) : Shape(id), p1(a), p2(b){}

Point Line :: getp1() const{
    return p1;
}

Point Line :: getp2() const{
    return p2;
}

void Line :: draw(char canvas[][80]){
    int x1 = p1.getx();
    int y1 = p1.gety();
    int x2 = p2.getx();
    int y2 = p2.gety();

    if (y1 == y2){
        if (x1 > x2){
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int x = x1; x <= x2; x++){
            if (x >= 0 && x < 80 && y1 >= 0 && y1 < 40){
                canvas[y1][x] = '-';
            } 
        }
    } else if (x1 == x2){
        if (y1 > y2){
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int y = y1; y <= y2; y++){
            if (y >= 0 && y < 40 && x1 >= 0 && x1 < 80){
                canvas[y][x1] = '|';
            }
        }
    } else{
        int dx = x2-x1;
        int dy = y2-y1;
        double distance = sqrt(dx*dx + dy*dy);
        int steps = (int) distance;
        if (steps < 1){
            steps = 1;
        }

        for (int i = 0; i <= steps; i++){
            double t = (double)i / steps;
            int x = round(x1 + t * dx);
            int y = round(y1 + t * dy);
            if (x >= 0 && x < 80 && y >= 0 && y < 40){
                if (dx * dy > 0){
                    canvas[y][x] = '\\';
                }
                else{
                    canvas[y][x] = '/';
                }
            }
        }
    }
    if (p1.getx() >= 0 && p1.getx() < 80 && p1.gety() >= 0 && p1.gety() < 40){
    canvas[p1.gety()][p1.getx()] = 'o';
    }
    if (p2.getx() >= 0 && p2.getx() < 80 && p2.gety() >= 0 && p2.gety() < 40){
        canvas[p2.gety()][p2.getx()] = 'o';
    }
}

Angle* Line :: operator+(const Line& other) const{
    Point a = p1;
    Point b = p2;
    Point c = other.p1;
    Point d = other.p2;
    bool shared = false;
    if ((a.getx() == c.getx() && a.gety() == c.gety()) || (a.getx() == d.getx() && a.gety() == d.gety()) || (b.getx() == c.getx() && b.gety() == c.gety()) || (b.getx() == d.getx() && b.gety() == d.gety())){
        shared = true;
    }
    if (shared == false){
        cout << "Lines do not share an endpoint" << endl;
        return nullptr;
    }
    int dx1 = b.getx() - a.getx();
    int dy1 = b.gety() - a.gety();
    int dx2 = d.getx() - c.getx();
    int dy2 = d.gety() - c.gety();
    if (dx1 == 0 && dy1 == 0){
        cout << "Invalid first line" << endl;
        return nullptr;
    }

    if (dx2 == 0 && dy2 == 0){
        cout << "Invalid second line" << endl;
        return nullptr;
    }
    if (dx1 * dy2 == dy1 * dx2){
        cout << "Lines are parallel" << endl;
        return nullptr;
    }
    Angle* newAngle = new Angle(0, *this, other);

    return newAngle;
}



