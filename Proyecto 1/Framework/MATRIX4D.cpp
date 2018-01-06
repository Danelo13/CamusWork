
#include "MATRIX4D.h"


MATRIX4D::MATRIX4D()
{
}

MATRIX4D::MATRIX4D(MATRIX4D& A)
{
	*this = A;
}

MATRIX4D::MATRIX4D(
	float a00, float a01, float a02, float a03,
	float a10, float a11, float a12, float a13,
	float a20, float a21, float a22, float a23,
	float a30, float a31, float a32, float a33)
{
	m00 = a00; m01 = a01; m02 = a02; m03 = a03;
	m10 = a10; m11 = a11; m12 = a12; m13 = a13;
	m20 = a20; m21 = a21; m22 = a22; m23 = a23;
	m30 = a30; m31 = a31; m32 = a32; m33 = a33;
}

MATRIX4D::MATRIX4D(
	VECTOR4D &row0,
	VECTOR4D &row1,
	VECTOR4D &row2,
	VECTOR4D &row3)
{
	Row0 = row0;
	Row1 = row1;
	Row2 = row2;
	Row3 = row3;
}
//MATRIX4D& MATRIX4D::operator=(float *X) {
//	
//	for (int i = 0; i < 16; i++)
//		this->v[i] = X[i];
//	return *this;
//}

MATRIX4D::~MATRIX4D()
{
}

ostream& operator<<(ostream& out, MATRIX4D &A)
{
	for (int j = 0; j < 4; j++) out << A.Row[j] << endl;
	return out;
}
istream& operator >> (istream& in, MATRIX4D &A)
{
	for (int j = 0; j < 4; in >> A.Row[j++]);//Otra forma 
	return in;
}


MATRIX4D operator*(MATRIX4D& A, MATRIX4D& B)
{
	MATRIX4D R = Zero();
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			for (int k = 0; k < 4; k++)
				R.m[j][i] += A.m[j][k] * B.m[k][i];//El valor anterior + el producto
	return R;

}

VECTOR4D operator*(VECTOR4D& V, MATRIX4D& M)
{
	VECTOR4D R(0, 0, 0, 0);
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			R.v[j] += V.v[i] * M.m[i][j];

	return R;
}
VECTOR4D operator*(MATRIX4D& M, VECTOR4D& V)
{
	return VECTOR4D(
		Dot(M.Row0, V),
		Dot(M.Row1, V),
		Dot(M.Row2, V),
		Dot(M.Row3, V));
}
MATRIX4D operator*(MATRIX4D& M, float X) {
	MATRIX4D R;
	for (int i = 0; i < 16; i++) {
		R.v[i] = X * M.v[i];
	}
	return R;
}

MATRIX4D Zero()
{
	MATRIX4D Z;
	memset(&Z, 0, sizeof(MATRIX4D));
	return Z;
}
MATRIX4D Identity()
{
	MATRIX4D I = Zero();
	for (int i = 0; i < 4; i++) I.m[i][i] = 1.0f;
	return I;
}

MATRIX4D Translation(float dx, float dy, float dz)
{
	MATRIX4D T = Identity();
	T.m30 = dx;
	T.m31 = dy;
	T.m32 = dz;
	return T;
}

MATRIX4D RotationX(float theta)
{
	MATRIX4D R = Identity();
	R.m11 = cosf(theta);
	R.m22 = R.m11;
	R.m21 = sinf(theta);
	R.m12 = -R.m21;
	return R;
}
MATRIX4D RotationY(float theta) {
	MATRIX4D R = Identity();
	R.m22 = R.m00 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;
	return R;
}
MATRIX4D RotationZ(float theta) {
	MATRIX4D R = Identity();
	R.m00 = cosf(theta);
	R.m20 = -sinf(theta);
	R.m02 = -R.m20;
	return R;
}
MATRIX4D Scaling(float sx, float sy, float sz)
{
	MATRIX4D S = Zero();
	S.m00 = sx;
	S.m11 = sy;
	S.m22 = sz;
	S.m33 = 1;
	return S;

}

float Det3(MATRIX4D& M) {
	float R;
	R = M.m00*M.m11*M.m22 + M.m01*M.m12*M.m20 + M.m10*M.m21*M.m02
		- M.m02*M.m11*M.m20 - M.m12*M.m21*M.m00 - M.m01*M.m10*M.m22;
	return R;
}

float Det3(MATRIX4D& M, int notX, int notY) {
	MATRIX4D A = Zero();
	int k = 0; int l = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j != notX || i != notY) {
				A.m[k][l] = M.m[i][j];
				l++;
				if (l > 3) {
					l = 0;
					k++;
				}
			}
		}
	}
	float R;
	R = A.m00*A.m11*A.m22 + A.m01*A.m12*A.m20 + A.m10*A.m21*A.m02
		- A.m02*A.m11*A.m20 - A.m12*A.m21*A.m00 - A.m01*A.m10*A.m22;
	return R;

}
float Det4(MATRIX4D& M) {
	return (M.m00 * (Det3(M, 0, 0))) - (M.m10 * (Det3(M, 1, 0))) + (M.m20  * (Det3(M, 2, 0))) - (M.m30 * (Det3(M, 3, 0)));
}



MATRIX4D Transpose(MATRIX4D& M) {
	MATRIX4D t;
	t.m00 = M.m00;
	t.m01 = M.m10;
	t.m02 = M.m20;
	t.m03 = M.m30;
	t.m10 = M.m01;
	t.m11 = M.m11;
	t.m12 = M.m21;
	t.m13 = M.m31;
	t.m20 = M.m02;
	t.m21 = M.m12;
	t.m22 = M.m22;
	t.m23 = M.m32;
	t.m30 = M.m03;
	t.m31 = M.m13;
	t.m32 = M.m23;
	t.m33 = M.m33;
	return t;
};
MATRIX4D Cofactors(MATRIX4D& M) {
	MATRIX4D A;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			A.m[i][j] = Det3(M, i, j);
		}
	return A;
}
MATRIX4D Inverse(MATRIX4D& M) {
	MATRIX4D I;
	if (Det4(M) != 0) {
		MATRIX4D ADT;
		ADT = Cofactors(M);
		ADT = Transpose(ADT);
		I = ADT * (1 / Det4(M));
	}
	else {
		cout << "Matriz no tiene Invertida" << endl;
		I = M;
	}
	return I;
}


MATRIX4D LookAtRH(VECTOR4D& EyePos, VECTOR4D& Target, VECTOR4D& Up) {
	VECTOR4D DirX, DirY, DirZ;
	DirZ = Normalize(EyePos - Target);
	DirX = Normalize(Cross3(Up, DirZ));
	DirY = Cross3(DirZ, DirX);

	MATRIX4D Vista = MATRIX4D(DirX.x, DirY.x, DirZ.x, 0,
		DirX.y, DirY.y, DirZ.y, 0,
		DirX.z, DirY.z, DirZ.z, 0,
		-Dot(DirX, EyePos), -Dot(DirY, EyePos), -Dot(DirZ, EyePos), 1);
	return Vista;
	
}

MATRIX4D FOVRH(float fovy, float ratio, float zNear, float zFar) {
	float h = 1 / tan(fovy / 2);
	float w = h*ratio;
	MATRIX4D P = MATRIX4D(h, 0, 0, 0,
						  0, w, 0, 0,
						  0, 0, zFar / (zNear - zFar), -1,
						  0, 0, zNear*zFar / (zNear - zFar), 0);
	return P;
}


MATRIX4D LookAtLH(VECTOR4D& EyePos, VECTOR4D& Target, VECTOR4D& Up) {
	VECTOR4D DirX, DirY, DirZ;
	DirZ = Normalize(Target - EyePos );
	DirX = Normalize(Cross3(Up, DirZ));
	DirY = Cross3(DirZ, DirX);

	MATRIX4D Vista = MATRIX4D(DirX.x, DirY.x, DirZ.x, 0,
		DirX.x, DirY.x, DirZ.x, 0,
		DirX.x, DirY.x, DirZ.x, 0,
		-Dot(DirX, EyePos), -Dot(DirY, EyePos), -Dot(DirZ, EyePos), 1);
	return Vista;

}

MATRIX4D FOVLH(float fovy, float ratio, float zNear, float zFar) {
	float h = 1 / tan(fovy / 2);
	float w = h*ratio;
	MATRIX4D P = MATRIX4D(w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, zFar / (zNear - zFar), -1,
		0, 0, zNear*zFar / (zNear - zFar), 0);
	return P;
}