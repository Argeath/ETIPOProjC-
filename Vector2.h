#pragma once

#define V2D(a, b) Utils::Vector2<double>(a, b)
#define V2(a, b) Utils::Vector2<int>(a, b)

namespace Utils {

	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		SOUTHWEST,
		SOUTHEAST,
		NORTHWEST,
		NORTHEAST
	};

	template<typename T>
	class Vector2 {
	public:
		T x;
		T y;

		Vector2() : x(0), y(0) {}
		Vector2(T a, T b) : x(a), y(b) {}
		Vector2(Direction dir) : x(0), y(0) {
			switch (dir) {
			case NORTHEAST:
				x = 1;
				y = -1;
				break;
			case NORTHWEST:
				x = -1;
			case NORTH:
				y = -1;
				break;
			case SOUTH:
				y = 1;
				break;
			case SOUTHEAST:
				y = 1;
			case EAST:
				x = 1;
				break;
			case SOUTHWEST:
				y = 1;
			case WEST:
				x = -1;
				break;
			}
		}

		Vector2 reversed() {
			return V2D(y, x);
		}

		Vector2& operator+=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		friend Vector2 operator+(Vector2 lhs, const Vector2 &v) {
			Vector2 n = lhs;
			n += v;
			return n;
		}

		Vector2& operator-=(const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		friend Vector2 operator-(Vector2 lhs, const Vector2 &v) {
			Vector2 n = lhs;
			n -= v;
			return n;
		}

		Vector2& operator*=(const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		friend Vector2 operator*(Vector2 lhs, const Vector2 &v) {
			Vector2 n = lhs;
			n *= v;
			return n;
		}

		Vector2& operator/=(const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		friend Vector2 operator/(Vector2 lhs, const Vector2 &v) {
			Vector2 n = lhs;
			n /= v;
			return n;;
		}

		Vector2& operator*=(const T& rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}

		friend Vector2 operator*(Vector2 lhs, const T &c) {
			Vector2 n = lhs;
			n *= c;
			return n;
		}


		Vector2& operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}

		friend Vector2 operator/(Vector2 lhs, const T &c) {
			Vector2 n = lhs;
			n /= c;
			return n;
		}

		friend bool operator==(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x == v2.x && v1.y == v2.y);
		}

		friend bool operator!=(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x != v2.x || v1.y != v2.y);
		}

		friend bool operator>(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x > v2.x && v1.y > v2.y);
		}

		friend bool operator<(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x < v2.x && v1.y < v2.y);
		}

		friend bool operator>=(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x >= v2.x && v1.y >= v2.y);
		}

		friend bool operator<=(const Vector2 &v1, const Vector2 &v2) {
			return (v1.x <= v2.x && v1.y <= v2.y);
		}

	};

}