#pragma once
#include<math.h>
class Vector3D
{
public:
	double x;
	double y;
	double z;
	Vector3D() {x = 0.0; y = 0.0; z = 0.0;}
	Vector3D(float x, float y, float z):x(x),y(y),z(z){}
	Vector3D operator -(Vector3D v)
	{
		Vector3D res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}

	Vector3D operator +(Vector3D v)
	{
		Vector3D res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}

	float operator *(Vector3D v)
	{
		return (double)x * v.x + y * v.y + z * v.z;
	}

	Vector3D operator*(double num)
	{
		Vector3D res;
		res.x = x * num;
		res.y = y * num;
		res.z = z * num;
		return res;
	}
	float modulo()
	{
		float aux = sqrt(x * x + y * y + z * z);
		return aux;

	}
};