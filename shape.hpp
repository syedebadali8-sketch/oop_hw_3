#ifndef SHAPE_HPP
#define SHAPE_HPP

class Triangle;

class Shape{
    protected:
        int ID;
        Triangle* prevTriangle; 
    public:
        Shape(int id);
        virtual ~Shape();
        virtual void draw(char canvas[][80]) = 0;
        int getID() const;


};

#endif
