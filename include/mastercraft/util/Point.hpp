

#ifndef MASTERCRAFT_POINT_HPP
#define MASTERCRAFT_POINT_HPP



#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>


namespace mastercraft::util {

    template<typename T>
    class Point {
        static_assert(std::is_arithmetic<T>::value, "Arithmetic type is required");

    public:
        static constexpr uint16_t NEAR_THRESHOLD = 10;

        T x = static_cast<T>(0);
        T y = static_cast<T>(0);

        ///////////////////// CONSTRUCTOR & DESTRUCTOR /////////////////////

        Point() = default;

        Point(T x, T y);

        template<typename U>
        Point<T>(const Point<U> &p);

        ///////////////////////////// OPERATORS ////////////////////////////

        /**
         * Allows array-like access
         */
        T &operator[](int i);

        bool operator==(const Point<T> &other) const;

        Point<T> operator+(const Point<T> &other) const;

        Point<T> operator-(const Point<T> &other) const;

        int32_t operator^(const Point<T> &other) const;

        template<typename U>
        Point<T> operator*(const Point<U> &other) const;

        template<typename U>

        Point<T> operator*(U factor) const;

        template<typename U>
        friend std::ostream &operator<<(std::ostream &os, const Point<U> &p);

        ///////////////////////////// OTHERS ///////////////////////////////

        [[nodiscard]] Point<T> rotate(int16_t angle, const Point<double> &center) const;

        [[nodiscard]] Point<T> translate(const Point<T> &translation) const;

        [[nodiscard]] static Point<double> center(const std::vector<Point<T>> &points);

        [[nodiscard]] static Point<double> center(Point<T> first);

        template<typename... Args>
        [[nodiscard]] static Point<double> center(Point<T> first, Args... args);
    };



    template<typename T>
    using Vector = Point<T>;

    typedef Point<int8_t> Point8;
    typedef Point<int16_t> Point16;
    typedef Point<int32_t> Point32;
    typedef Point<int64_t> Point64;
    typedef Point<float> PointF;
    typedef Point<double> PointD;

    typedef Point<uint8_t> Pointu8;
    typedef Point<uint16_t> Pointu16;
    typedef Point<uint32_t> Pointu32;
    typedef Point<uint64_t> Pointu64;

    typedef Vector<int8_t> Vector8;
    typedef Vector<int16_t> Vector16;
    typedef Vector<int32_t> Vector32;
    typedef Vector<int64_t> Vector64;
    typedef Vector<float> VectorF;
    typedef Vector<double> VectorD;

    typedef Vector<uint8_t> Vectoru8;
    typedef Vector<uint16_t> Vectoru16;
    typedef Vector<uint32_t> Vectoru32;
    typedef Vector<uint64_t> Vectoru64;


    static double radians(int16_t deg) {
        constexpr double r = M_PI / 180.0;
        return deg * r;
    }


    template<typename T>
    static int orientation(const Point<T> &a, const Point<T> &b, const Point<T> &c) {
        int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

        if (val == 0) {
            return 0;
        }
        return val > 0 ? 1 : 2;
    }


    template<typename T>
    Point<T>::Point(T t_x, T t_y) :
            x(t_x), y(t_y) {
    }


    template<typename T>
    template<typename U>
    Point<T>::Point(const Point<U> &p) {
        static_assert(std::is_arithmetic<U>::value, "Arithmetic type is required");
        this->x = static_cast<T>(p.x);
        this->y = static_cast<T>(p.y);
    }


    template<typename T>
    T &Point<T>::operator[](int i) {
        return *(&x + i);
    }


    template<typename T>
    bool Point<T>::operator==(const Point<T> &other) const {
        return (std::abs(this->x - other.x) < NEAR_THRESHOLD
                && std::abs(this->y - other.y) < NEAR_THRESHOLD);
    }


    template<typename T>
    Point<T> Point<T>::operator+(const Point<T> &other) const {
        return Point<T>(this->x + other.x, this->y + other.y);
    }


    template<typename T>
    Point<T> Point<T>::operator-(const Point<T> &other) const {
        return Point<T>(this->x - other.x, this->y - other.y);
    }


    template<typename T>
    template<typename U>
    Point<T> Point<T>::operator*(const Point<U> &other) const {
        static_assert(std::is_arithmetic<U>::value, "Arithmetic type is required");
        return Point<T>(
                static_cast<T>(this->x * other.x),
                static_cast<T>(this->y * other.y)
        );
    }


    template<typename U>
    std::ostream &operator<<(std::ostream &os, const Point<U> &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }


    template<typename T>
    template<typename U>
    Point<T> Point<T>::operator*(U factor) const {
        static_assert(std::is_arithmetic<U>::value, "Arithmetic type is required");
        return Point<T>(
                static_cast<T>(this->x * factor),
                static_cast<T>(this->y * factor)
        );
    }


    template<typename T>
    int32_t Point<T>::operator^(const Point<T> &other) const {
        return this->x * other.y - this->y * other.x;
    }


    template<typename T>
    Point<T> Point<T>::rotate(int16_t angle, const Point<double> &center) const {
        double x = this->x - center.x;
        double y = this->y - center.y;
        double rad = radians(angle);
        double c = cos(rad);
        double s = sin(rad);

        return Point<T>(
                static_cast<T>(x * c - y * s + center.x),
                static_cast<T>(x * s + y * c + center.y)
        );
    }


    template<typename T>
    Point<T> Point<T>::translate(const Point<T> &translation) const {
        return Point<T>(
                this->x + translation.x,
                this->y + translation.y
        );
    }


    template<typename T>
    Point<double> Point<T>::center(const std::vector<Point<T>> &points) {
        uint64_t size = points.size();
        double x = 0, y = 0;

        for (Point<T> p: points) {
            x += p.x;
            y += p.y;
        }

        return Point<double>(
                x / size,
                y / size
        );
    }


    template<typename T>
    Point<double> Point<T>::center(Point<T> first) {
        return Point<double>(first);
    }


    template<typename T>
    template<typename... Args>
    Point<double> Point<T>::center(Point<T> first, Args... args) {
        return Point<T>::center({ args... });
    }
}


#endif //MASTERCRAFT_POINT_HPP
