#define GLEW_STATIC
#include <GL\glew.h>
#include <queue>
#include "MeshConstructor.h"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "bezier2D.h"
#include "obj_loader.h"


MeshConstructor::MeshConstructor(const int type)
{
	

	switch (type)
	{
	case Axis:	
		InitLine(AxisGenerator());
		break;
	case Cube:
		 InitMesh(CubeTriangles());
		 break;
	case Octahedron:
		 InitMesh(OctahedronGenerator());
		 break;
	case Tethrahedron:
		 InitMesh(TethrahedronGenerator());
		 break;
	default:
		break;
	}

	
}

MeshConstructor::MeshConstructor(const std::string& fileName)
{
	InitMesh(OBJModel(fileName).ToIndexedModel());
}

int MeshConstructor::checkCollision(MeshConstructor* other, glm::mat4 self_trans,
															glm::mat4 self_rot,
															glm::mat4 other_trans,
															glm::mat4 other_rot)


{
	std::queue<BVH*> self_queue;
	BVH* self_curr=&this->bvh;
	self_queue.push(self_curr);
	while (!self_queue.empty()) {
		self_curr = self_queue.front();
		self_queue.pop();
		other->bvh.box->updateDynamic(other_rot, other_trans);
		this->bvh.box->updateDynamic(self_rot, self_trans);
		if (self_curr->box->checkCollision(other->bvh.box)&&
			(other->checkCollision(this, other_trans, other_rot, self_trans,self_rot)!=-1)) 

		{
			if (self_curr->left != nullptr && self_curr->right != nullptr) {
				self_queue.push(self_curr->left);
				self_queue.push(self_curr->right);
			}
			else if (self_curr->left != nullptr)
				self_queue.push(self_curr->left);
			else if (self_curr->right != nullptr)
				self_queue.push(self_curr->right);
			else
				return self_curr->box->pickShape;
			
		}
		
	}

	return -1;
}

MeshConstructor::MeshConstructor(Bezier1D *curve,bool isSurface,unsigned int resT,unsigned int resS)
{
	//if(isSurface)
	//{
	//	Bezier2D surface(*curve,glm::vec3(0,0,1),4);
	//	InitMesh(surface.GetSurface(resT,resS));		
	//}
	//else
	//{
	//	InitLine( curve->GetLine(resT));
	//}
}

MeshConstructor::MeshConstructor(const MeshConstructor &mesh)
{
	indicesNum = mesh.indicesNum;
	if(mesh.is2D)
		CopyMesh(mesh);
	else
		CopyLine(mesh);
}

MeshConstructor::~MeshConstructor(void)
{
	if(ib)
		delete ib;
	for (unsigned int i = 0; i < vbs.size(); i++)
	{
		if(vbs[i])
			delete vbs[i];
	}
}

void MeshConstructor::make_tree(std::vector<glm::vec3> positions)
{
	std::list<Node::vecType> point_list;
	for (auto i = 0; i < positions.size(); i++)
	{

		point_list.push_back(Node::vecType(positions[i].x, positions[i].y, positions[i].z, 1.0f));
	}
	tree.makeTree(point_list);
	//tree.printTree(tree.getRoot());

	// calc center of the base bounding box
	glm::vec3 center = glm::vec3(0);
	for (auto& position : positions)
		center += position;
	center = 1.0f / positions.size() * center;

	// calc size of the base bounding box
	glm::vec3 size = glm::vec3(0);
	for (auto& position : positions)
		size = glm::max(size,glm::abs(position-center));

	BoundingBox *base = new BoundingBox(center, size);

	this->bvh.box = base;
	this->bvh.left= make_BVH(*this->tree.getRoot(), *base, true, 0);
	this->bvh.right=make_BVH(*this->tree.getRoot(), *base, false, 0);
}
BVH* MeshConstructor::make_BVH (Node node, BoundingBox daddy, bool is_left, int level)
{
	int axis = level % 3;
	glm::vec3 center = daddy.center;
	glm::vec3 size = daddy.size;
	BVH *bvh = new BVH();

	
	if (is_left)
	{
		center[axis] = ((daddy.center[axis] + daddy.size[axis]) + node.data[axis])/2.0f;
		size[axis] = abs((daddy.center[axis] + daddy.size[axis]) - center[axis]);
	}
	else
	{
		center[axis] = ((daddy.center[axis] - daddy.size[axis]) + node.data[axis]) / 2.0f;
		size[axis] = abs((daddy.center[axis] - daddy.size[axis]) - center[axis]);
	}

	bvh->box = new BoundingBox(center, size) ;
	if (node.left != nullptr)
	{
		bvh->left=make_BVH(*(node.left), *bvh->box, true, level + 1);
	}
	if (node.right != nullptr)
	{
		bvh->right= make_BVH(*(node.right), *bvh->box, false, level + 1);
	}
	return bvh;
	

}
void MeshConstructor::InitLine(IndexedModel &model){
	
	int verticesNum = model.positions.size();
	indicesNum = model.indices.size();
	
	vao.Bind();

	for (int i = 0; i < 2; i++)
	{
		vbs.push_back(new VertexBuffer(model.GetData(i),verticesNum*sizeof(model.positions[0])));	
		vao.AddBuffer(*vbs.back(),i,3,GL_FLOAT);
	}
	
	ib = new IndexBuffer((unsigned int*)model.GetData(4),indicesNum);
	
	vao.Unbind();
	is2D = false;
	
}

void MeshConstructor::InitMesh( IndexedModel &model){
	make_tree(model.positions);
	int verticesNum = model.positions.size();
	indicesNum = model.indices.size();
	
	vao.Bind();

	for (int i = 0; i < 3; i++)
	{
		vbs.push_back(new VertexBuffer(model.GetData(i),verticesNum*sizeof(model.positions[0])));	
		vao.AddBuffer(*vbs.back(),i,3,GL_FLOAT);
	}
	vbs.push_back(new VertexBuffer(model.GetData(3),verticesNum*sizeof(model.texCoords[0])));
	vao.AddBuffer(*vbs.back(),vbs.size()-1,2,GL_FLOAT);
	
	ib = new IndexBuffer((unsigned int*)model.GetData(4),indicesNum);
	
	vao.Unbind();
	is2D = true;
	
}

void MeshConstructor::CopyLine(const MeshConstructor &mesh){
	
	vao.Bind();

	for (int i = 0; i < 2; i++)
	{
		vbs.push_back(new VertexBuffer(*(mesh.vbs[i])));	
		vao.AddBuffer(*vbs.back(),i,3,GL_FLOAT);
	}
	
	ib = new IndexBuffer(*mesh.ib);
	
	vao.Unbind();

	is2D = false;
	
}

void MeshConstructor::CopyMesh(const MeshConstructor &mesh){
	tree = *new Kdtree(mesh.tree);
	vao.Bind();

	for (int i = 0; i < 4; i++)
	{
		vbs.push_back(new VertexBuffer(*(mesh.vbs[i])));	
		vao.AddBuffer(*vbs.back(),i,3,GL_FLOAT);
	}
	
	
	ib = new IndexBuffer(*mesh.ib);
	//ib = mesh.ib;
	vao.Unbind();

	is2D = true;
	
}

BVH::BVH()
{
	this->box = new BoundingBox(glm::vec3(0), glm::vec3(0));
	this->left = nullptr;
	this->right = nullptr;

}
