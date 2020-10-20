#pragma once
#include "Vectors.h"

class Transform{

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;

		Transform(Vector3 pos, Vector3 rot, Vector3 sca);
		Transform();
};
