#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "VertexArray.hpp"
#include "Mesh.h"
#include "bezier1D.h"
#include "kdtree.h"
#define MINIMUM_VERTCIES_FOR_BVH 100

class BVH {
public:
	BoundingBox *box;
	struct BVH *left;
	struct BVH *right;
	int level;

	BVH();
	BVH(BVH & bvh_other);
};

class MeshConstructor
{
	
	VertexArray vao;
	IndexBuffer *ib;
	//TO DO: add bounding box data base and build it in the constructor 
	std::vector<VertexBuffer*> vbs;
	bool is2D;
	int unsigned indicesNum;
	void make_tree(std::vector<glm::vec3> point_list);
	// old function
	BVH* MeshConstructor::make_BVH(Node node, BoundingBox daddy, bool is_left, int level);
	// new function
	BVH* MeshConstructor::make_BVH(Node node, std::vector<glm::vec3> point_list, int level);
	void InitLine(IndexedModel &model);
	void InitMesh(IndexedModel &model);
	void CopyMesh(const MeshConstructor &mesh);
	void CopyLine(const MeshConstructor &mesh);
	
	
public:
	Kdtree tree;

	BVH bvh;

	//TO DO: add collision detection function which get other MeshConstructor and Mat4 of related transformasions. The function may return a pointer to the relevant Bounding Box when collide
	enum SimpleShapes
	{
		Axis,
		Cube,
		Octahedron,
		Tethrahedron,
		BezierLine,
		BezierSurface,
	};
	MeshConstructor(const int type);
	MeshConstructor(Bezier1D *curve,bool isSurface,unsigned int resT,unsigned int resS);
	MeshConstructor(const MeshConstructor &mesh);
	MeshConstructor(const std::string& fileName);
	
	// returns the pickshape index of the collision. if no collision, return -1
	int MeshConstructor::checkCollision(BVH* other,  glm::mat4 self_trans,
																 glm::mat4 self_rot, 
																 glm::mat4 other_trans,
																 glm::mat4 other_rot );
	void Bind() {vao.Bind();}
	void Unbind() {vao.Unbind();}
	inline unsigned int GetIndicesNum(){return indicesNum;}
	inline bool Is2D() {return is2D;}
	~MeshConstructor(void);

};

