#ifndef UAD_MESH_GL_H
#define UAD_MESH_GL_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>
#include "MATRIX4D.h"

#include "PrimitiveBase.h"
#include "UtilsGL.h"
// #include "Parser.h"
#include "Parser_.h"
struct buffers {
	GLuint			VB;
	GLuint			IB;
	int num_Vertices;
	int num_Indices;
};

class MeshGL : public PrimitiveBase {
public:
	MeshGL() : shaderID(0) {}
	void Create() {};
	void Create(char *File);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	GLuint	shaderID;
	GLint	vertexAttribLoc;
	GLint	normalAttribLoc;
	GLint	uvAttribLoc;

	GLint  matWorldViewProjUniformLoc;
	GLint  matWorldUniformLoc;
	Material *XMaterial;
	vector <Mesh*> Meshes;
	vector <buffers> Info;


	Parser_ Parseador;
	
	MATRIX4D	transform;
};


#endif