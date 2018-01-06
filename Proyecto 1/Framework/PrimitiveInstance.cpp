#include "PrimitiveInstance.h"

void PrimitiveInst::TranslateAbsolute(float x, float y, float z) {
	Position = Translation( x, y, z);
}

void PrimitiveInst::RotateXAbsolute(float ang) {
	RotacionX = RotationX(ang);
}

void PrimitiveInst::RotateYAbsolute(float ang) {
	RotacionY = RotationY(ang);
}

void PrimitiveInst::RotateZAbsolute(float ang) {
	RotacionZ = RotationZ(ang);
}

void PrimitiveInst::ScaleAbsolute(float sc) {
	 Scale = Scaling( sc, sc, sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z) {

	MATRIX4D tmp = Translation( x, y, z);
	Position = Position * tmp;
}

void PrimitiveInst::RotateXRelative(float ang) {

	MATRIX4D tmp = RotationX(ang);
	RotacionX = RotacionX * tmp;
}

void PrimitiveInst::RotateYRelative(float ang) {

	MATRIX4D tmp = RotationY(ang);
	RotacionY = RotacionY * tmp;
}

void PrimitiveInst::RotateZRelative(float ang) {

	MATRIX4D tmp = RotationZ(ang);
	RotacionZ = RotacionZ * tmp;
}

void PrimitiveInst::ScaleRelative(float sc) {

	MATRIX4D tmp = Scaling(sc,sc,sc);
	Scale = Scale * tmp;
}

void PrimitiveInst::Update() {
	Final = Scale*RotacionX*RotacionY*RotacionZ*Position;
}

void PrimitiveInst::Draw() {
	pBase->Draw(&Final.m[0][0], &(*pViewProj).m[0][0]);
}
