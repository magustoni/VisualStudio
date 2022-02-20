#pragma once
class Int3D
{
public:
	int x;
	int y;
	int z;
	Int3D(int xi = 0, int yi = 0, int zi = 0) { x = xi; y = yi; z = zi; };
	bool operator == (Int3D in) { return (this->x == in.x && this->y == in.y && this->z == in.z); }
};