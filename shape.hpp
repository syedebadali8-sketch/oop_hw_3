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

};

#endif
