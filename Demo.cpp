#include "Demo.h"



Demo::Demo() {

}


Demo::~Demo() {
}



void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildTexturedCube();

	BuildTextureLantai();

	BuildTexturedPlane();

	BuildTexturedTiang();

	BuildTexturedTali();

	BuildTexturedTribun();

	BuildTexturedBanner();

	BuildTexturedManusia();

	BuildTexturedTiangSamsak();

	BuildTexturedHitam();

	BuildTexturedJuara();

	BuildTexturedKepala();

	BuildTexturedSabuk();

	BuildTexturedKaki();


	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);


	

}

void Demo::Update(double deltaTime) {
	
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	DrawTexturedCube();

	DrawColoredPlane();

	DrawColoredLantai();

	DrawColoredTiang();

	DrawColoredTali();

	DrawTexturedTribun();

	DrawTexturedBanner();

	DrawTexturedManusia();

	DrawTexturedTiangSamsak();

	DrawTexturedHitam();

	DrawTexturedJuara();

	DrawTexturedKepala();

	DrawTexturedSabuk();

	DrawTexturedKaki();

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildTexturedCube() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("download (1).jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-10, -0.5, 10, 0, 0,  // 0
		10, -0.5, 10, 1, 0,   // 1
		10,  2, 10, 1, 1,   // 2
		-10,  2, 10, 0, 1,  // 3

		// right
		10,  2,  10, 0, 0,  // 4
		10,  2, -10, 1, 0,  // 5
		10, -0.5, -10, 1, 1,  // 6
		10, -0.5,  10, 0, 1,  // 7

		// back
		-10, -0.5, -10, 0, 0, // 8 
		10,  -0.5, -10, 1, 0, // 9
		10,   2, -10, 1, 1, // 10
		-10,  2, -10, 0, 1, // 11

		// left
		-10, -0.5, -10, 0, 0, // 12
		-10, -0.5,  10, 1, 0, // 13
		-10,  2,  10, 1, 1, // 14
		-10,  2, -10, 0, 1, // 15

		// upper
		10, 2,  10, 0, 0,   // 16
		-10, 2,  10, 1, 0,  // 17
		-10, 2, -10, 1, 1,  // 18
		10, 2, -10, 0, 1,   // 19

		// bottom
		-10, -0.5, -10, 0, 0, // 20
		10, -0.5, -10, 1, 0,  // 21
		10, -0.5,  10, 1, 1,  // 22
		-10, -0.5,  10, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedCube()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("tembok.jpeg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords

		// front
		-25, 25, 25, 0, 0,  // 0
		25, 25, 25, 1, 0,   // 1
		25,  -0.5, 25, 1, 1,   // 2
		-25,  -0.5, 25, 0, 1,  // 3

		// right
		25,  25,  25, 0, 0,  // 4
		25,  25, -25, 1, 0,  // 5
		25, -0.5, -25, 1, 1,  // 6
		25, -0.5,  25, 0, 1,  // 7

		// back
		-25, 25, -25, 0, 0,  // 8
		25, 25, -25, 1, 0,   // 9
		25,  -0.5, -25, 1, 1,   // 10
		-25,  -0.5, -25, 0, 1, // 11

		// left
		-25.0, 25.0, 25, 0, 0, // 12
		-25.0, 25.0,  -25, 1, 0, // 13
		-25.0, -0.5,  -25, 1, 1, // 14
		-25.0,  -0.5, 25, 0, 1, // 15


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 ,
						 4,  6,  5, 4, 7, 6,
						 8, 10, 9, 8, 11, 10,
						 12, 14, 13, 12, 15,14};

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}



void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTextureLantai()
{
	// Load and create a texture 
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("carpet.jpeg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-25.0, -0.5, -25.0,  0,  0, //0
		 25.0, -0.5, -25.0, 50,  0, //1
		 25.0, -0.5,  25.0, 50, 50, //2
		-25.0, -0.5,  25.0,  0, 50, //3


		// upper
		-25.0, 25, -25.0,  0,  0, //4
		 25.0, 25, -25.0, 50,  0, //5
		 25.0, 25,  25.0, 50, 50, //6
		-25.0, 25,  25.0,  0, 50,  // 7

	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 ,
						 4,  6,  5, 4, 7, 6, };

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}



void Demo::DrawColoredLantai()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 2);

	glBindVertexArray(VAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedTiang() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("background3.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front tiang 1
		-8.5, 2, 8.5, 0, 0,  // 0
		-8, 2, 8.5, 1, 0,   // 1
		-8,  4.5, 8.5, 1, 1,   // 2
		-8.5,  4.5, 8.5, 0, 1,  // 3

		// right
		-8,  4.5,  8.5, 0, 0,  // 4
		-8,  4.5, 8, 1, 0,  // 5
		-8, 2, 8, 1, 1,  // 6
		-8, 2,  8.5, 0, 1,  // 7

		// back
		-8.5, 2, 8, 0, 0, // 8 
		-8,  2, 8, 1, 0, // 9
		-8,   4.5, 8, 1, 1, // 10
		-8.5,  4.5, 8, 0, 1, // 11

		// left
		-8.5, 2, 8, 0, 0, // 12
		-8.5, 2,  8.5, 1, 0, // 13
		-8.5,  4.5,  8.5, 1, 1, // 14
		-8.5,  4.5, 8, 0, 1, // 15

		// upper
		-8, 4.5, 8.5, 0, 0,   // 16
		-8.5, 4.5,  8.5, 1, 0,  // 17
		-8.5, 4.5, 8, 1, 1,  // 18
		-8, 4.5, 8, 0, 1,   // 19

		// bottom
		-8.5, 2, 8, 0, 0, // 20
		-8, 2, 8, 1, 0,  // 21
		-8, 2,  8.5, 1, 1,  // 22
		-8.5, 2,  8.5, 0, 1, // 23

		// front tiang 2
		-8.5, 2, -8, 0, 0,  // 24
		-8, 2, -8, 1, 0,   // 25
		-8,  4.5, -8, 1, 1,   // 26
		-8.5,  4.5, -8, 0, 1,  // 27

		// right
		-8,  4.5,  -8, 0, 0,  // 28
		-8,  4.5, -8.5, 1, 0,  // 29
		-8, 2, -8.5, 1, 1,  // 30
		-8, 2,  -8, 0, 1,  // 31

		// back
		-8.5, 2, -8.5, 0, 0, // 32 
		-8,  2, -8.5, 1, 0, // 33
		-8,   4.5, -8.5, 1, 1, // 34
		-8.5,  4.5, -8.5, 0, 1, // 35

		// left
		-8.5, 2, -8.5, 0, 0, // 36
		-8.5, 2,  -8, 1, 0, // 37
		-8.5,  4.5,  -8, 1, 1, // 38
		-8.5,  4.5, -8.5, 0, 1, // 39

		// upper
		-8, 4.5, -8, 0, 0,   // 40
		-8.5, 4.5,  -8, 1, 0,  // 41
		-8.5, 4.5, -8.5, 1, 1,  // 42
		-8, 4.5, -8.5, 0, 1,   // 43

		// bottom
		-8.5, 2, -8.5, 0, 0, // 44
		-8, 2, -8.5, 1, 0,  // 45
		-8, 2,  -8, 1, 1,  // 46
		-8.5, 2,  -8, 0, 1, // 47

		// front tiang 3
		8, 2, -8, 0, 0,  // 48
		8.5, 2, -8, 1, 0,   // 49
		8.5,  4.5, -8, 1, 1,   // 50
		8,  4.5, -8, 0, 1,  // 51

		// right
		8.5,  4.5,  -8, 0, 0,  // 52
		8.5,  4.5, -8.5, 1, 0,  // 53
		8.5, 2, -8.5, 1, 1,  // 54
		8.5, 2,  -8, 0, 1,  // 55

		// back
		8, 2, -8.5, 0, 0, // 56 
		8.5,  2, -8.5, 1, 0, // 57
		8.5,   4.5, -8.5, 1, 1, // 58
		8,  4.5, -8.5, 0, 1, // 59

		// left
		8, 2, -8.5, 0, 0, // 60
		8, 2,  -8, 1, 0, // 61
		8,  4.5,  -8, 1, 1, // 62
		8,  4.5, -8.5, 0, 1, // 63

		// upper
		8.5, 4.5, -8, 0, 0,   // 64
		8, 4.5,  -8, 1, 0,  // 65
		8, 4.5, -8.5, 1, 1,  // 66
		8.5, 4.5, -8.5, 0, 1,   // 67

		// bottom
		8, 2, -8.5, 0, 0, // 68
		8.5, 2, -8.5, 1, 0,  // 69
		8.5, 2,  -8, 1, 1,  // 70
		8, 2,  -8, 0, 1, // 71

		// front tiang 4
		8, 2, 8.5, 0, 0,  // 72
		8.5, 2, 8.5, 1, 0,   // 73
		8.5,  4.5, 8.5, 1, 1,   // 74
		8,  4.5, 8.5, 0, 1,  // 75

		// right
		8.5,  4.5,  8.5, 0, 0,  // 52
		8.5,  4.5, 8, 1, 0,  // 53
		8.5, 2, 8, 1, 1,  // 54
		8.5, 2,  8.5, 0, 1,  // 55

		// back
		8, 2, 8, 0, 0, // 56 
		8.5,  2, 8, 1, 0, // 57
		8.5,   4.5, 8, 1, 1, // 58
		8,  4.5, 8, 0, 1, // 59

		// left
		8, 2, 8, 0, 0, // 60
		8, 2,  8.5, 1, 0, // 61
		8,  4.5,  8.5, 1, 1, // 62
		8,  4.5, 8, 0, 1, // 63

		// upper
		8.5, 4.5, 8.5, 0, 0,   // 64
		8, 4.5,  8.5, 1, 0,  // 65
		8, 4.5, 8, 1, 1,  // 66
		8.5, 4.5, 8, 0, 1,   // 67

		// bottom
		8, 2, 8, 0, 0, // 68
		8.5, 2, 8, 1, 0,  // 69
		8.5, 2,  8.5, 1, 1,  // 70
		8, 2,  8.5, 0, 1, // 71

		
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22 ,  // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // bottom
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94       // bottom



	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTiang()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 3);

	glBindVertexArray(VAO4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedTali() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("rectangle 17.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
-8.5, 2.5, 8.5, 0, 0,   // 0
8.5, 2.5, 8.5, 1, 0,    // 1
8.5, 2.75, 8.5, 1, 1,   // 2
-8.5, 2.75, 8.5, 0, 1,  // 3

// right
8.5, 2.75, 8.5, 0, 0,   // 4
8.5, 2.75, -8.5, 1, 0,  // 5
8.5, 2.5, -8.5, 1, 1,   // 6
8.5, 2.5, 8.5, 0, 1,    // 7

// back
-8.5, 2.5, -8.5, 0, 0,  // 8
8.5, 2.5, -8.5, 1, 0,   // 9
8.5, 2.75, -8.5, 1, 1,  // 10
-8.5, 2.75, -8.5, 0, 1, // 11

// left
-8.5, 2.5, -8.5, 0, 0,  // 12
-8.5, 2.5, 8.5, 1, 0,   // 13
-8.5, 2.75, 8.5, 1, 1,  // 14
-8.5, 2.75, -8.5, 0, 1, // 15

// upper
8.5, 2.75, 8.5, 0, 0,   // 16
-8.5, 2.75, 8.5, 1, 0,  // 17
-8.5, 2.75, -8.5, 1, 1, // 18
8.5, 2.75, -8.5, 0, 1,  // 19

// bottom
-8.5, 2.5, -8.5, 0, 0,  // 20
8.5, 2.5, -8.5, 1, 0,   // 21
8.5, 2.5, 8.5, 1, 1,    // 22
-8.5, 2.5, 8.5, 0, 1,   // 23


// front
-8.5, 3.25, 8.5, 0, 0,  // 0
8.5, 3.25, 8.5, 1, 0,   // 1
8.5, 3.5, 8.5, 1, 1,    // 2
-8.5, 3.5, 8.5, 0, 1,   // 3

// right
8.5, 3.5, 8.5, 0, 0,   // 4
8.5, 3.5, -8.5, 1, 0,  // 5
8.5, 3.25, -8.5, 1, 1, // 6
8.5, 3.25, 8.5, 0, 1,  // 7

// back
-8.5, 3.25, -8.5, 0, 0, // 8
8.5, 3.25, -8.5, 1, 0,  // 9
8.5, 3.5, -8.5, 1, 1,   // 10
-8.5, 3.5, -8.5, 0, 1,  // 11

// left
-8.5, 3.25, -8.5, 0, 0, // 12
-8.5, 3.25, 8.5, 1, 0,  // 13
-8.5, 3.5, 8.5, 1, 1,   // 14
-8.5, 3.5, -8.5, 0, 1,  // 15


		// upper
		-8, 4.5, -8, 0, 0,   // 40
		-8.5, 4.5,  -8, 1, 0,  // 41
		-8.5, 4.5, -8.5, 1, 1,  // 42
		-8, 4.5, -8.5, 0, 1,   // 43

		// bottom
		-8.5, 2, -8.5, 0, 0, // 44
		-8, 2, -8.5, 1, 0,  // 45
		-8, 2,  -8, 1, 1,  // 46
		-8.5, 2,  -8, 0, 1, // 47

		// front
-8.5, 4, 8.5, 0, 0,   // 0
8.5, 4, 8.5, 1, 0,    // 1
8.5, 4.25, 8.5, 1, 1, // 2
-8.5, 4.25, 8.5, 0, 1,// 3

// right
8.5, 4.25, 8.5, 0, 0,  // 4
8.5, 4.25, -8.5, 1, 0, // 5
8.5, 4, -8.5, 1, 1,    // 6
8.5, 4, 8.5, 0, 1,     // 7

// back
-8.5, 4, -8.5, 0, 0,   // 8
8.5, 4, -8.5, 1, 0,    // 9
8.5, 4.25, -8.5, 1, 1, // 10
-8.5, 4.25, -8.5, 0, 1,// 11

// left
-8.5, 4, -8.5, 0, 0,   // 12
-8.5, 4, 8.5, 1, 0,    // 13
-8.5, 4.25, 8.5, 1, 1, // 14
-8.5, 4.25, -8.5, 0, 1,// 15


		// upper
		8.5, 4.5, -8, 0, 0,   // 64
		8, 4.5,  -8, 1, 0,  // 65
		8, 4.5, -8.5, 1, 1,  // 66
		8.5, 4.5, -8.5, 0, 1,   // 67

		// bottom
		8, 2, -8.5, 0, 0, // 68
		8.5, 2, -8.5, 1, 0,  // 69
		8.5, 2,  -8, 1, 1,  // 70
		8, 2,  -8, 0, 1, // 71

		// front tiang 4
		8, 2, 8.5, 0, 0,  // 72
		8.5, 2, 8.5, 1, 0,   // 73
		8.5,  4.5, 8.5, 1, 1,   // 74
		8,  4.5, 8.5, 0, 1,  // 75

		// right
		8.5,  4.5,  8.5, 0, 0,  // 52
		8.5,  4.5, 8, 1, 0,  // 53
		8.5, 2, 8, 1, 1,  // 54
		8.5, 2,  8.5, 0, 1,  // 55

		// back
		8, 2, 8, 0, 0, // 56 
		8.5,  2, 8, 1, 0, // 57
		8.5,   4.5, 8, 1, 1, // 58
		8,  4.5, 8, 0, 1, // 59

		// left
		8, 2, 8, 0, 0, // 60
		8, 2,  8.5, 1, 0, // 61
		8,  4.5,  8.5, 1, 1, // 62
		8,  4.5, 8, 0, 1, // 63

		// upper
		8.5, 4.5, 8.5, 0, 0,   // 64
		8, 4.5,  8.5, 1, 0,  // 65
		8, 4.5, 8, 1, 1,  // 66
		8.5, 4.5, 8, 0, 1,   // 67

		// bottom
		8, 2, 8, 0, 0, // 68
		8.5, 2, 8, 1, 0,  // 69
		8.5, 2,  8.5, 1, 1,  // 70
		8, 2,  8.5, 0, 1, // 71

		


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		//16, 18, 17, 16, 19, 18,  // upper
		//20, 22, 21, 20, 23, 22 ,  // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		//40, 42, 41, 40, 43, 42,      // upper
		//44, 46, 45, 44, 47, 46  ,     // bottom
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left



	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredTali()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 4);

	glBindVertexArray(VAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedTiangSamsak() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, & texture9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("download (1).jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front tiang samsak 1
24, -0.5, -20, 0, 0,   // 0
24.25, -0.5, -20, 1, 0,    // 1
24.25, 5.5, -20, 1, 1,   // 2
24, 5.5, -20, 0, 1,  // 3

// right
24.25, 5.5, -20, 0, 0,   // 4
24.25, 5.5, -20.25, 1, 0,  // 5
24.25, -0.5, -20.25, 1, 1,   // 6
24.25, -0.5, -20, 0, 1,    // 7

// back
24, -0.5, -20.25, 0, 0,  // 8
24.25, -0.5, -20.25, 1, 0,   // 9
24.25, 5.5, -20.25, 1, 1,  // 10
24, 5.5, -20.25, 0, 1, // 11

// left
24, -0.5, -20.25, 0, 0,  // 12
24, -0.5, -20, 1, 0,   // 13
24, 5.5, -20, 1, 1,  // 14
24, 5.5, -20.25, 0, 1, // 15

// upper
24.25, 5.5, -20, 0, 0,   // 16
24, 5.5, -20, 1, 0,  // 17
24, 5.5, -20.25, 1, 1, // 18
24.25, 5.5, -20.25, 0, 1,  // 19

// front tiang samsak atas
22.25, 5.25, -20, 0, 0,  // 0
24, 5.25, -20, 1, 0,     // 1
24, 5.5, -20, 1, 1,      // 2
22.25, 5.5, -20, 0, 1,   // 3

// right
24, 5.5, -20, 0, 0,      // 4
24, 5.5, -20.25, 1, 0,   // 5
24, 5.25, -20.25, 1, 1,  // 6
24, 5.25, -20, 0, 1,     // 7

// back
22.25, 5.25, -20.25, 0, 0,  // 8
24, 5.25, -20.25, 1, 0,     // 9
24, 5.5, -20.25, 1, 1,      // 10
22.25, 5.5, -20.25, 0, 1,   // 11

// left
22.25, 5.25, -20.25, 0, 0,  // 12
22.25, 5.25, -20, 1, 0,     // 13
22.25, 5.5, -20, 1, 1,      // 14
22.25, 5.5, -20.25, 0, 1,   // 15

// upper
24, 5.5, -20, 0, 0,         // 16
22.25, 5.5, -20, 1, 0,      // 17
22.25, 5.5, -20.25, 1, 1,   // 18
24, 5.5, -20.25, 0, 1,      // 19

// upper
24, 5.25, -20, 0, 0,         // 16
22.25, 5.25, -20, 1, 0,      // 17
22.25, 5.25, -20.25, 1, 1,   // 18
24, 5.25, -20.25, 0, 1,      // 19

// front tali samsak
22.3, 4.75, -20.10, 0, 0,  // 0
22.4, 4.75, -20.10, 1, 0,  // 1
22.4, 5.25, -20.10, 1, 1,  // 2
22.3, 5.25, -20.10, 0, 1,  // 3

// right
22.4, 5.25, -20.10, 0, 0,  // 4
22.4, 5.25, -20.20, 1, 0,  // 5
22.4, 4.75, -20.20, 1, 1,  // 6
22.4, 4.75, -20.10, 0, 1,  // 7

// back
22.3, 4.75, -20.20, 0, 0,  // 8
22.4, 4.75, -20.20, 1, 0,  // 9
22.4, 5.25, -20.20, 1, 1,  // 10
22.3, 5.25, -20.20, 0, 1,  // 11

// left
22.3, 4.75, -20.20, 0, 0,  // 12
22.3, 4.75, -20.10, 1, 0,  // 13
22.3, 5.25, -20.10, 1, 1,  // 14
22.3, 5.25, -20.20, 0, 1,  // 15

// upper
22.4, 5.25, -20.10, 0, 0,  // 16
22.3, 5.25, -20.10, 1, 0,  // 17
22.3, 5.25, -20.20, 1, 1,  // 18
22.4, 5.25, -20.20, 0, 1,  // 19

// front tiang samsak 2
-24, -0.5, -20, 0, 0,      // 0
-24.25, -0.5, -20, 1, 0,   // 1
-24.25, 5.5, -20, 1, 1,    // 2
-24, 5.5, -20, 0, 1,       // 3

// right
-24.25, 5.5, -20, 0, 0,    // 4
-24.25, 5.5, -20.25, 1, 0, // 5
-24.25, -0.5, -20.25, 1, 1,// 6
-24.25, -0.5, -20, 0, 1,   // 7

// back
-24, -0.5, -20.25, 0, 0,   // 8
-24.25, -0.5, -20.25, 1, 0,// 9
-24.25, 5.5, -20.25, 1, 1, // 10
-24, 5.5, -20.25, 0, 1,    // 11

// left
-24, -0.5, -20.25, 0, 0,   // 12
-24, -0.5, -20, 1, 0,      // 13
-24, 5.5, -20, 1, 1,       // 14
-24, 5.5, -20.25, 0, 1,    // 15

// upper
-24.25, 5.5, -20, 0, 0,    // 16
-24, 5.5, -20, 1, 0,       // 17
-24, 5.5, -20.25, 1, 1,    // 18
-24.25, 5.5, -20.25, 0, 1, // 19

// front tiang samsak atas
-22.25, 5.25, -20, 0, 0,   // 0
-24, 5.25, -20, 1, 0,      // 1
-24, 5.5, -20, 1, 1,       // 2
-22.25, 5.5, -20, 0, 1,    // 3

// right
-24, 5.5, -20, 0, 0,       // 4
-24, 5.5, -20.25, 1, 0,    // 5
-24, 5.25, -20.25, 1, 1,   // 6
-24, 5.25, -20, 0, 1,      // 7

// back
-22.25, 5.25, -20.25, 0, 0,// 8
-24, 5.25, -20.25, 1, 0,   // 9
-24, 5.5, -20.25, 1, 1,    // 10
-22.25, 5.5, -20.25, 0, 1, // 11

// left
-22.25, 5.25, -20.25, 0, 0,// 12
-22.25, 5.25, -20, 1, 0,   // 13
-22.25, 5.5, -20, 1, 1,    // 14
-22.25, 5.5, -20.25, 0, 1, // 15

// upper
-24, 5.5, -20, 0, 0,       // 16
-22.25, 5.5, -20, 1, 0,    // 17
-22.25, 5.5, -20.25, 1, 1, // 18
-24, 5.5, -20.25, 0, 1,    // 19

// upper
-24, 5.25, -20, 0, 0,      // 16
-22.25, 5.25, -20, 1, 0,   // 17
-22.25, 5.25, -20.25, 1, 1,// 18
-24, 5.25, -20.25, 0, 1,   // 19

// front tali samsak
-22.3, 4.75, -20.10, 0, 0,  // 0
-22.4, 4.75, -20.10, 1, 0,  // 1
-22.4, 5.25, -20.10, 1, 1,  // 2
-22.3, 5.25, -20.10, 0, 1,  // 3

// right
-22.4, 5.25, -20.10, 0, 0,  // 4
-22.4, 5.25, -20.20, 1, 0,  // 5
-22.4, 4.75, -20.20, 1, 1,  // 6
-22.4, 4.75, -20.10, 0, 1,  // 7

// back
-22.3, 4.75, -20.20, 0, 0,  // 8
-22.4, 4.75, -20.20, 1, 0,  // 9
-22.4, 5.25, -20.20, 1, 1,  // 10
-22.3, 5.25, -20.20, 0, 1,  // 11

// left
-22.3, 4.75, -20.20, 0, 0,  // 12
-22.3, 4.75, -20.10, 1, 0,  // 13
-22.3, 5.25, -20.10, 1, 1,  // 14
-22.3, 5.25, -20.20, 0, 1,  // 15

// upper
-22.4, 5.25, -20.10, 0, 0,  // 16
-22.3, 5.25, -20.10, 1, 0,  // 17
-22.3, 5.25, -20.20, 1, 1,  // 18
-22.4, 5.25, -20.20, 0, 1,  // 19


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22 ,  // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94  ,     // bottom
		96,  97,  98,  96,  98,  99,    // front
100, 103, 102, 100, 101, 102,   // right
104, 105, 106, 104, 106, 107,   // back
108, 110, 109, 108, 111, 110,   // left
112, 114, 113, 112, 115, 114,   // upper
116, 118, 117, 116, 119, 118,    // bottom
120, 123, 122, 120, 121, 122,   // right
124, 125, 126, 124, 126, 127,   // back
128, 130, 129, 128, 131, 130,   // left
132, 134, 133, 132, 135, 134,   // upper
136, 138, 137, 136, 139, 138 ,   // bottom
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedTiangSamsak()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 8);

	glBindVertexArray(VAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 360, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedTribun() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture6);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("ringsamping.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
-15, -0.5, 15, 0, 0,  // 0
15, -0.5, 15, 1, 0,   // 1
15, 1.75, 15, 1, 1,   // 2
-15, 1.75, 15, 0, 1,  // 3

// right
15, 1.75, 15, 0, 0,   // 4
15, 1.75, -15, 1, 0,  // 5
15, -0.5, -15, 1, 1,  // 6
15, -0.5, 15, 0, 1,   // 7

// back
-15, -0.5, -15, 0, 0, // 8
15, -0.5, -15, 1, 0,  // 9
15, 1.75, -15, 1, 1,  // 10
-15, 1.75, -15, 0, 1, // 11

// left
-15, -0.5, -15, 0, 0, // 12
-15, -0.5, 15, 1, 0,  // 13
-15, 1.75, 15, 1, 1,  // 14
-15, 1.75, -15, 0, 1, // 15

// upper
-20, 1.75, 20, 0, 0,  // 16
-15, 1.75, 20, 1, 0,  // 17
-15, 1.75, -15, 1, 1,  // 18
-20, 1.75, -15, 0, 1,  // 19

// upper
20, 1.75, 20, 0, 0,  // 16
15, 1.75, 20, 1, 0,  // 17
15, 1.75, -15, 1, 1,  // 18
20, 1.75, -15, 0, 1,  // 19
		

		// front
-20, -0.5, 20, 0, 0,  // 0
20, -0.5, 20, 1, 0,   // 1
20, 3, 20, 1, 1,      // 2
-20, 3, 20, 0, 1,     // 3

// right
20, 3, 20, 0, 0,      // 4
20, 3, -15, 1, 0,     // 5
20, -0.5, -15, 1, 1,  // 6
20, -0.5, 20, 0, 1,   // 7

// back
-20, -0.5, -20, 0, 0, // 8
20, -0.5, -20, 1, 0,  // 9
20, 3, -20, 1, 1,     // 10
-20, 3, -20, 0, 1,    // 11

// left
-20, -0.5, -15, 0, 0, // 12
-20, -0.5, 20, 1, 0,  // 13
-20, 3, 20, 1, 1,     // 14
-20, 3, -15, 0, 1,    // 15

// upper
20, 3, -15, 0, 0,      // 16
25, 3, -15, 1, 0,     // 17
25, 3, 25, 1, 1,    // 18
20, 3, 25, 0, 1,     // 19

// upper
-20, 3, -15, 0, 0,      // 16
-25, 3, -15, 1, 0,     // 17
-25, 3, 25, 1, 1,    // 18
-20, 3, 25, 0, 1,     // 19

// upper
15, 1.75, 20, 0, 0,  // 16
-15, 1.75, 20, 1, 0,  // 17
-15, 1.75, 15, 1, 1,  // 18
15, 1.75, 15, 0, 1,  // 19

// upper
-20, 3, 20, 0, 0,      // 16
20, 3, 20, 1, 0,     // 17
20, 3, 25, 1, 1,    // 18
-20, 3, 25, 0, 1,     // 19

// back
-20, -0.5, -15, 0, 0,   // 8
-15, -0.5, -15, 1, 0,   // 9
-15, 1.75, -15, 1, 1,   // 10
-20, 1.75, -15, 0, 1,   // 11

// back
20, -0.5, -15, 0, 0,   // 8
15, -0.5, -15, 1, 0,   // 9
15, 1.75, -15, 1, 1,   // 10
20, 1.75, -15, 0, 1,   // 11

// back
25, -0.5, -15, 0, 0,   // 8
20, -0.5, -15, 1, 0,   // 9
20, 3, -15, 1, 1,   // 10
25, 3, -15, 0, 1,   // 11

// back
-25, -0.5, -15, 0, 0,   // 8
-20, -0.5, -15, 1, 0,   // 9
-20, 3, -15, 1, 1,   // 10
-25, 3, -15, 0, 1,   // 11

// front
-4, 10.25, -0.1, 0, 0,  // 0
4, 10.25, -0.1, 1, 0,   // 1
4, 12, -0.1, 1, 1,      // 2
-4, 12, -0.1, 0, 1,     // 3

// right
4, 12, -0.1, 0, 0,      // 4
4, 12, 0.1, 1, 0,       // 5
4, 10.25, 0.1, 1, 1,    // 6
4, 10.25, -0.1, 0, 1,   // 7

// back
-4, 10.25, 0.1, 0, 0,   // 8
4, 10.25, 0.1, 1, 0,    // 9
4, 12, 0.1, 1, 1,       // 10
-4, 12, 0.1, 0, 1,      // 11

// left
-4, 10.25, -0.1, 0, 0,  // 12
-4, 10.25, 0.1, 1, 0,   // 13
-4, 12, 0.1, 1, 1,      // 14
-4, 12, -0.1, 0, 1,     // 15

// top
4, 12, -0.1, 0, 0,      // 16
-4, 12, -0.1, 1, 0,     // 17
-4, 12, 0.1, 1, 1,      // 18
4, 12, 0.1, 0, 1,       // 19

// bottom
-4, 10.25, -0.1, 0, 0,  // 20
4, 10.25, -0.1, 1, 0,   // 21
4, 10.25, 0.1, 1, 1,    // 22
-4, 10.25, 0.1, 0, 1




	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		//8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22 ,  // upper
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		//32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94  ,     // bottom
		96,  97,  98,  96,  98,  99,    // front
100, 103, 102, 100, 101, 102,   // right
104, 105, 106, 104, 106, 107,   // back
108, 110, 109, 108, 111, 110,   // left
112, 114, 113, 112, 115, 114,   // upper
116, 118, 117, 116, 119, 118,    // bottom
120, 123, 122, 120, 121, 122,   // right
124, 125, 126, 124, 126, 127,   // back
128, 130, 129, 128, 131, 130,   // left
132, 134, 133, 132, 135, 134,   // upper
136, 138, 137, 136, 139, 138 ,   // bottom
140, 143, 142, 140, 141, 142,  // right
144, 145, 146, 144, 146, 147,  // back
148, 150, 149, 148, 151, 150,  // left
152, 154, 153, 152, 155, 154,  // upper
156, 158, 157, 156, 159, 158,  // bottom
160, 163, 162, 160, 161, 162,  // right
164, 165, 166, 164, 166, 167,  // back
168, 170, 169, 168, 171, 170,  // left
172, 174, 173, 172, 175, 174,  // upper
176, 178, 177, 176, 179, 178,   // bottom
180, 182, 181, 180, 183, 182,  // upper
184, 186, 185, 184, 187, 186,  // bottom
188, 191, 190, 188, 189, 190,  // right
192, 193, 194, 192, 194, 195,  // back
196, 198, 197, 196, 199, 198,  // left
200, 202, 201, 200, 203, 202,  // upper
204, 206, 205, 204, 207, 206 ,  // bottom
208, 209, 210, 208, 210, 211,  // back
212, 214, 213, 212, 215, 214,  // left
216, 218, 217, 216, 219, 218,  // upper
220, 222, 221, 220, 223, 222,  // bottom
224, 227, 226, 224, 225, 226,  // right
228, 229, 230, 228, 230, 231,  // back
232, 234, 233, 232, 235, 234,  // left
236, 238, 237, 236, 239, 238,  // upper
240, 242, 241, 240, 243, 242,  // bottom
244, 246, 245, 244, 247, 246,  // upper
248, 250, 249, 248, 251, 250,  // bottom
252, 255, 254, 252, 253, 254,  // right
256, 257, 258, 256, 258, 259,  // back
260, 262, 261, 260, 263, 262,  // left
264, 266, 265, 264, 267, 266,  // upper
268, 270, 269, 268, 271, 270,   // bottom
272, 274, 273, 272, 275, 274,  // upper
276, 278, 277, 276, 279, 278,  // bottom
280, 281, 282, 280, 282, 283,  // back
284, 286, 285, 284, 287, 286,  // left
288, 290, 289, 288, 291, 290,  // upper
292, 294, 293, 292, 295, 294,  // bottom
296, 299, 298, 296, 297, 298,  // right
300, 301, 302, 300, 302, 303,  // back
304, 306, 305, 304, 307, 306,  // left
308, 310, 309, 308, 311, 310,  // upper
312, 314, 313, 312, 315, 314,  // bottom
316, 318, 317, 316, 319, 318,  // upper
320, 322, 321, 320, 323, 322,  // bottom
324, 327, 326, 324, 325, 326,  // right
328, 329, 330, 328, 330, 331,  // back
332, 334, 333, 332, 335, 334,  // left
336, 338, 337, 336, 339, 338,  // upper
340, 342, 341, 340, 343, 342   // bottom





	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedTribun()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture6);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 5);

	glBindVertexArray(VAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 576, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedBanner() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("banner.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
-20, 15, 24, 0, 0,     // 0
20, 15, 24, 1, 0,      // 1
20, 22.5, 24, 1, 1,    // 2
-20, 22.5, 24, 0, 1,   // 3

// right
20, 22.5, 24, 0, 0,    // 4
20, 22.5, 25, 1, 0,    // 5
20, 15, 25, 1, 1,      // 6
20, 15, 24, 0, 1,      // 7

// back
-20, 15, 25, 0, 0,     // 8
20, 15, 25, 1, 0,      // 9
20, 22.5, 25, 1, 1,    // 10
-20, 22.5, 25, 0, 1,   // 11

// left
-20, 15, 25, 0, 0,     // 12
-20, 15, 24, 1, 0,     // 13
-20, 22.5, 24, 1, 1,   // 14
-20, 22.5, 25, 0, 1,   // 15

// upper
20, 22.5, 24, 0, 0,    // 16
-20, 22.5, 24, 1, 0,   // 17
-20, 22.5, 25, 1, 1,   // 18
20, 22.5, 25, 0, 1,    // 19

// bottom
-20, 15, 25, 0, 0,     // 20
20, 15, 25, 1, 0,      // 21
20, 15, 24, 1, 1,      // 22
-20, 15, 24, 0, 1,     // 23

// front led 2
-20, 15, -24, 0, 0,     // 0
20, 15, -24, 1, 0,      // 1
20, 22.5, -24, 1, 1,    // 2
-20, 22.5, -24, 0, 1,   // 3

// right
20, 22.5, -24, 0, 0,    // 4
20, 22.5, -25, 1, 0,    // 5
20, 15, -25, 1, 1,      // 6
20, 15, -24, 0, 1,      // 7

// back
-20, 15, -25, 0, 0,     // 8
20, 15, -25, 1, 0,      // 9
20, 22.5, -25, 1, 1,    // 10
-20, 22.5, -25, 0, 1,   // 11

// left
-20, 15, -25, 0, 0,     // 12
-20, 15, -24, 1, 0,     // 13
-20, 22.5,- 24, 1, 1,   // 14
-20, 22.5, -25, 0, 1,   // 15

// upper
20, 22.5, -24, 0, 0,    // 16
-20, 22.5, -24, 1, 0,   // 17
-20, 22.5, -25, 1, 1,   // 18
20, 22.5, -25, 0, 1,    // 19

// bottom
-20, 15, -25, 0, 0,     // 20
20, 15, -25, 1, 0,      // 21
20, 15, -24, 1, 1,      // 22
-20, 15, -24, 0, 1,     // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22  , // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedBanner()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 6);

	glBindVertexArray(VAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 144, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void Demo::BuildTexturedManusia() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("rectangle 20.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

// Body
// front
-1.5, 4.75, -0.8, 0, 0,  // 24
1.5, 4.75, -0.8, 1, 0,   // 25
1.5, 8, -0.8, 1, 1,      // 26
-1.5, 8, -0.8, 0, 1,     // 27

// right
1.5, 8, -0.8, 0, 0,      // 28
1.5, 8, 0.8, 1, 0,       // 29
1.5, 4.75, 0.8, 1, 1,    // 30
1.5, 4.75, -0.8, 0, 1,   // 31

// back
-1.5, 4.75, 0.8, 0, 0,   // 32
1.5, 4.75, 0.8, 1, 0,    // 33
1.5, 8, 0.8, 1, 1,       // 34
-1.5, 8, 0.8, 0, 1,      // 35

// left
-1.5, 4.75, -0.8, 0, 0,  // 36
-1.5, 4.75, 0.8, 1, 0,   // 37
-1.5, 8, 0.8, 1, 1,      // 38
-1.5, 8, -0.8, 0, 1,     // 39

// top
1.5, 8, -0.8, 0, 0,      // 40
-1.5, 8, -0.8, 1, 0,     // 41
-1.5, 8, 0.8, 1, 1,      // 42
1.5, 8, 0.8, 0, 1,       // 43

// bottom
-1.5, 4.75, -0.8, 0, 0,  // 44
1.5, 4.75, -0.8, 1, 0,   // 45
1.5, 4.75, 0.8, 1, 1,    // 46
-1.5, 4.75, 0.8, 0, 1,   // 47


// front
2.5, 10.25, -0.5, 0, 0,   // 48
3.85, 10.25, -0.5, 1, 0,  // 49
2.85, 7.5, -0.5, 1, 1,    // 50
1.5, 7.5, -0.5, 0, 1,     // 51

// right
2.85, 7.5, -0.5, 0, 0,    // 52
2.85, 7.5, 0.5, 1, 0,     // 53
3.85, 10.25, 0.5, 1, 1,   // 54
3.85, 10.25, -0.5, 0, 1,  // 55

// back
2.5, 10.25, 0.5, 0, 0,    // 56
3.85, 10.25, 0.5, 1, 0,   // 57
2.85, 7.5, 0.5, 1, 1,     // 58
1.5, 7.5, 0.5, 0, 1,      // 59

// left
2.5, 10.25, -0.5, 0, 0,   // 60
2.5, 10.25, 0.5, 1, 0,    // 61
1.5, 7.5, 0.5, 1, 1,      // 62
1.5, 7.5, -0.5, 0, 1,     // 63

// top
2.85, 7.5, -0.5, 0, 0,    // 64
1.5, 7.5, -0.5, 1, 0,     // 65
1.5, 7.5, 0.5, 1, 1,      // 66
2.85, 7.5, 0.5, 0, 1,     // 67

// bottom
2.5, 10.25, -0.5, 0, 0,   // 68
3.85, 10.25, -0.5, 1, 0,  // 69
3.85, 10.25, 0.5, 1, 1,   // 70
2.5, 10.25, 0.5, 0, 1,    // 71

// Left Arm
// front
-3.85, 10.25, -0.5, 0, 0,   // 72
-2.85, 10.25, -0.5, 1, 0,    // 73
-1.5, 7.5, -0.5, 1, 1,      // 74
-2.85, 7.5, -0.5, 0, 1,     // 75

// right
-1.5, 7.5, -0.5, 0, 0,      // 76
-1.5, 7.5, 0.5, 1, 0,       // 77
-2.85, 10.25, 0.5, 1, 1,     // 78
-2.85, 10.25, -0.5, 0, 1,    // 79

// back
-3.85, 10.25, 0.5, 0, 0,    // 80
-2.85, 10.25, 0.5, 1, 0,     // 81
-1.5, 7.5, 0.5, 1, 1,       // 82
-2.85, 7.5, 0.5, 0, 1,      // 83

// left
-3.85, 10.25, -0.5, 0, 0,   // 84
-3.85, 10.25, 0.5, 1, 0,    // 85
-2.85, 7.5, 0.5, 1, 1,      // 86
-2.85, 7.5, -0.5, 0, 1,     // 87

// top
-1.5, 7.5, -0.5, 0, 0,      // 88
-2.85, 7.5, -0.5, 1, 0,     // 89
-2.85, 7.5, 0.5, 1, 1,      // 90
-1.5, 7.5, 0.5, 0, 1,       // 91

// bottom
-3.85, 10.25, -0.5, 0, 0,   // 92
-2.85, 10.25, -0.5, 1, 0,    // 93
-2.85, 10.25, 0.5, 1, 1,     // 94
-3.85, 10.25, 0.5, 0, 1,    // 95


	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22  , // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94  ,     // bottom
		96,  97,  98,  96,  98,  99,    // front
100, 103, 102, 100, 101, 102,   // right
104, 105, 106, 104, 106, 107,   // back
108, 110, 109, 108, 111, 110,   // left
112, 114, 113, 112, 115, 114,   // upper
116, 118, 117, 116, 119, 118,    // bottom
120, 123, 122, 120, 121, 122,   // right
124, 125, 126, 124, 126, 127,   // back
128, 130, 129, 128, 131, 130,   // left
132, 134, 133, 132, 135, 134,   // upper
136, 138, 137, 136, 139, 138 ,   // bottom
140, 143, 142, 140, 141, 142,  // right
144, 145, 146, 144, 146, 147,  // back
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedManusia()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture8);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 7);

	glBindVertexArray(VAO8); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 720, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void Demo::BuildTexturedHitam() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("background2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front dasar tiang samsak
23, -0.5, -19, 0, 0,    // 0
25, -0.5, -19, 1, 0,   // 1
25, 0.5, -19, 1, 1,    // 2
23, 0.5, -19, 0, 1,     // 3

// right
25, 0.5, -19, 0, 0,    // 4
25, 0.5, -21.5, 1, 0,  // 5
25, -0.5, -21.5, 1, 1, // 6
25, -0.5, -19, 0, 1,   // 7

// back
23, -0.5, -21.5, 0, 0,  // 8
25, -0.5, -21.5, 1, 0, // 9
25, 0.5, -21.5, 1, 1,  // 10
23, 0.5, -21.5, 0, 1,   // 11

// left
23, -0.5, -21.5, 0, 0,  // 12
23, -0.5, -19, 1, 0,    // 13
23, 0.5, -19, 1, 1,     // 14
23, 0.5, -21.5, 0, 1,   // 15

// upper
25, 0.5, -19, 0, 0,    // 16
23, 0.5, -19, 1, 0,     // 17
23, 0.5, -21.5, 1, 1,   // 18
25, 0.5, -21.5, 0, 1,  // 19


// front samsak
21.55, 1.5, -19.10, 0, 0,   // 0
23.25, 1.5, -19.10, 1, 0,   // 1
23.25, 4.75, -19.10, 1, 1,  // 2
21.55, 4.75, -19.10, 0, 1,  // 3

// right
23.25, 4.75, -19.10, 0, 0,  // 4
23.25, 4.75, -21.20, 1, 0,   // 5
23.25, 1.5, -21.20, 1, 1,    // 6
23.25, 1.5, -19.10, 0, 1,   // 7

// back
21.55, 1.5, -21.20, 0, 0,    // 8
23.25, 1.5, -21.20, 1, 0,    // 9
23.25, 4.75, -21.20, 1, 1,   // 10
21.55, 4.75, -21.20, 0, 1,   // 11

// left
21.55, 1.5, -21.20, 0, 0,    // 12
21.55, 1.5, -19.10, 1, 0,   // 13
21.55, 4.75, -19.10, 1, 1,  // 14
21.55, 4.75, -21.20, 0, 1,   // 15

// upper
23.25, 4.75, -19.10, 0, 0,  // 16
21.55, 4.75, -19.10, 1, 0,  // 17
21.55, 4.75, -21.20, 1, 1,   // 18
23.25, 4.75, -21.20, 0, 1,   // 19

// bottom
21.55, 1.5, -21.20, 0, 0,    // 20
23.25, 1.5, -21.20, 1, 0,    // 21
23.25, 1.5, -19.10, 1, 1,   // 22
21.55, 1.5, -19.10, 0, 1,   // 23


// front dasar tiang samsak
-23, -0.5, -19, 0, 0,      // 0
-25, -0.5, -19, 1, 0,      // 1
-25, 0.5, -19, 1, 1,       // 2
-23, 0.5, -19, 0, 1,       // 3

// right
-25, 0.5, -19, 0, 0,       // 4
-25, 0.5, -21.5, 1, 0,     // 5
-25, -0.5, -21.5, 1, 1,    // 6
-25, -0.5, -19, 0, 1,      // 7

// back
-23, -0.5, -21.5, 0, 0,    // 8
-25, -0.5, -21.5, 1, 0,    // 9
-25, 0.5, -21.5, 1, 1,     // 10
-23, 0.5, -21.5, 0, 1,     // 11

// left
-23, -0.5, -21.5, 0, 0,    // 12
-23, -0.5, -19, 1, 0,      // 13
-23, 0.5, -19, 1, 1,       // 14
-23, 0.5, -21.5, 0, 1,     // 15

// upper
-25, 0.5, -19, 0, 0,       // 16
-23, 0.5, -19, 1, 0,       // 17
-23, 0.5, -21.5, 1, 1,     // 18
-25, 0.5, -21.5, 0, 1,     // 19


// front samsak
-21.55, 1.5, -19.10, 0, 0,   // 0
-23.25, 1.5, -19.10, 1, 0,   // 1
-23.25, 4.75, -19.10, 1, 1,  // 2
-21.55, 4.75, -19.10, 0, 1,  // 3

// right
-23.25, 4.75, -19.10, 0, 0,  // 4
-23.25, 4.75, -21.20, 1, 0,  // 5
-23.25, 1.5, -21.20, 1, 1,   // 6
-23.25, 1.5, -19.10, 0, 1,   // 7

// back
-21.55, 1.5, -21.20, 0, 0,   // 8
-23.25, 1.5, -21.20, 1, 0,   // 9
-23.25, 4.75, -21.20, 1, 1,  // 10
-21.55, 4.75, -21.20, 0, 1,  // 11

// left
-21.55, 1.5, -21.20, 0, 0,   // 12
-21.55, 1.5, -19.10, 1, 0,   // 13
-21.55, 4.75, -19.10, 1, 1,  // 14
-21.55, 4.75, -21.20, 0, 1,  // 15

// upper
-23.25, 4.75, -19.10, 0, 0,  // 16
-21.55, 4.75, -19.10, 1, 0,  // 17
-21.55, 4.75, -21.20, 1, 1,  // 18
-23.25, 4.75, -21.20, 0, 1,  // 19

// bottom
-21.55, 1.5, -21.20, 0, 0,   // 20
-23.25, 1.5, -21.20, 1, 0,   // 21
-23.25, 1.5, -19.10, 1, 1,   // 22
-21.55, 1.5, -19.10, 0, 1,   // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22 ,  // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94  ,     // bottom
		96,  97,  98,  96,  98,  99,    // front
100, 103, 102, 100, 101, 102,   // right
104, 105, 106, 104, 106, 107,   // back
108, 110, 109, 108, 111, 110,   // left
112, 114, 113, 112, 115, 114,   // upper
116, 118, 117, 116, 119, 118,    // bottom
	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedHitam()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture10);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 9);

	glBindVertexArray(VAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 360, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedJuara() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("download (1).jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front tribun juara
-5, -0.5, -20, 0, 0,   // 0
5, -0.5, -20, 1, 0,    // 1
5, 2, -20, 1, 1,       // 2
-5, 2, -20, 0, 1,      // 3

// right
5, 2, -20, 0, 0,       // 4
5, 2, -25, 1, 0,       // 5
5, -0.5, -25, 1, 1,    // 6
5, -0.5, -20, 0, 1,    // 7

// back
-5, -0.5, -25, 0, 0,   // 8
5, -0.5, -25, 1, 0,    // 9
5, 2, -25, 1, 1,       // 10
-5, 2, -25, 0, 1,      // 11

// left
-5, -0.5, -25, 0, 0,   // 12
-5, -0.5, -20, 1, 0,   // 13
-5, 2, -20, 1, 1,      // 14
-5, 2, -25, 0, 1,      // 15

// upper
5, 2, -20, 0, 0,       // 16
-5, 2, -20, 1, 0,      // 17
-5, 2, -25, 1, 1,      // 18
5, 2, -25, 0, 1,       // 19

// bottom
-5, -0.5, -25, 0, 0,   // 20
5, -0.5, -25, 1, 0,    // 21
5, -0.5, -20, 1, 1,    // 22
-5, -0.5, -20, 0, 1,   // 23

// front tribun juara 1
-2.5, 2, -20, 0, 0,    // 0
2.5, 2, -20, 1, 0,     // 1
2.5, 3.25, -20, 1, 1,  // 2
-2.5, 3.25, -20, 0, 1, // 3

// right
2.5, 3.25, -20, 0, 0,  // 4
2.5, 3.25, -25, 1, 0,  // 5
2.5, 2, -25, 1, 1,     // 6
2.5, 2, -20, 0, 1,     // 7

// back
-2.5, 2, -25, 0, 0,    // 8
2.5, 2, -25, 1, 0,     // 9
2.5, 3.25, -25, 1, 1,  // 10
-2.5, 3.25, -25, 0, 1, // 11

// left
-2.5, 2, -25, 0, 0,    // 12
-2.5, 2, -20, 1, 0,    // 13
-2.5, 3.25, -20, 1, 1, // 14
-2.5, 3.25, -25, 0, 1, // 15

// upper
2.5, 3.25, -20, 0, 0,  // 16
-2.5, 3.25, -20, 1, 0, // 17
-2.5, 3.25, -25, 1, 1, // 18
2.5, 3.25, -25, 0, 1,  // 19

// bottom
-2.5, 2, -25, 0, 0,    // 20
2.5, 2, -25, 1, 0,     // 21
2.5, 2, -20, 1, 1,     // 22
-2.5, 2, -20, 0, 1,    // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22 ,  // bottom
		24,  25,  26,  24,  26,  27,   // front
		28,  31,  30,  28, 29, 30,     // right
		32,  33,  34,  32,  34,  35,   // back
		36,  38,  37,  36,  39,  38,   // left
		40, 42, 41, 40, 43, 42,      // upper
		44, 46, 45, 44, 47, 46  ,     // upper
		48,  49,  50,  48,  50,  51,   // front
		52,  55,  54,  52, 53, 54,     // right
		56,  57,  58,  56,  58,  59,   // back
		60,  62,  61,  60,  63,  62,   // left
		64, 66, 65, 64, 67, 66,      // upper
		68, 70, 69, 68, 71, 70 ,      // bottom
		72,  73,  74,  72,  74,  75,   // front
		76,  79,  78,  76, 77, 78,     // right
		80,  81,  82,  80,  82,  83,   // back
		84,  86,  85,  84,  87,  86,   // left
		88, 90, 89, 88, 91, 90,      // upper
		92, 94, 93, 92, 95, 94  ,     // bottom
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedJuara()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, texture11);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 10);

	glBindVertexArray(VAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 360, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedKepala() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("download (1).jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// Head
// front
-1, 8, -1, 0, 0,  // 0
1, 8, -1, 1, 0,   // 1
1, 10, -1, 1, 1,  // 2
-1, 10, -1, 0, 1, // 3

// right
1, 10, -1, 0, 0,  // 4
1, 10, 1, 1, 0,   // 5
1, 8, 1, 1, 1,    // 6
1, 8, -1, 0, 1,   // 7

// back
-1, 8, 1, 0, 0,   // 8
1, 8, 1, 1, 0,    // 9
1, 10, 1, 1, 1,   // 10
-1, 10, 1, 0, 1,  // 11

// left
-1, 8, -1, 0, 0,  // 12
-1, 8, 1, 1, 0,   // 13
-1, 10, 1, 1, 1,  // 14
-1, 10, -1, 0, 1, // 15

// top
1, 10, -1, 0, 0,  // 16
-1, 10, -1, 1, 0, // 17
-1, 10, 1, 1, 1,  // 18
1, 10, 1, 0, 1,   // 19

// bottom
-1, 8, -1, 0, 0,  // 20
1, 8, -1, 1, 0,   // 21
1, 8, 1, 1, 1,    // 22
-1, 8, 1, 0, 1,   // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO12);
	glGenBuffers(1, &VBO12);
	glGenBuffers(1, &EBO12);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO12);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO12);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedKepala()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, texture12);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 11);

	glBindVertexArray(VAO12); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedKaki() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("background2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// Ri Leg
// front
-1, 2, -1, 0, 0,  // 48
1, 2, -1, 1, 0,   // 49
1, 4.75, -1, 1, 1,   // 50
-1, 4.75, -1, 0, 1,  // 51

// right
1, 4.75, -1, 0, 0,   // 52
1, 4.75, 1, 1, 0,    // 53
1, 2, 1, 1, 1,    // 54
1, 2, -1, 0, 1,   // 55

// back
-1, 2, 1, 0, 0,   // 56
1, 2, 1, 1, 0,    // 57
1, 4.75, 1, 1, 1,    // 58
-1, 4.75, 1, 0, 1,   // 59

// left
-1, 2, -1, 0, 0,  // 60
-1, 2, 1, 1, 0,   // 61
-1, 4.75, 1, 1, 1,   // 62
-1, 4.75, -1, 0, 1,  // 63

// top
1, 4.75, -1, 0, 0,   // 64
-1, 4.75, -1, 1, 0,  // 65
-1, 4.75, 1, 1, 1,   // 66
1, 4.75, 1, 0, 1,    // 67

// bottom
-1, 2, -1, 0, 0,  // 68
1, 2, -1, 1, 0,   // 69
1, 2, 1, 1, 1,    // 70
-1, 2, 1, 0, 1,   // 71
// Right Arm
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO13);
	glGenBuffers(1, &VBO13);
	glGenBuffers(1, &EBO13);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO13);

	glBindBuffer(GL_ARRAY_BUFFER, VBO13);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO13);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedKaki()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, texture13);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 12);

	glBindVertexArray(VAO13); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedSabuk() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture14);
	glBindTexture(GL_TEXTURE_2D, texture14);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("download (1).jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-10, -0.5, 10, 0, 0,  // 0
		10, -0.5, 10, 1, 0,   // 1
		10,  2, 10, 1, 1,   // 2
		-10,  2, 10, 0, 1,  // 3

		// right
		10,  2,  10, 0, 0,  // 4
		10,  2, -10, 1, 0,  // 5
		10, -0.5, -10, 1, 1,  // 6
		10, -0.5,  10, 0, 1,  // 7

		// back
		-10, -0.5, -10, 0, 0, // 8 
		10,  -0.5, -10, 1, 0, // 9
		10,   2, -10, 1, 1, // 10
		-10,  2, -10, 0, 1, // 11

		// left
		-10, -0.5, -10, 0, 0, // 12
		-10, -0.5,  10, 1, 0, // 13
		-10,  2,  10, 1, 1, // 14
		-10,  2, -10, 0, 1, // 15

		// upper
		10, 2,  10, 0, 0,   // 16
		-10, 2,  10, 1, 0,  // 17
		-10, 2, -10, 1, 1,  // 18
		10, 2, -10, 0, 1,   // 19

		// bottom
		-10, -0.5, -10, 0, 0, // 20
		10, -0.5, -10, 1, 0,  // 21
		10, -0.5,  10, 1, 1,  // 22
		-10, -0.5,  10, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  7,  6,  4,5,6, // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO14);
	glGenBuffers(1, &VBO14);
	glGenBuffers(1, &EBO14);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO14);

	glBindBuffer(GL_ARRAY_BUFFER, VBO14);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO14);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawTexturedSabuk()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, texture14);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 13);

	glBindVertexArray(VAO14); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 5.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Camera: Free Camera Implementation", 800, 600, false, true);
}