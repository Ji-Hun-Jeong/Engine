#pragma once

struct Vector2
{
    float x, y;

    // �⺻ ������
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    // ����
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // ����
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // ��Į�� ����
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // ���� ���� (�� ��ҳ��� ����)
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    // ��Į�� ������
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // ���� ������ (�� ��ҳ��� ����)
    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }

    // �� ���� (���� ũ�� ����)
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    // �Ҵ� ������
    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // ���� ���� ����
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // ���� ���� ����
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // ��Į�� �� ���� ����
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // ���� �� ���� ����
    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    // ��Į�� ������ ���� ����
    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // ���� ������ ���� ����
    Vector2& operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    // ��ȣ ����
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    // ũ�� ���
    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // ����ȭ�� ���� ��ȯ
    Vector2 Normalize() const {
        float mag = Magnitude();
        assert(mag);
        return Vector2(x / mag, y / mag);
    }

    // ����� ������
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector2& vec) {
        is >> vec.x >> vec.y;
        return is;
    }
};
