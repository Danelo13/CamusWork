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
		float u, v;

};
struct Material {
	GLuint IB;
	GLuint diffuse_textID;
	string diffusePath;
	vector <unsigned short> indices;
	int ind;
};


struct CTexture {
#ifdef USING_OPENGL_ES
	GLuint TexID;
#elif defined(USING_D3D11)


#endif
	int x, y, channels;
};
struct Mesh {
	CVertex4			*vertices;
	unsigned short		*indices;
	int num_Vertices;
	int num_Indices;
	vector<Material> MaterialList;
	vector<CTexture> Textures;
};


class Cparser {
public:
	Cparser();
	~Cparser();

	bool OpenFile(const char * Filename);

	fstream Continuar;

	string reader;
	int NVertx;
	int NIndex;
	int NNormal;
	int NTexture;

	char Nothing;
	float holder;

	void Literate(const char * Filename, /*vector<unsigned short> index,*/ vector<Mesh> MeshCount);
};