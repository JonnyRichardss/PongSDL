#ifndef USE_GAMEMATH
#define USE_GAMEMATH
struct Vector2 {
    float x;
    float y;
    Vector2() :x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
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
    Vector2& operator*= (const float& other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }
    Vector2& operator*= (const int& other) {
        this->x *= other;
        this->y *= other;
        return *this;
    }
    friend Vector2 operator* (const int& lhs, Vector2 rhs) {
        return rhs *= lhs;
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
};
long double Lerp(long double a, long double b, long double fac);
#endif // !USE_GAMEMATH


