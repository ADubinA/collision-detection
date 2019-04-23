#include "Mesh.h"

void IndexedModel::CalcNormals()
{
    for(unsigned int i = 0; i < indices.size(); i += 3)
    {
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        glm::vec3 v1 = positions[i1] - positions[i0];
        glm::vec3 v2 = positions[i2] - positions[i0];
        
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
            
        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }
    
    for(unsigned int i = 0; i < positions.size(); i++)
	{
        normals[i] = glm::normalize(normals[i]);
		colors[i] = (glm::vec3(1,1,1) + normals[i])/2.0f;
	}
}


IndexedModel CubeTriangles()
{
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1))
	};



	unsigned int indices[] =	{0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };

	    IndexedModel model;
	
	for(unsigned int i = 0; i < 24; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.colors.push_back(*vertices[i].GetColor());
		model.normals.push_back(*vertices[i].GetNormal());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}
	for(unsigned int i = 0; i < 36; i++)
        model.indices.push_back(indices[i]);
	
	return model;
}

IndexedModel AxisGenerator()
{
	IndexedModel model;

	LineVertex axisVertices[] = 
	{
		LineVertex(glm::vec3(1,0,0),glm::vec3(1,0,0)),
		LineVertex(glm::vec3(-1,0,0),glm::vec3(1,0,0)),
		LineVertex(glm::vec3(0,1,0),glm::vec3(0,1,0)),
		LineVertex(glm::vec3(0,-1,0),glm::vec3(0,1,0)),
		LineVertex(glm::vec3(0,0,1),glm::vec3(0,0,1)),
		LineVertex(glm::vec3(0,0,-1),glm::vec3(0,0,1)),
	};


	 unsigned int axisIndices[] = 
	{
		0,1,
		2,3,
		4,5
	};

	 for(unsigned int i = 0; i < 6; i++)
	{
		model.positions.push_back(*axisVertices[i].GetPos());
		model.colors.push_back(*axisVertices[i].GetColor());

	}
	for(unsigned int i = 0; i < 6; i++)
        model.indices.push_back(axisIndices[i]);
	
	return model;
}

IndexedModel TethrahedronGenerator()
{

	Vertex vertices[] =
	{
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(-1, -1, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(-1, -1, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 1), glm::vec3(-1, -1, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(1, -1, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(1, -1, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 1), glm::vec3(1, -1, 1),glm::vec3(0, 1, 1)),

		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(1, 1, -1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(1, 1), glm::vec3(1, 1, -1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(1, 1, -1),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),

	};



	unsigned int indices[] =	{0, 1, 2,
							     3, 4, 5,
								 6,7,8,
								 9,10,11
						
	                          };

	    IndexedModel model;
	
	for(unsigned int i = 0; i < 12; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.colors.push_back(*vertices[i].GetColor());
		model.normals.push_back(*vertices[i].GetNormal());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}
	for(unsigned int i = 0; i < 12; i++)
        model.indices.push_back(indices[i]);
	
	return model;
}

IndexedModel OctahedronGenerator()
{
	Vertex vertices[] =
	{
		Vertex(glm::vec3( 0, 0,-1), glm::vec2(1, 0), glm::vec3(1, 1, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(0, 1, 0), glm::vec2(0, 0), glm::vec3(1, 1, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(0, 1), glm::vec3(1, 1, -1),glm::vec3(0, 0, 1)),
		
		Vertex(glm::vec3(0, 0, -1), glm::vec2(1, 0), glm::vec3(1, -1, -1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(0,-1, 0), glm::vec2(0, 0), glm::vec3(1, -1, -1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(0, 1), glm::vec3(1, -1, -1),glm::vec3(0, 1, 1)),

		Vertex(glm::vec3(0, 0, -1), glm::vec2(0, 1), glm::vec3(-1, 1, -1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(0, 1, 0), glm::vec2(1, 1), glm::vec3(-1, 1, -1),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 0, 0), glm::vec2(1, 0), glm::vec3(-1, 1, -1),glm::vec3(0, 1, 0)),
		
		Vertex(glm::vec3(0, 0, -1), glm::vec2(0, 1), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(0, -1, 0), glm::vec2(1, 1), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, 0, 0), glm::vec2(1, 0), glm::vec3(-1, -1, -1),glm::vec3(1, 1, 0)),		

		Vertex(glm::vec3(0, 0, 1), glm::vec2(1, 1), glm::vec3(-1, -1, 1),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(0, -1, 0), glm::vec2(1, 0), glm::vec3(-1, -1, 1),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 0, 0), glm::vec2(0, 0), glm::vec3(-1, -1, 1),glm::vec3(1, 0, 0)),
		

		Vertex(glm::vec3(0, 0, 1), glm::vec2(1, 1), glm::vec3(1, -1, 1),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(0, -1, 0), glm::vec2(1, 0), glm::vec3(1, -1, 1),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(0, 0), glm::vec3(1, -1, 1),glm::vec3(1, 0, 1)),

		Vertex(glm::vec3(0, 0, 1), glm::vec2(1, 1), glm::vec3(1, 1, 1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(0,1, 0), glm::vec2(1, 0), glm::vec3(1, 1, 1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(1, 0, 0), glm::vec2(0, 0), glm::vec3(1, 1, 1),glm::vec3(0, 0, 0)),

		Vertex(glm::vec3(0, 0, 1), glm::vec2(1, 1), glm::vec3(-1, 1, 1),glm::vec3(0.7f, 0.7f, 0.7f)),
		Vertex(glm::vec3(0, 1, 0), glm::vec2(1, 0), glm::vec3(-1, 1, 1),glm::vec3(0.7f, 0.7f, 0.7f)),
		Vertex(glm::vec3(-1, 0, 0), glm::vec2(0, 0), glm::vec3(-1, 1, 1),glm::vec3(0.7f, 0.7f, 0.7f)),
		
	};



	unsigned int indices[] =	{0, 1, 2,
							     3, 4, 5,
								 6,7,8,
								 9,10,11,
								 12,13,14, 
								 15,16,17,
								 18,19,20,
								 21,22,23,
	                          };

	    IndexedModel model;
	
	for(unsigned int i = 0; i < 24; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.colors.push_back(*vertices[i].GetColor());
		model.normals.push_back(*vertices[i].GetNormal());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}
	for(unsigned int i = 0; i < 24; i++)
        model.indices.push_back(indices[i]);
	
	return model;
}

BoundingBox::BoundingBox(glm::vec3 center, glm::vec3 size)
{
	this->center = center;
	this->size = size;
	this->xInit = glm::vec3(1, 0, 0);      // x axis of the box. default value (1,0,0)		
	this->yInit = glm::vec3(0, 1, 0);      // y axis of the box. default value (0,1,0)		
	this->zInit = glm::vec3(0, 0, 1);	   // z axis of the box. default value (0,0,1)
}

bool BoundingBox::checkCollision(BoundingBox other)
{
	float R0, R1, R;
	glm::vec3 D = this->center - other.center;
	glm::mat3x3 c = glm::mat3x3(
		glm::vec3(glm::dot(this->xInit, other.xInit), glm::dot(this->xInit, other.yInit), glm::dot(this->xInit, other.zInit)),
		glm::vec3(glm::dot(this->yInit, other.xInit), glm::dot(this->yInit, other.yInit), glm::dot(this->yInit, other.zInit)),
		glm::vec3(glm::dot(this->zInit, other.xInit), glm::dot(this->zInit, other.yInit), glm::dot(this->zInit, other.zInit))
								);

	//test A0
	R0 = this->size.x;
	R1 = other.size.x*glm::abs(c[0][0]) +
		 other.size.y*glm::abs(c[0][1]) + 
		 other.size.z*glm::abs(c[0][2]);
	R= glm::abs(glm::dot(xInit, D));
	if (R > R0 + R1)
		return false;
	//test A1
	R0 = this->size.y;
	R1 = other.size.x*glm::abs(c[1][0]) +
		 other.size.y*glm::abs(c[1][1]) +
		 other.size.z*glm::abs(c[1][2]);
	R = glm::abs(glm::dot(yInit, D));
	if (R > R0 + R1)
		return false;
	//test A2
	R0 = this->size.z;
	R1 = other.size.x*glm::abs(c[2][0]) +
		 other.size.y*glm::abs(c[2][1]) +
	     other.size.z*glm::abs(c[2][2]);
	R = glm::abs(glm::dot(zInit, D));
	if (R > R0 + R1)
		return false;
	//test B0
	R1 = other.size.x;
	R0 = this->size.x*glm::abs(c[0][0]) +
		 this->size.y*glm::abs(c[1][0]) +
		 this->size.z*glm::abs(c[2][0]);
	R = glm::abs(glm::dot(other.xInit, D));
	if (R > R0 + R1)
		return false; 
	//test B1
	R1 = other.size.y;
	R0 = this->size.x*glm::abs(c[0][1]) +
		 this->size.y*glm::abs(c[1][1]) +
		 this->size.z*glm::abs(c[2][1]);
	R = glm::abs(glm::dot(other.yInit, D));
	if (R > R0 + R1)
		return false; 
	//test B1
	R1 = other.size.z;
	R0 = this->size.x*glm::abs(c[0][2]) +
		 this->size.y*glm::abs(c[1][2]) +
		 this->size.z*glm::abs(c[2][2]);
	R = glm::abs(glm::dot(other.zInit, D));
	if (R > R0 + R1)
		return false;
	//test A0xB0
	R0 = this->size.y*glm::abs(c[2][0]) +
		 this->size.z*glm::abs(c[1][0]);
	R1 = other.size.y*glm::abs(c[0][2]) +
		 other.size.z*glm::abs(c[0][1]);
	R = glm::abs(c[1][0]*glm::dot(zInit, D)-c[2][0]*glm::dot(yInit, D));
	if (R > R0 + R1)
		return false;
	//test A0xB1
	R0 = this->size.y*glm::abs(c[2][1]) +
		this->size.z*glm::abs(c[1][1]);
	R1 = other.size.x*glm::abs(c[0][2]) +
		other.size.z*glm::abs(c[0][0]);
	R = glm::abs(c[1][1] * glm::dot(zInit, D) - c[2][1] * glm::dot(yInit, D));
	if (R > R0 + R1)
		return false;
	//test A0xB2
	R0 = this->size.y*glm::abs(c[2][2]) +
		this->size.z*glm::abs(c[1][2]);
	R1 = other.size.x*glm::abs(c[0][1]) +
		other.size.y*glm::abs(c[0][0]);
	R = glm::abs(c[1][2] * glm::dot(zInit, D) - c[2][2] * glm::dot(yInit, D));
	if (R > R0 + R1)
		return false;
	//test A1xB0
	R0 = this->size.x*glm::abs(c[2][0]) +
		this->size.z*glm::abs(c[0][0]);
	R1 = other.size.y*glm::abs(c[1][2]) +
		other.size.z*glm::abs(c[1][1]);
	R = glm::abs(c[2][0] * glm::dot(xInit, D) - c[0][0] * glm::dot(zInit, D));
	if (R > R0 + R1)
		return false;
	//test A1xB1
	R0 = this->size.x*glm::abs(c[2][1]) +
		this->size.z*glm::abs(c[0][1]);
	R1 = other.size.x*glm::abs(c[1][2]) +
		other.size.z*glm::abs(c[1][0]);
	R = glm::abs(c[2][1] * glm::dot(xInit, D) - c[0][1] * glm::dot(zInit, D));
	if (R > R0 + R1)
		return false;
	//test A1xB2
	R0 = this->size.x*glm::abs(c[2][2]) +
		this->size.z*glm::abs(c[0][2]);
	R1 = other.size.x*glm::abs(c[1][1]) +
		other.size.y*glm::abs(c[1][0]);
	R = glm::abs(c[2][2] * glm::dot(xInit, D) - c[0][2] * glm::dot(zInit, D));
	if (R > R0 + R1)
		return false;
	//test A2xB0
	R0 = this->size.x*glm::abs(c[1][0]) +
		this->size.y*glm::abs(c[0][0]);
	R1 = other.size.y*glm::abs(c[2][2]) +
		other.size.z*glm::abs(c[2][1]);
	R = glm::abs(c[0][0] * glm::dot(yInit, D) - c[1][0] * glm::dot(xInit, D));
	if (R > R0 + R1)
		return false;
	//test A2xB1
	R0 = this->size.x*glm::abs(c[1][1]) +
		this->size.y*glm::abs(c[0][1]);
	R1 = other.size.x*glm::abs(c[2][2]) +
		other.size.z*glm::abs(c[2][0]);
	R = glm::abs(c[0][1] * glm::dot(yInit, D) - c[1][1] * glm::dot(xInit, D));
	if (R > R0 + R1)
		return false;
	//test A2xB2
	R0 = this->size.x*glm::abs(c[1][2]) +
		this->size.y*glm::abs(c[0][2]);
	R1 = other.size.x*glm::abs(c[2][1]) +
		other.size.y*glm::abs(c[2][0]);
	R = glm::abs(c[0][2] * glm::dot(yInit, D) - c[1][2] * glm::dot(xInit, D));
	if (R > R0 + R1)
		return false;
}
