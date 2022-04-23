#include <cmath>
#include <iostream>

struct Vector {
    double _x, _y;
    Vector(double x, double y) : _x(x), _y(y) {};
};

template <class T=Vector, class K=float>
K distance_func2 (const T &a,const T &b) {
        T delta=T(b._x-a._x, b._y - a._y);
        return static_cast<K>(delta._x*delta._x + delta._y*delta._y);
};

template <class K=float>
K uncook(const K &x) { return sqrt(x); }


double bezier_y(float t) {
    double _coeff[4] = {0.l, 0.l, 3.l, -2.l};

    double result = _coeff[0]+(_coeff[1]+(_coeff[2]+(_coeff[3]*t))*t)*t;
    return result;
}

float find_distance(float r, float s, int steps = 7)
{

    const float inc(s/steps);
    std::cout << "Inc: " << inc << "\n";
    float ret(0);
    Vector last(0, bezier_y(r));
    std::cout << "x: " << last._x << " y: " << last._y << "\n";

    for(int i = steps - 1; i > 0; --i)
    {
        r += inc;
        const Vector n(0, bezier_y(r));
        std::cout << "n.x: " << n._x << " n.y: " << n._y << " r: " << r << "\n";
        ret+=uncook(distance_func2(last,n));
        last=n;
    }
    ret+=uncook(distance_func2(last, Vector(0, bezier_y(s))));

    return ret;
}

template<typename T>
inline T real_precision()
{ return T(1e-8); }

template<typename T>
inline bool approximate_equal(const T &a, const T &b)
{ return a < b ? b - a < real_precision<T>() : a - b < real_precision<T>(); }

int main() {
    std::cout.precision(20);
    double l = find_distance(0, 1, 7);
    if (approximate_equal(1.0, l)) {
        std::cout << "\nOK\n\n";
    } else {
        std::cout << "\nError. Expected: " << 1.0 << ", but got: " << l << "\n\n";
    }

	return 0;
}
