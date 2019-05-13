#include "game.h"
#include <iostream>
#include <list>
#include <math.h>

#define BOUNDING_BOX_INDEX 2

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}



Game::Game():Scene(){curve = 0;}

Game::Game(glm::vec3 position,float angle,float hwRelation,float near, float far) : Scene(position,angle,hwRelation,near,far)
{ 
	curve = new Bezier1D();
}

void Game::addShape(int type,int parent,unsigned int mode)
{
		chainParents.push_back(parent);
		if(type!=BezierLine && type!=BezierSurface)
			shapes.push_back(new Shape(type,mode));
		else
		{
			if(type == BezierLine)
				shapes.push_back(new Shape(curve,30,30,false,mode));
			else
				shapes.push_back(new Shape(curve,30,30,true,mode));
		}
}

void Game::Rec_Create_Bounding_Box(std::vector<TransStruct>* data,Node* root, int parent, int level, bool is_left)
{
	this->addShapeCopy(BOUNDING_BOX_INDEX, -1, LINE_LOOP);

	TransStruct current_data;
	current_data.level = level;
	current_data.picked_shape= shapes.size() - 1;
	current_data.data = root->data;
	data->push_back(current_data);
	shapes[current_data.picked_shape]->Hide();
	

	pickedShape = shapes.size() - 1;
	if (level ==0)
	{
		shapes[pickedShape]->Unhide();
	}

	if (level % 3 == 0) {
		shapeTransformation(xScale, 1.0f / float(pow(2, level)));
		shapeTransformation(xLocalTranslate, float(root->data.x));
	}
	else if (level % 3 == 1) {
		shapeTransformation(yScale, 1.0f / float(pow(2, level)));
		shapeTransformation(yLocalTranslate, float(root->data.y));
	}
	else if (level % 3 == 2) {
		shapeTransformation(zScale, 1.0f / float(pow(2, level)));
		shapeTransformation(zLocalTranslate, float(root->data.z));

	}
	//if (!is_left)
	//{
	//	shapeTransformation(xLocalTranslate, float(root->data.x));
	//	shapeTransformation(yLocalTranslate, float(root->data.y));
	//	shapeTransformation(zLocalTranslate, float(root->data.z));
	//}
	chainParents[pickedShape] = parent;


	if (root->left != nullptr)
	{
		Rec_Create_Bounding_Box(data, root->left, pickedShape, level + 1,true);
	}
	if (root->right != nullptr)
	{
		Rec_Create_Bounding_Box(data,root->right, pickedShape, level + 1, false);
	}
}

void Game::CreateBoundingBoxes(BVH * box_tree, int parent, int level)
{
	this->addShapeCopy(BOUNDING_BOX_INDEX, -1, LINE_LOOP);
	pickedShape = shapes.size() - 1;
	box_tree->box->setPickShape(pickedShape);
	box_tree->level = level;
	shapes[pickedShape]->Hide();

	shapeTransformation(xLocalTranslate, box_tree->box->static_center.x);
	shapeTransformation(yLocalTranslate, box_tree->box->static_center.y);
	shapeTransformation(zLocalTranslate, box_tree->box->static_center.z);


	shapeTransformation(xScale, box_tree->box->size.x);
	shapeTransformation(yScale, box_tree->box->size.y);
	shapeTransformation(zScale, box_tree->box->size.z);

	chainParents[pickedShape] = parent;


	if (level ==0 )
	{
		shapes[pickedShape]->Unhide();
	}
	if (box_tree->left != nullptr)
	{
		CreateBoundingBoxes(box_tree->left, parent, level+1);
	}
	if (box_tree->right != nullptr)
	{
		CreateBoundingBoxes(box_tree->right, parent, level+1);
	}
}


void Game::Init()
{
	std::vector<TransStruct> data;
	addShape(Axis,-1,LINES);
	//addShape(Octahedron,-1,TRIANGLES);
	addShapeFromFile("../res/objs/ball.obj",-1,TRIANGLES);
	addShape(Cube,1,LINE_LOOP);
	shapes[BOUNDING_BOX_INDEX]->Hide();
	addShapeCopy(1, -1, TRIANGLES);

	//addShapeCopy(3,2,LINE_LOOP);+		vao	{m_RendererID=4 }	VertexArray


	for (int i=0; i<this->shapes.size(); i++)
	{
		Shape *shape = shapes[i];
		if (shape->mode == TRIANGLES)
		{
			BVH *bvh = &shape->mesh->bvh;
			
			CreateBoundingBoxes(bvh, i, 0);


		}
	}
	/*int axis = 0;
	for (auto& trans : data)
	{
		
		pickedShape = trans.picked_shape;
		if (trans.level == 1)
		{
			shapes[pickedShape]->Unhide();
		}

		if (axis==0)
			shapeTransformation(xScale, 1.0f / float(pow(2,trans.level)));
		else if(axis==1)
			shapeTransformation(yScale, 1.0f / float(pow(2, trans.level)));
		else if(axis==2)
			shapeTransformation(zScale, 1.0f / float(pow(2, trans.level)));

		shapeTransformation(xLocalTranslate, trans.data.x);
		shapeTransformation(yLocalTranslate, trans.data.y);
		shapeTransformation(zLocalTranslate, trans.data.z);
		axis++;
		axis = axis % 3;
	}*/

	//translate all scene away from camera
	myTranslate(glm::vec3(0,0,-90),0);

	pickedShape = 0;

	shapeTransformation(yScale,10);
	shapeTransformation(xScale,10);
	shapeTransformation(zScale,10);

	pickedShape = 3;

	shapeTransformation(yGlobalTranslate, 50);
	//pickedShape = 1;

	//shapeTransformation(xScale, 0.1);
	//shapeTransformation(yScale, 0.1);
	//shapeTransformation(zScale, 0.1);
	//pickedShape = 3;

	//shapeTransformation(xScale, 0.1);
	//shapeTransformation(yScale, 0.1);
	//shapeTransformation(zScale, 0.1);

	ReadPixel();
	pickedShape = -1;
	Activate();
}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Normal,Shader *s)
{
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal", Normal);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 1.0f);
	s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);	
	collisionDetection();
}

void Game::WhenRotate()
{
	//if(pickedShape>=0)
	//	printMat(GetShapeTransformation());
}

void Game::WhenTranslate()
{
	if(pickedShape>=0)
	{
		glm::vec4 pos = GetShapeTransformation()*glm::vec4(0,0,0,1);
	//	std::cout<<"( "<<pos.x<<", "<<pos.y<<", "<<pos.z<<")"<<std::endl;
	}
}

void Game::Motion()
{
	if(isActive)
	{
		int p = pickedShape;
		pickedShape = 3;
		//shapeTransformation(zLocalRotate,0.45);
		pickedShape = p;
	}
}

Game::~Game(void)
{
	delete curve;
}
