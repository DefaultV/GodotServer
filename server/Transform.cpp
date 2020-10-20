#include "Transform.h"

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 sca){
	position = pos;
	rotation = rot;
	scale = sca;
}

Transform::Transform(){

	position = Vector3(0,0,0);
	rotation = Vector3(0,0,0);
	scale = Vector3(1,1,1);
}
