#include "Vector2D.h"

void Vector2D::normalize() {
	float l = length();
	if (l > 0) {
		(*this) *= 1 / l;
	}
}
