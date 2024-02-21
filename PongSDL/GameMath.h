#ifndef USE_GAMEMATH
#define USE_GAMEMATH
#include <math.h>
struct Vector2 {
    double x;
    double y;
    Vector2() :x(0), y(0) {}
    Vector2(double _x, double _y) : x(_x), y(_y) {}
    Vector2(double _val) : x(_val), y(_val) {}
    Vector2& operator+=(const Vector2& _other) {
        this->x += _other.x;
        this->y += _other.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& _other) {
        this->x -= _other.x;
        this->y -= _other.y;
        return *this;
    }
    friend Vector2 operator+(Vector2 lhs, const Vector2& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Vector2 operator-(Vector2 lhs, const Vector2& rhs) {
        lhs -= rhs;
        return lhs;
    }
    Vector2& operator*= (const double& other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }
    friend Vector2 operator* (const double& lhs, Vector2 rhs) {
        return rhs *= lhs;
    }
    friend Vector2 operator* (Vector2 lhs, const double& rhs) {
        return lhs *= rhs;
    }
    static Vector2 one() {
        return Vector2(1, 1);
    }
    static Vector2 up() {
        return Vector2(0, 1);
    }
    static Vector2 right() {
        return Vector2(1, 0);
    }
    static Vector2 zero() {
        return Vector2();
    }
    static double dot(Vector2 a, Vector2 b) {
        return (a.x * b.x) + (a.y * b.y);
    }
    double GetMagnitude() {
        return sqrt(pow(x, 2)+ pow(y, 2));
    }
    void Normalise() {
        double mag = GetMagnitude();
        x = x / mag;
        y = y / mag;
    }
};
long double Lerp(long double a, long double b, long double fac);
#endif // !USE_GAMEMATH


