#include "Parser.h"

Cparser::Cparser()
{

}

Cparser::~Cparser()
{

}

bool Cparser::OpenFile(const char * Filename) {
	Continuar.open(Filename, fstream::in);
	if (!Continuar.is_open()) {
		return false;
	}
	return true;

}
//
//void Cparser::Literate(const char * Filename, /*vector<unsigned short> index,*/ vector<Mesh> MeshCount) {
//
//
//	Mesh *M;
//	if (OpenFile(Filename)) {
//		getline(Continuar, reader);
//		if (reader == "xof 0303txt 0032") {
//			while (!Continuar.eof())
//			{
//				getline(Continuar, reader);
//				int findMesh = reader.find("Mesh mesh");
//
//				if (findMesh != -1) {
//					M = new Mesh();
//
//
//					Continuar >> NVertx >> Nothing;
//					for (int i = 0; i < NVertx; i++) {
//						CVertex4 *V = new CVertex4();
//						//Unnombre >> holder >> Nothing;
//						Continuar >> holder >> Nothing;
//						V->x = holder;
//						Continuar >> holder >> Nothing;
//						V->y = holder;
//						Continuar >> holder >> Nothing >> Nothing;
//						V->z = holder;
//						V->w = 1;
//
//						M->vertices.push_back(V);
//
//					}
//					Continuar >> NIndex >> Nothing;
//					for (int i = 0; i < NIndex; i++) {
//						unsigned short *Ind = new unsigned short();
//						unsigned short *temp = new unsigned short();
//
//						Continuar >> Nothing >> Nothing >> holder >> Nothing;
//						*Ind = holder;
//						M->indices.push_back(Ind);
//						Continuar >> holder >> Nothing;
//						*temp = holder;
//
//						Continuar >> holder >> Nothing >> Nothing;
//						*Ind = holder;
//						M->indices.push_back(Ind);
//						M->indices.push_back(temp);
//					}
//
//					if (reader == "  MeshNormals normals {") {
//						Continuar >> NNormal >> Nothing;
//						for (int i = 0; i < NNormal; i++) {
//							CVertex4 *V = new CVertex4();
//							Continuar >> holder >> Nothing;
//							/*		Vertex[]
//									Vertex[i].nx = holder;
//									Unnombre >> holder >> Nothing;
//									Vertex[i].ny = holder;
//									Unnombre >> holder >> Nothing >> Nothing;
//									Vertex[i].nz = holder;
//									Vertex[i].nw = 1;*/
//
//							V->nx = holder;
//							Continuar >> holder >> Nothing;
//							V->ny = holder;
//							Continuar >> holder >> Nothing >> Nothing;
//							V->nz = holder;
//							V->nw = 1; 
//							M->vertices.push_back(V);
//						}
//
//					}
//					if (reader == "  MeshTextureCoords tc0 {") {
//						//Continuar >> NTexture >> Nothing;
//						//for (int i = 0; i < NTexture; i++) {
//
//						//	Continuar >> holder >> Nothing;
//						//	MeshCount.vertices[i].s = holder
//						//		Vertex[i].s = holder;
//						//	Continuar >> holder >> Nothing >> Nothing;
//						//	Vertex[i].t = holder;
//
//						//}
//
//					}
//					if (reader == "  MeshMaterialList mtls {")
//					{
//
//					}
//				}
//			}
//		}
//		Continuar.close();
//	}
//
//}