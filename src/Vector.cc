#include "Vector.hh"
#include <cmath>

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

int Vector2::exists() const {
    return this->x != 0 || this->y != 0;
}

float Vector2::area() const {
    return abs(this->x * this->y);
}

float Vector2::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

int Vector2::iX() const {
    return (int)this->x;
}

int Vector2::iY() const {
    return (int)this->y;
}

Vector2 Vector2::operator+(Vector2 other) const {
    return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(Vector2 other) const {
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(Vector2 other) const {
    return Vector2(this->x * other.x, this->y * other.y);
}

Vector2 Vector2::operator/(Vector2 other) const {
    return Vector2(this->x / other.x, this->y / other.y);
}

Vector2 Vector2::operator+=(Vector2 other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2 Vector2::operator*(float other) const {
    return Vector2(this->x * other, this->y * other);
}

Vector2 Vector2::operator/(float other) const {
    return Vector2(this->x / other, this->y / other);
}

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Rect2::Rect2() {
    // does nothing I think.
}

Rect2::Rect2(Vector2 pos, Vector2 size) {
    this->pos = pos;
    this->size = size;
}

Rect2::Rect2(float x, float y, float w, float h) {
    this->pos.x = x;
    this->pos.y = y;
    this->size.x = w;
    this->size.y = h;
}

Vector2 Rect2::end() const {
    return this->pos + this->size;
}
