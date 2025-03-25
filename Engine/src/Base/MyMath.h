#pragma once

struct Vector2
{
    float x, y;

    // ±âº» »ý¼ºÀÚ
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    // µ¡¼À
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // »¬¼À
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // ½ºÄ®¶ó °ö¼À
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // º¤ÅÍ °ö¼À (°¢ ¿ä¼Ò³¢¸® °öÇÔ)
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    // ½ºÄ®¶ó ³ª´°¼À
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // º¤ÅÍ ³ª´°¼À (°¢ ¿ä¼Ò³¢¸® ³ª´®)
    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }

    // ºñ±³ ¿¬»ê (º¤ÅÍ Å©±â ±âÁØ)
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    // ÇÒ´ç ¿¬»êÀÚ
    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // µ¡¼À º¹ÇÕ ´ëÀÔ
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // »¬¼À º¹ÇÕ ´ëÀÔ
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // ½ºÄ®¶ó °ö º¹ÇÕ ´ëÀÔ
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // º¤ÅÍ °ö º¹ÇÕ ´ëÀÔ
    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    // ½ºÄ®¶ó ³ª´°¼À º¹ÇÕ ´ëÀÔ
    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // º¤ÅÍ ³ª´°¼À º¹ÇÕ ´ëÀÔ
    Vector2& operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    // ºÎÈ£ º¯°æ
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    // Å©±â °è»ê
    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // Á¤±ÔÈ­µÈ º¤ÅÍ ¹ÝÈ¯
    Vector2 Normalize() const {
        float mag = Magnitude();
        assert(mag);
        return Vector2(x / mag, y / mag);
    }

    // ÀÔÃâ·Â ¿¬»êÀÚ
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector2& vec) {
        is >> vec.x >> vec.y;
        return is;
    }
};
