#include "graphics.h"
extern bool input;
extern bool Fire;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
	
}

bool Graphics::Initialize(int width, int height)
{
	// Used for the linux OS
	#if !defined(__APPLE__) && !defined(MACOSX)
		// cout << glewGetString(GLEW_VERSION) << endl;
		glewExperimental = GL_TRUE;

		auto status = glewInit();

		// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
		glGetError();

		//Check for error
		if (status != GLEW_OK)
		{
			std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
			return false;
		}
	#endif

	// For OpenGL 3
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Init Camera
	m_camera = new Camera();
	if(!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	// Set up Gourand shader
	m_shader[0] = new Shader();
	if(!m_shader[0]->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if(!m_shader[0]->AddShader(GL_VERTEX_SHADER, "shaders/pvVert.glsl"))
	{
		printf("Gouraud Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if(!m_shader[0]->AddShader(GL_FRAGMENT_SHADER, "shaders/pvFrag.glsl"))
	{
		printf("Gouraud Fragment Shader failed to Initialize\n");
		return false;
	}

	// Set up Phong shader
	m_shader[1] = new Shader();
	if(!m_shader[1]->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if(!m_shader[1]->AddShader(GL_VERTEX_SHADER, "shaders/pfVert.glsl"))
	{
		printf("Phong Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if(!m_shader[1]->AddShader(GL_FRAGMENT_SHADER, "shaders/pfFrag.glsl"))
	{
		printf("Phong Fragment Shader failed to Initialize\n");
		return false;
	}

	physicsEngine.SetUpPhysics(); //Sets up the Bullet physics world that the simulation will run in

	// And now we create all the desired physics objects
	// The rendered objects are also created
	physicsEngine.CreatePlayer(btVector3(-15.0,1.5,0.0), btVector3(1.0f, 3.0f, 1.0f), btScalar(10.0f)); //Create the player's collider
	physicsEngine.CreateGun(); // Create the gun
	//Create enemies
	physicsEngine.CreateEnemy(btVector3(3.0,2.0,5.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemy(btVector3(7.0,2.0,-5.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemy(btVector3(-2.0,2.0,3.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemy(btVector3(3.0,2.0,5.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemy(btVector3(7.0,2.0,-5.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemy(btVector3(-2.0,2.0,3.0), btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	//Create enemies that will spawn while the plaeyr is playing
	physicsEngine.CreateEnemyToBeSpawned(5000, btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemyToBeSpawned(10000, btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemyToBeSpawned(15000, btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	physicsEngine.CreateEnemyToBeSpawned(20000, btVector3(2.0f, 10.0f, 2.0f), btScalar(0.0f));
	
	
	
	

    //Create the level using the CreateObject() function
	//Setting up the first room of the level
	//The first room consists of: 4 walls, a floor, a roof, 2 doors and 2 sets of decorative butraces
	physicsEngine.CreateObject(btVector3(0.0, -1.0, 0.0), btVector3(50, 0.01, 50), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Floor.obj", false);
	physicsEngine.CreateObject(btVector3(0, 4.78, 17.5), btVector3(30, 10, 0.1), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallLeft.obj", false);
	physicsEngine.CreateObject(btVector3(0, 4.78, -17.5), btVector3(30, 10, 0.1), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallLeft.obj", false);
	physicsEngine.CreateObject(btVector3(-25.0, 4.78, 0.0), btVector3(0.1, 10, 30), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/NewWall.obj", false);
	physicsEngine.CreateObject(btVector3(25.0, 4.78, 0.0), btVector3(0.0, 0.0, 0.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/NewWall.obj", false);
	physicsEngine.CreateObject(btVector3(0.0, 10.0, 0.0), btVector3(0, 0, 0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Roof.obj", false);
	physicsEngine.CreateObject(btVector3(0.0, 5.2, -17.5), btVector3(0, 0, 0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Butress1.obj", false);
	physicsEngine.CreateObject(btVector3(0.0, 5.2, 17.5), btVector3(0, 0, 0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Butress2.obj", false);
	physicsEngine.CreateObject(btVector3(-25.1, -1.0, 0.0), btVector3(0, 0, 0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Door.obj", false);
	//physicsEngine.CreateObject(btVector3(25.1, -1.0, 0.0), btVector3(0, 0, 0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Door.obj", false);
	physicsEngine.CreateObject(btVector3(25.0, 4.78, 13.3), btVector3(0.1, 10.0, 10.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(25.0, 4.78, -13.3), btVector3(0.1, 10.0, 10.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);

	//First Coridor setup:
	physicsEngine.CreateObject(btVector3(40.0, -1.1, 0.0), btVector3(20, 0.1, 10.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorFloorF.obj", false);
	physicsEngine.CreateObject(btVector3(40.0, 4.0, 3.8), btVector3(15, 10, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorWallF.obj", false);
	physicsEngine.CreateObject(btVector3(40.0, 4.0, -3.8), btVector3(15, 10, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorWallF.obj", false);
	physicsEngine.CreateObject(btVector3(40.0, 9.0, 0.0), btVector3(20, 0.1, 10.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorRoofF.obj", false);

	//Setting up the second room:
	physicsEngine.CreateObject(btVector3(84.0, -1.1, 0.0), btVector3(30, 0.1, 36), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Floor2.obj", false);
	physicsEngine.CreateObject(btVector3(55.0, 4.78, 0.0), btVector3(0.0, 0.0, 0.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallSide1.obj", false);
	physicsEngine.CreateObject(btVector3(110.0, 4.78, 0.0), btVector3(0.5, 10.0, 36.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallSide2.obj", false);
	physicsEngine.CreateObject(btVector3(55.0, 4.78, -18.5), btVector3(0.5, 10.0, 15.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(55.0, 4.78, 18.5), btVector3(0.5, 10.0, 15.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(82.5, 4.78, -33.0), btVector3(55.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallDown2.obj", false);
	physicsEngine.CreateObject(btVector3(84.0, 10.0, 0.0), btVector3(30, 0.1, 36), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Roof2.obj", false);
	physicsEngine.CreateObject(btVector3(82.5, 4.78, 33.0), btVector3(0.0, 0.0, 0.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallUp2.obj", false);
	physicsEngine.CreateObject(btVector3(105.0, 4.78, 33.0), btVector3(17.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(63.0, 4.78, 33.0), btVector3(17.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	
	//Setting up the second Coridor:
	physicsEngine.CreateObject(btVector3(84.5, -1.1, 48.5), btVector3(10.0, 0.1, 20.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorFloorR.obj", false);
	physicsEngine.CreateObject(btVector3(80.0, 4.0, 48.5), btVector3(0.5, 10.0, 15.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorWallR.obj", false);
	physicsEngine.CreateObject(btVector3(89.0, 4.0, 48.5), btVector3(0.5, 10.0, 15.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorWallR.obj", false);
	physicsEngine.CreateObject(btVector3(84.5, 9.0, 48.5), btVector3(10.0, 0.1, 20.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/CoridorRoofR.obj", false);
	
	//Setting up the third room:
	physicsEngine.CreateObject(btVector3(82.5, 4.78, 64.0), btVector3(0.0, 0.0, 0.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallUp2.obj", false);
	physicsEngine.CreateObject(btVector3(105.0, 4.78, 64.0), btVector3(17.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(63.0, 4.78, 64.0), btVector3(17.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cubeSmall.obj", false);
	physicsEngine.CreateObject(btVector3(84.0, -1.1, 97.0), btVector3(30, 0.1, 36), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Floor2.obj", false);
	physicsEngine.CreateObject(btVector3(110.0, 4.78, 97.0), btVector3(0.5, 10.0, 36.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallSide2.obj", false);
	physicsEngine.CreateObject(btVector3(82.5, 4.78, 130.0), btVector3(55.0, 10.0, 0.5), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallDown2.obj", false);
	physicsEngine.CreateObject(btVector3(84.0, 10.0, 97.0), btVector3(30, 0.1, 36), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/Roof2.obj", false);
	physicsEngine.CreateObject(btVector3(55.0, 4.78, 97.0), btVector3(0.5, 10.0, 36.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/WallSide2.obj", false);

	//Create light switch
	physicsEngine.CreateObject(btVector3(110.0, 1.0, 97.0), btVector3(1.0, 1.0, 1.0), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), btScalar(0.0f), "models/cube.obj", true);

	//Set up lights
	incomingLight = {10.0, 100.0, 0.0, 1.0};
	ambient = {0.1, 0.1, 0.1, 1.0};

	sl.incoming = {0.0, -1.0, 0.0, 1.0};
	sl.ambient = {0.8, 0.8, 0.8, 1.0};
	sl.angle = glm::cos(glm::radians(10.0));

	// Connect the program
	if(!m_shader[0]->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	if(!m_shader[1]->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}

	m_spotLight = m_shader[0]->GetUniformLocation("lightPosition");
	if(m_spotLight == INVALID_UNIFORM_LOCATION) {
		cout << "light position not found\n";
	}

	m_sAmbient = m_shader[0]->GetUniformLocation("sAmbient");
	if(m_sAmbient == INVALID_UNIFORM_LOCATION) {
		cout << "ambient value not found\n";
	}

	 m_lightDir = m_shader[0]->GetUniformLocation("lightDir");
	if(m_lightDir == INVALID_UNIFORM_LOCATION)
	{
		printf("light direction not found\n");
	}

	m_clipCosine = m_shader[0]->GetUniformLocation("clip");
	if(m_clipCosine == INVALID_UNIFORM_LOCATION)
	{
		printf("clip not found\n");
	}

	m_diffuse = m_shader[0]->GetUniformLocation("DiffuseColor");
	if(m_diffuse == INVALID_UNIFORM_LOCATION)
	{
		printf("diffuse not found\n");
	}

	m_specular = m_shader[0]->GetUniformLocation("SpecularColor");
	if(m_specular == INVALID_UNIFORM_LOCATION)
	{
		printf("specular color not found\n");
	}

	m_shininess = m_shader[0]->GetUniformLocation("Shininess");
	if(m_shininess == INVALID_UNIFORM_LOCATION)
	{
		printf("shininess not found\n");
	}

	m_ambient = m_shader[0]->GetUniformLocation("AmbientColor");
	if(m_ambient == INVALID_UNIFORM_LOCATION)
	{
		printf("ambient color not found\n");
	}

	m_light = m_shader[0]->GetUniformLocation("LightArray");
	if(m_light == INVALID_UNIFORM_LOCATION)
	{
		printf("light array not found\n");
	}

	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader[0]->GetUniformLocation("projectionMatrix");
	if(m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("projection matrix not found\n");
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader[0]->GetUniformLocation("viewMatrix");
	if(m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("view matrix not found\n");
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader[0]->GetUniformLocation("modelMatrix");
	if(m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("model matrix not found\n");
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// enable object movement
	moveObjects = true;

	cycleShader();

	return true;
}

void Graphics::Update(unsigned int dt, bool& Fire, GLFWwindow* window)
{
	Keyboard(window);
	physicsEngine.Update(dt, window, playerDirection, playerLocation);
	gameOver = physicsEngine.getGameOver();
	if (gameOver)
		GameOverCheck(dt, window);

	bool tempSwitch = physicsEngine.GetLightSwitch();
	if (tempSwitch != lightSwitch) {
		lightSwitch = tempSwitch;
		toggleLights();
	}
}

void Graphics::Keyboard(GLFWwindow* window) {
	if (glfwGetKey( window, GLFW_KEY_F ) == GLFW_PRESS)
	{
		if(!flashToggle)
		{
			FlashlightToggle();
			flashToggle = true;
		}
	}
	if (glfwGetKey( window, GLFW_KEY_F ) == GLFW_RELEASE)
	{
		flashToggle = false;
	}
}

void Graphics::toggleLights() {
	if (lightSwitch) 
		ambient = {0.6, 0.6, 0.6, 1.0};
	else
		ambient = {0.2, 0.2, 0.2, 1.0};
}

void Graphics::GameOverCheck(unsigned int dt, GLFWwindow* window) {
	if (ambient.r <= 1.0)
		ambient.r += 0.01;
	if (ambient.g >= 0.0)
		ambient.g -= 0.01;
	if (ambient.b >= 0.0)
		ambient.b -= 0.01;

	lifetime -= dt * 1.0;

	if (lifetime <= 0.0)
		glfwSetWindowShouldClose(window,1); 	
}

void Graphics::FlashlightToggle() {
	flashlightOn = !flashlightOn;

	if (flashlightOn) 
		sl.ambient = {0.8, 0.8, 0.8, 1.0};
	else 
		sl.ambient = {0, 0, 0, 0};
}

void Graphics::Render()
{
	glm::mat4 tempMat;
	glm::vec4 tempVec;
	int index;

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_shader[shaderIndex]->Enable();

	//Move the camera with the player
	m_camera->UpdateView(playerLocation, playerDirection);

	// Send in the projection and view to the shader
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
	glUniform4f(m_ambient, ambient.r, ambient.g, ambient.b, ambient.a);
	glUniform4f(m_light, incomingLight.r, incomingLight.g, incomingLight.b, incomingLight.a);

	tempMat = physicsEngine.visibleObjects[1]->GetModel();

	tempVec = tempMat * glm::vec4(0.0, 0.0, 0.0, 1.0);

	// Spotlight info
	glUniform4f(m_spotLight, playerLocation.x, playerLocation.y + 1.0, playerLocation.z, 1.0);
	glUniform4f(m_sAmbient, sl.ambient.r, sl.ambient.g, sl.ambient.b, sl.ambient.a);
	glUniform3f(m_lightDir, playerDirection.x * 10, playerDirection.y, playerDirection.z * 10);
	glUniform1f(m_clipCosine, sl.angle);

	//Go through the visible objects and update them
	for(int i = 0; i < physicsEngine.visibleObjects.size(); i++)
	{
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(physicsEngine.visibleObjects[i]->GetModel()));

		tempVec = physicsEngine.visibleObjects[i]->getDiffuse();

		glUniform4f(m_diffuse, tempVec.r, tempVec.g, tempVec.b, tempVec.a);

		tempVec = physicsEngine.visibleObjects[i]->getSpecular();
		if (specToggle) {
			tempVec.r *= 1.5;
			tempVec.g *= 1.5;
			tempVec.b *= 1.5;
		}
		else {
			tempVec.r *= 0.75;
			tempVec.g *= 0.75;
			tempVec.b *= 0.75;
		}

		glUniform4f(m_specular, tempVec.r, tempVec.g, tempVec.b, tempVec.a);

		glUniform1f(m_shininess, physicsEngine.visibleObjects[i]->getShine());

		physicsEngine.visibleObjects[i]->Render();
	}

	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}

std::string Graphics::ErrorString(GLenum error)
{
	if(error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if(error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if(error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if(error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}

}

// Light/Shader functions
void Graphics::cycleShader() {
	shaderType = !shaderType;	//flip the boolean

	if (shaderType)
		shaderIndex = 0;
	else
		shaderIndex = 1;

	m_spotLight = m_shader[shaderIndex]->GetUniformLocation("lightPosition");
	if(m_spotLight == INVALID_UNIFORM_LOCATION) {
		cout << "light position not found\n";
	}

	m_sAmbient = m_shader[shaderIndex]->GetUniformLocation("sAmbient");
	if(m_sAmbient == INVALID_UNIFORM_LOCATION) {
		cout << "sAmbient not found\n";
	}

	m_lightDir = m_shader[shaderIndex]->GetUniformLocation("lightDir");
	if(m_lightDir == INVALID_UNIFORM_LOCATION)
	{
		printf("Light Direction not found\n");
	}

	m_clipCosine = m_shader[shaderIndex]->GetUniformLocation("clip");
	if(m_clipCosine == INVALID_UNIFORM_LOCATION)
	{
		printf("clip not found\n");
	}

	m_diffuse = m_shader[shaderIndex]->GetUniformLocation("DiffuseColor");
	if(m_diffuse == INVALID_UNIFORM_LOCATION)
	{
		printf("Diffuse Color not found\n");
	}

	m_specular = m_shader[shaderIndex]->GetUniformLocation("SpecularColor");
	if(m_specular == INVALID_UNIFORM_LOCATION)
	{
		printf("Specular Color not found\n");
	}

	m_shininess = m_shader[shaderIndex]->GetUniformLocation("Shininess");
	if(m_shininess == INVALID_UNIFORM_LOCATION)
	{
		printf("Shininess not found\n");
	}

	m_ambient = m_shader[shaderIndex]->GetUniformLocation("AmbientColor");
	if(m_ambient == INVALID_UNIFORM_LOCATION)
	{
		printf("Ambient Color not found\n");
	}

	m_light = m_shader[shaderIndex]->GetUniformLocation("LightArray");
	if(m_light == INVALID_UNIFORM_LOCATION)
	{
		printf("Light Array not found\n");
	}

	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader[shaderIndex]->GetUniformLocation("projectionMatrix");
	if(m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_projectionMatrix not found\n");
	}

	// Locate the view matrix in the shader
	m_viewMatrix = m_shader[shaderIndex]->GetUniformLocation("viewMatrix");
	if(m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_viewMatrix not found\n");
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader[shaderIndex]->GetUniformLocation("modelMatrix");
	if(m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_modelMatrix not found\n");
	}	
}	


