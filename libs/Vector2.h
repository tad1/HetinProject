#pragma once
#include <cmath>

template <class T>
class Vector2T {
public:
    T x;
    T y;

    Vector2T(T x_ = 0, T y_ = 0) : x(x_), y(y_) {};

    //casting
    template <class T2>
    operator Vector2T<T2>() {
        Vector2T<T2> result;
        result.x = (T2)x;
        result.y = (T2)y;
        return result;
    }


#pragma region UnaryOperators

    Vector2T operator- () {
        Vector2T<T> result = *this;
        result.x *= -1;
        result.y *= -1;
        return result;
    };

    template <class T2>
    Vector2T operator + (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x += arg.x;
        result.y += arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator - (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x -= arg.x;
        result.y -= arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator * (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x *= arg.x;
        result.y *= arg.y;
        return result;
    };

    template <class T2>
    Vector2T operator * (const T2 arg) {
        Vector2T<T> result = *this;
        result.x *= arg;
        result.y *= arg;
        return result;
    };

    template <class T2>
    Vector2T operator / (const T2 arg) {
        Vector2T<T> result = *this;
        result.x /= arg;
        result.y /= arg;
        return result;
    };


    
    template <class T2>
    Vector2T operator / (const Vector2T<T2> arg) {
        Vector2T<T2> result = *this;
        result.x /= arg.x;
        result.y /= arg.y;
        return result;
    };

    bool operator !() {
        return !this->x && !this->y;
    }
#pragma endregion

#pragma region BinaryOperators


    template <class T2>
    void operator+= (const Vector2T<T2> arg) {
        this->x += arg.x;
        this->y += arg.y;
    }

    template <class T2>
    void operator-= (const Vector2T<T2> arg) {
        this->x -= arg.x;
        this->y -= arg.y;
    }
    
    template <class T2>
    bool operator == (Vector2T<T2> param) {
        return this->x == param.x && this->y == param.y;
    }

    template <class T2>
    bool operator != (Vector2T<T2> param) {
        return this->x != param.x || this->y != param.y;
    }
#pragma endregion

    

    T SqrMagnitude() {
        return this->x * this->x + this->y * this->y;
    }

    T Magnitude() {
        return sqrt(SqrMagnitude());
    }

    Vector2T<T> Normalize() {
        Vector2T<float> result = *this;
        result /= result.magnitude();
        return result;
    }

    const char* ToString() {
        //TODO: make dynamic
        char* result = new char[100];
        strcpy(result, "Vector2(");
        strcat(result, String::ToString(this->x));
        strcat(result, ",");
        strcat(result, String::ToString(this->y));
        strcat(result, ")");
        return (const char*)result;
    }

#pragma region StaticMethods
    template <class T2, class T3>
    static T Dot(Vector2T<T2> a, Vector2T<T3> b) {
        return a.x * b.x + a.y * b.y;
    }

    //TODO: upgrade if needed to convert into 3d vector
    template <class T2, class T3>
    static T Cross(Vector2T<T2> a, Vector2T<T3> b) {
        return this->x * b.y - this->y * b.x;

    }

    template <class T2, class T3>
    T Distance(Vector2T<T2> a, Vector2T<T3> b) {
        Vector2T<T> result(a.x - b.x, a.y - b.y);
        return result.SqrMagnitude();

    }

    template <class T2>
    static Vector2T<T> Lerp(Vector2T<T2> a, Vector2T<T2> b, float t) {
        Vector2T<T> direction(b.x - a.x, b.y - a.y);
        return a + (direction * t);
    }

    template <class T2, class T3>
    static Vector2T<T> Max(Vector2T<T2> a, Vector2T<T2> b) {
        Vector2T<T> result;
        result.x = max(a.x, b.x);
        result.y = max(a.y, b.y);
        return result;
    }

    template <class T2, class T3>
    static Vector2T<T> Min(Vector2T<T2> a, Vector2T<T2> b) {
        Vector2T<T> result;
        result.x = min(a.x, b.x);
        result.y = min(a.y, b.y);
        return result;
    }




#pragma endregion

};

typedef Vector2T<float> Vector2;
typedef Vector2T<int> GridVector;
