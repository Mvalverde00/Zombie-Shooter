#ifndef VECTORS2D
#define VECTORS2D

#include <SDL.h>
#include <math.h>

class Vector2D {
public:

	float x, y;

	Vector2D() {
		x = 0;
		y = 0;
	}

	Vector2D(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void norm() {
		float denom = std::sqrt(x*x + y*y);
		if (denom == 0) return;
		x/=denom;
		y/=denom;
	}

	Vector2D operator + (Vector2D v) const{
		return Vector2D(x + v.x, y + v.y);
	}
	void operator += (Vector2D v) {
		x += v.x;
		y += v.y;
	}

	Vector2D operator - (Vector2D v) const{
		return Vector2D(x - v.x, y - v.y);
	}
	Vector2D operator * (float a) const {
		return Vector2D(x*a, y*a);
	}

	bool operator == (Vector2D v) const{
		return x == v.x && y == v.y;
	}

	operator SDL_Point () {
		SDL_Point p;
		p.x = x;
		p.y = y;
		return p;
	}

	friend std::ostream& operator << (std::ostream& os, const Vector2D& v) {
	    os << '(' << v.x << ", " << v.y << ")\n";
	    return os;
	}

};

#endif