#include "Viewer.h"
#include <iostream>

void TestApp::InitVars() {
	DtTimer.Init();


	Position = VECTOR4D(0.0f, 0.0f, 0.0f,0.0f);
	Orientation = VECTOR4D(0.0f, 0.0f, 0.0f,0.0f);
	Scaling = VECTOR4D(1.0f, 1.0f, 1.0f,0.0f);
}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);
	//int indexCube = PrimitiveMgr.CreateCube();
	//Cubes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);
	//Cubes[1].CreateInstance(PrimitiveMgr9.GetPrimitive(indexCube), &VP);

	//int indexMesh = PrimitiveMgr.CreateMesh("NuBatman.X");
	int indexMesh2 = PrimitiveMgr.CreateMesh("CerdoNuevo.X");
	//Mesh[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexMesh), &VP);
	Mesh2[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexMesh2), &VP);
	int indexTri = PrimitiveMgr.CreateCube();
	Triangle[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri), &VP);

	MATRIX4D View;
	VECTOR4D Pos = VECTOR4D(0.0f, 1.0f, 5.0f,0.0f);
	VECTOR4D Up = VECTOR4D(0.0f, 1.0f, 0.0f,0.0f);
	VECTOR4D LookAt = VECTOR4D(0.0001f, 0.0001f, 0.0001f,0.0f) - Pos;
	View = LookAtRH( Pos, LookAt, Up);
	MATRIX4D Proj;

	Proj = FOVRH(  0.785398f,1280.0f / 720.0f, 0.1f, 1000.0f);
	cout << endl << Proj << endl;
	cout << endl << View << endl;
	//	D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	VP = View*Proj;

}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	Triangle[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Triangle[0].RotateXAbsolute(Orientation.x);
	Triangle[0].RotateYAbsolute(Orientation.y);
	Triangle[0].RotateZAbsolute(Orientation.z);
	Triangle[0].ScaleAbsolute(Scaling.x);
	Triangle[0].Update();

	//Mesh[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	//Mesh[0].RotateXAbsolute(Orientation.x);
	//Mesh[0].RotateYAbsolute(Orientation.y);
	//Mesh[0].RotateZAbsolute(Orientation.z);
	//Mesh[0].ScaleAbsolute(Scaling.x);
	//Mesh[0].Update();
	//OnInput();


	Mesh2[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Mesh2[0].RotateXAbsolute(Orientation.x);
	Mesh2[0].RotateYAbsolute(Orientation.y);
	Mesh2[0].RotateZAbsolute(Orientation.z);
	Mesh2[0].ScaleAbsolute(Scaling.x);
	Mesh2[0].Update();
	OnInput();
	/*
	Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x);
	Cubes[0].Update();

	Cubes[1].TranslateAbsolute(-Position.x,-Position.y, Position.z);
	Cubes[1].RotateXAbsolute(-Orientation.x);
	Cubes[1].RotateYAbsolute(-Orientation.y);
	Cubes[1].RotateZAbsolute(-Orientation.z);
	Cubes[1].ScaleAbsolute(Scaling.x);
	Cubes[1].Update();
	*/
	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
//	Triangle[0].Draw();
	//Mesh[0].Draw();
	Mesh2[0].Draw();
	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	const float vel = 10.0f;
	if (IManager.PressedKey(SDLK_UP)) {
		Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
		Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
		Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
		Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP5)) {
		Orientation.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP6)) {
		Orientation.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP2)) {
		Orientation.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP3)) {
		Orientation.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP0)) {
		Orientation.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
		Orientation.z += 1.0f*DtTimer.GetDTSecs();
	}


}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}