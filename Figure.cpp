#include <iostream>
#include <cmath>
#include <cassert>


class Figure {
public:
    virtual double calc_area() = 0;

    virtual double calc_perimeter() = 0;
};

class Point : public virtual Figure {
public:
    // без этого не хочет наследоваться. Почему?
    Point() : x(0.), y(0.) {}

    Point(double x, double y) : x(x), y(y) {}

    Point(Point &p) : x(p.x), y(p.y) {}

    double calc_area() override {
        return 0.;
    }

    double calc_perimeter() override {
        return 0.;
    }

    std::pair<double, double> get_position() {
        return std::make_pair(x, y);
    }

    virtual ~Point() = default;

private:
    double x;
    double y;
};

class Segment : public virtual Point {
public:
    Segment() : p1(0, 0), p2(0, 0) {}

    Segment(Point &p1, Point &p2) : p1(p1), p2(p2) {}

    double calc_area() override {
        return 0.;
    }

    double calc_perimeter() override {
        return 0.;
    }

    double get_length() {
        auto pos1 = p1.get_position(), pos2 = p2.get_position();
        return find_dist(pos1.first, pos2.first, pos1.second, pos2.second);
    }


private:
    Point p1;
    Point p2;

    double find_dist(double x1, double x2, double y1, double y2) {
        return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
};

class Triangle : public virtual Segment {
public:
    Triangle(Point &p1, Point &p2, Point &p3) : s1(p1, p2), s2(p2, p3), s3(p3, p1),
                                                perimeter(s1.get_length() + s2.get_length() + s3.get_length()),
                                                area(gerone_formula(perimeter, s1.get_length(), s2.get_length(),
                                                                    s3.get_length())) {
    }

    double calc_area() override {
        return area;
    }

    double calc_perimeter() override {
        return perimeter;
    }

    double gerone_formula(double p, double a, double b, double c) {
        p /= 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    Segment s1;
    Segment s2;
    Segment s3;

    double perimeter;
    double area;
};

class Rectangle : public virtual Segment {
public:

    Rectangle() = default;

    Rectangle(Point &p1, Point &p2, Point &p3, Point &p4) : s1(p1, p2), s2(p2, p3), s3(p3, p4),
                                                            s4(p4, p1), perimeter(
                    s1.get_length() + s2.get_length() + s3.get_length() + s4.get_length()),
                                                            area(s1.get_length() * s2.get_length()) {}

    double calc_area() override {
        return area;
    }

    double calc_perimeter() override {
        return perimeter;
    }

private:
    Segment s1;
    Segment s2;
    Segment s3;
    Segment s4;

    double perimeter;
    double area;
};

class Square : public virtual Rectangle {
public:
    Square(Point &p1, Point &p2, Point &p3, Point &p4) : s1(p1, p2), s2(p2, p3), s3(p3, p4),
                                                         s4(p4, p1), perimeter(
                    s1.get_length() + s2.get_length() + s3.get_length() + s4.get_length()),
                                                         area(s1.get_length() * s1.get_length()) {}

    double calc_area() override {
        return area;
    }

    double calc_perimeter() override {
        return perimeter;
    }

private:
    Segment s1;
    Segment s2;
    Segment s3;
    Segment s4;

    double perimeter;
    double area;
};


class Rhombus : Segment {

};


int main() {
    double eps = 1e-7;

    Point p1(2, 3), p2(2, 7), pp1(0, 0), pp2(0, 3), pp3(4, 0);
    Segment s1(p1, p2);
    assert(std::abs(s1.get_length() - 4) < eps);

    // ?? - can't create without ref
    //Triangle t1(Point(0., 0.), Point(0., 3.), Point(4., 0.));

    Triangle t1(pp1, pp2, pp3);
    assert(std::abs(t1.calc_perimeter() - (3 + 4 + 5)) < eps);
    assert(std::abs(t1.calc_area() - 6) < eps);

    Point point1(0, 0), point2(6, 0), point3(6, 10), point4(0, 10);
    Rectangle r1(point1, point2, point3, point4);
    assert(std::abs(r1.calc_perimeter() - 32) < eps);
    assert(std::abs(r1.calc_area() - 60) < eps);


    Point ppoint1(0, 0), ppoint2(6, 0), ppoint3(6, 6), ppoint4(0, 6);
    Square sq1(ppoint1, ppoint2, ppoint3, ppoint4);
    assert(std::abs(sq1.calc_perimeter() - 24) < eps);
    assert(std::abs(sq1.calc_area() - 36) < eps);


}
