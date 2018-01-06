#pragma once
#include <fstream>
#include <string>
#include "MATRIX4D.h"
#include <vector>
#include "UtilsGL.h"

using namespace std;
struct CVertex4 {

	float x, y, z, w;
	float nx, ny, nz, nw;
	float s, t;
};

struct Material {
	GLuint IB;
	GLuint diffuse_textID;
	string diffusePath;
	vector <unsigned short> indices;
	int ind;
};
struct Mesh {
	CVertex4			*vertices;
	unsigned short 		*indices;
	GLuint			VB;
	GLuint			IB;
	int				vert, ind, totalMaterial;
	vector <Material*> materials;

};
class Parser_
{
public:
	Parser_();
	~Parser_();
	bool OpenFile(const char * Filename);

	fstream Continuar;

	string reader;
	int NVertx;
	int NIndex;
	int NNormal;
	int NTexture;

	char tempchar;
	float holder;

	vector<Mesh*> Literate(const char * Filename, /*vector<unsigned short> index,*/ vector<Mesh*> MeshCount);
};

