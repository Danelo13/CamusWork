#include "MeshGL.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void MeshGL::Create(char* File) {
	shaderID = glCreateProgram();

	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	GLuint vshader_id = createShader(GL_VERTEX_SHADER, vsSourceP);
	GLuint fshader_id = createShader(GL_FRAGMENT_SHADER, fsSourceP);

	glAttachShader(shaderID, vshader_id);
	glAttachShader(shaderID, fshader_id);

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	vertexAttribLoc = glGetAttribLocation(shaderID, "Vertex");
	normalAttribLoc = glGetAttribLocation(shaderID, "Normal");
	uvAttribLoc = glGetAttribLocation(shaderID, "UV");

	matWorldViewProjUniformLoc = glGetUniformLocation(shaderID, "WVP");
	matWorldUniformLoc = glGetUniformLocation(shaderID, "World");



	
	Meshes = Parseador.Literate(File,Meshes);

	for (int i = 0; i < Meshes.size(); i++) {
	cout << "size " << Meshes.size() << endl;

		glGenBuffers(1, &Meshes[i]->VB);
		glBindBuffer(GL_ARRAY_BUFFER, Meshes[i]->VB);
		glBufferData(GL_ARRAY_BUFFER, Meshes[i]->vert * sizeof(CVertex4), Meshes[i]->vertices , GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//for (int j = 0; j < Meshes[i]->ind * 3; ++j) {

			glGenBuffers(1, &Meshes[i]->IB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->IB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->ind * sizeof(unsigned short) , Meshes[i]->indices, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//}
	}
	MATRIX4D &transform = Identity();
}

void MeshGL::Transform(float *t) {
	for (int i = 0; i < 16; i++)
		transform.v[i] = t[i];
}

void MeshGL::Draw(float *t, float *vp) {
	glUseProgram(shaderID);

	if (t)
		for (int i = 0; i < 16; i++)
			transform.v[i] = t[i];

	MATRIX4D VP;
	for (int i = 0; i < 16; i++)
		VP.v[i] = vp[i];
	MATRIX4D WVP = transform*VP;

	glUniformMatrix4fv(matWorldUniformLoc, 1, GL_FALSE, t);
	glUniformMatrix4fv(matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);

	for (int i = 0; i < Meshes.size(); i++) {

		glBindBuffer(GL_ARRAY_BUFFER, Meshes[i]->VB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Meshes[i]->IB);

		glEnableVertexAttribArray(vertexAttribLoc);
		glEnableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1)
			glEnableVertexAttribArray(uvAttribLoc);

		glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(0));
		glVertexAttribPointer(normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(16));

		if (uvAttribLoc != -1)
			glVertexAttribPointer(uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex4), BUFFER_OFFSET(32));

		glDrawElements(GL_TRIANGLES, Meshes[i]->ind, GL_UNSIGNED_SHORT, 0);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertexAttribLoc);
		glDisableVertexAttribArray(normalAttribLoc);

		if (uvAttribLoc != -1) {
			glDisableVertexAttribArray(uvAttribLoc);
		}
	}
	glUseProgram(0);
}

void MeshGL::Destroy() {
	glDeleteProgram(shaderID);
}