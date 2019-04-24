#pragma once
#include "scene.h"
#include "bezier1D.h"

class Game : public Scene
{
	struct TransStruct
	{
		int level;
		glm::vec4 data;
		glm::vec3 translate;
		glm::vec3 resize;
		int picked_shape;

	};
	Bezier1D *curve;
	void Game::Rec_Create_Bounding_Box(std::vector<TransStruct>* data, Node* root, int parent, int level, bool is_left);
	void Game::CreateBoundingBoxes(BVH box_tree, int parent, int level);
public:
	Game(void);
	Game(glm::vec3 position,float angle,float hwRelation,float near, float far);
	void Init();
	void addShape(int type,int parent,unsigned int mode);
//	void Update( glm::mat4 MVP ,glm::mat4 *jointTransforms,const int length,const int  shaderIndx);
	void Update(const glm::mat4 &MVP,const glm::mat4 &Normal,Shader *s);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	~Game(void);
};

