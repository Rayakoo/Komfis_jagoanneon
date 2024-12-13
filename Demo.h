#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2, texture3 , VBO3, VAO3, EBO3 , 
		texture4, VBO4 ,VAO4, EBO4 , texture5, VBO5, VAO5, EBO5, texture6, VBO6, VAO6, EBO6, texture7, VBO7, VAO7, EBO7, texture8, VBO8,VAO8,EBO8, texture9, VBO9, VAO9, EBO9,
		texture10, VBO10, VAO10, EBO10, texture11, VBO11, VAO11, EBO11, texture12, VBO12, VAO12, EBO12, texture13, VBO13, VAO13, EBO13,
		texture14, VBO14, VAO14, EBO14, texture15, VBO15, VAO15, EBO15;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildTexturedCube();
	void BuildTexturedPlane();
	void BuildTexturedTiang();
	void BuildTexturedTali();
	void BuildTexturedTribun();
	void BuildTexturedBanner();
	void BuildTexturedManusia();
	void DrawColoredTiang();
	void DrawTexturedCube();
	void DrawColoredPlane();
	void BuildTextureLantai();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void DrawColoredLantai();
	void DrawColoredTali();
	void DrawTexturedTribun();
	void DrawTexturedBanner();
	void DrawTexturedManusia();
	void BuildTexturedHitam();
	void DrawTexturedHitam();
	void BuildTexturedJuara();
	void DrawTexturedJuara();
	void BuildTexturedKepala();
	void DrawTexturedKepala();
	void BuildTexturedKaki();
	void DrawTexturedKaki();
	void BuildTexturedSabuk();
	void DrawTexturedSabuk();
	void BuildTexturedTiangSamsak();
	void DrawTexturedTiangSamsak();
	void InitCamera();
};

