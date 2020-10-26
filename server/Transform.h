#pragma once
#include "Vectors.h"

class Transform{

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		Transform(Vector3 pos, Vector3 rot, Vector3 sca);
		Transform();
		void setPosition(float, float, float);
		void setPosition(Vector3);
		void setRotation(float, float, float);
		void setScale(float, float, float);
};
