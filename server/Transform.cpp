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

void Transform::setPosition(Vector3 vec){

	position.x = vec.x;
	position.y = vec.y;
	position.z = vec.z;
}

void Transform::setPosition(float x, float y, float z){

	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::setRotation(float x, float y, float z){

	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Transform::setScale(float x, float y, float z){

	scale.x = x;
	scale.y = y;
	scale.z = z;
}

