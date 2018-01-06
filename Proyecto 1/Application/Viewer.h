#include <Core.h>
#include <PrimitiveManager.h>
#include <PrimitiveInstance.h>

#include <MATRIX4D.h>
#include <VECTOR4D.h>
#include <Timer.h>

class TestApp : public AppBase {
public:
	TestApp() : AppBase() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();

	void OnUpdate();
	void OnDraw();
	void OnInput();

	void OnPause();
	void OnResume();

	void OnReset();

	PrimitiveManager PrimitiveMgr;
	PrimitiveInst	Mesh[10];
	PrimitiveInst	Mesh2[10];
	PrimitiveInst	Triangle[10];

	VECTOR4D		Position;
	VECTOR4D		Orientation;
	VECTOR4D		Scaling;
	MATRIX4D		WorldTransform;

	MATRIX4D		View;
	MATRIX4D		Projection;
	MATRIX4D		VP;



	bool	FirstFrame;
	Timer	DtTimer;
	float Dtsecs;
	int CamSelection;
};