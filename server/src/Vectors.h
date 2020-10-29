#pragma once
#include <cmath>

struct Vector3{

	float x, y, z;
	Vector3(float w, float r, float q){
		x = w;
		y = r;
		z = q;
	}
	Vector3(){}
	float distanceTo(Vector3 vec){

		return sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2) + pow(z - vec.z, 2));
	}
	float distanceTo_manhatten(Vector3 vec){

		return abs(x - vec.x) + abs(y - vec.y) + abs(z - vec.z);
	}
	Vector3 operator*(float mul){

		Vector3 vec;
		vec.x = x * mul;
		vec.y = y * mul;
		vec.z = z * mul;
		return vec;
	}
};
