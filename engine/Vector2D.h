#ifndef SALAMANDER_VECTOR2D_H
#define SALAMANDER_VECTOR2D_H

class Vector2D {
public:
    Vector2D() = default;
    Vector2D(int x, int y) : m_x{x}, m_y{y} {}

    [[nodiscard]] int x() const noexcept { return m_x; }
    [[nodiscard]] int y() const noexcept { return m_y; }
    void set_x(int x) noexcept { m_x = x; }
    void set_y(int y) noexcept { m_y = y; }


    Vector2D operator+(Vector2D &other) const { return Vector2D{m_x + other.m_x, m_y + other.m_y}; }
    Vector2D operator-(Vector2D &other) const { return Vector2D{m_x - other.m_x, m_y - other.m_y}; }
    Vector2D &operator+=(Vector2D &other) { m_x += other.m_x; m_y += other.m_y; return *this; }
    Vector2D &operator-=(Vector2D &other) { m_x -= other.m_x; m_y -= other.m_y; return *this; }

private:
    int m_x{};
    int m_y{};
};

#endif //SALAMANDER_VECTOR2D_H
