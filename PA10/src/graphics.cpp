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
	physicsEngine.CreatePlane();
	physicsEngine.CreateCube(btVector3(8.5,1,17), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f)); //Creating the plunger
	physicsEngine.CreateBall(btVector3(8.5,0,14), btScalar(1.0f), btScalar(0.8f)); //Creating the ball
	

	//Creating the walls plane and bumpers for the pinball game
	physicsEngine.CreateLeftWall(btVector3(-10,1,1)); //Left wall
	physicsEngine.CreateLeftWall(btVector3(11,1,1));  //Right wall
	physicsEngine.CreateTopWall(btVector3(0,1,-16), btVector3(25,5,5)); //Top wall
	physicsEngine.CreateBottomLeft(btVector3(-8.8,.9,19.5)); //Botton Left wall
	physicsEngine.CreateBottomRight(btVector3(4,1,19.0)); //Bottom Right wall
	physicsEngine.CreateBottomThree(btVector3(8.5,1,21.0)); //Extra piece on the bottom
	physicsEngine.CreateCylinder(btVector3(2,1,5), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f)); //First bumper
	physicsEngine.CreateCylinder(btVector3(-2,1,-3), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f)); //Second bumper
	physicsEngine.CreateCylinder(btVector3(-5,1,12), btVector3(1.0f, 1.0f, 1.0f), btScalar(0.0f)); //Third bumper
	physicsEngine.CreateScoreboard(btVector3(0.2,8,-23)); //Create the scoreboard

	physicsEngine.CreateFlipper(btVector3(-0.05,1,20.5), btVector3(2,1,0.5), .3, 0, 0);   //Right flipper
	physicsEngine.CreateFlipper(btVector3(-6.55,1,20.5), btVector3(2,1,0.5), -.3, 0, 0);   //Left flipper

	//Invisible(sort of invisible) colliders for the rounded corners
	//They still have a mesh but it's tiny and hidden inside of the other meshes
	//-----------------------------Spawn Location----------Size----------------X,Y.Z Orientation
	//                             vvvvvvvvvvvvvvvv        vvvvv              vvvvvvvvvv
	physicsEngine.CreateBoxCollider(btVector3(8,1,-15),  btVector3(5,2,3),  -0.5, 0, 0, false);   //Upper Right corner
	physicsEngine.CreateBoxCollider(btVector3(-8,1,-15), btVector3(5,2,3),   0.5, 0, 0, false);   //Upper Left corner
	physicsEngine.CreateBoxCollider(btVector3(-10,1,19), btVector3(5,2,3),  -0.5, 0, 0, false);   //Lower Left corner
	physicsEngine.CreateBoxCollider(btVector3(1,1,20.5), btVector3(3,6,0.5), 0.6, 0, 0, false);   //Lower Right corner
	physicsEngine.CreateBoxCollider(btVector3(4,1,17), btVector3(3,6,0.5), 1.1, 0, 0, false);   //Extra collider
	physicsEngine.CreateBoxCollider(btVector3(5.7,1,14), btVector3(3,6,0.5), 1.58, 0, 0, false);   //Extra collider
	physicsEngine.CreateBoxCollider(btVector3(5.7,1,18), btVector3(3,6,0.5), 1.58, 0, 0, false);   //Extra collider
	physicsEngine.CreateBoxCollider(btVector3(0,0,25), btVector3(20,5,0.5), 0, 0, 0, true);   //Bottom Wall (Game loss logic)
	

	//Set up lights

	incomingLight = {10.0, 100.0, 0.0, 1.0};
	ambient = {0.44, 0.44, 0.44, 1.0};

	sl.incoming = {0.0, -1.0, 0.0, 1.0};
	sl.ambient = {0.2, 0.2, 0.8, 1.0};
	sl.angle = glm::cos(glm::radians(5.0));

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

	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// enable object movement
	moveObjects = true;

	return true;
}

void Graphics::Update(unsigned int dt, bool& Fire)
{
	physicsEngine.Update(dt);
	if(Fire == true)
  	{
   		physicsEngine.PlungerFire(true);
  	}
  	else
  	{ 
   		physicsEngine.PlungerFire(false);
  	}
}

// Set ambient light; toggle between 1/2x value and 2x value
void Graphics::setAmbient(int scalar) {
	ambient.r *= pow(1.25, scalar);
	ambient.g *= pow(1.25, scalar);
	ambient.b *= pow(1.25, scalar);
}

// set Specular light; toggle a value in a boolean array
void Graphics::setSpecular(bool flag){
	specToggle = flag;
}

// set spotlight size; change the spotlight's angle
void Graphics::setSLSize(int scalar) {
	if (sl.angle <= 1.0 && sl.angle > 0.0)
		sl.angle += (0.001 * scalar);
}

// set Spotlight Brightness; change the spotlights alpha value
void Graphics::setSLBrightness(int scalar) {
		sl.ambient.r += (0.1 * scalar);
		sl.ambient.g += (0.1 * scalar);
		sl.ambient.b += (0.1 * scalar);
}

void Graphics::Render()
{
	glm::mat4 tempMat;
	glm::vec4 tempVec;
	int index;

	//clear the screen
	glClearColor(0.0, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_shader[shaderIndex]->Enable();

	// Send in the projection and view to the shader
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
	glUniform4f(m_ambient, ambient.r, ambient.g, ambient.b, ambient.a);
	glUniform4f(m_light, incomingLight.r, incomingLight.g, incomingLight.b, incomingLight.a);

	// Attach the spotlight to the sphere
	index = physicsEngine.getBallIndex();

	tempMat = physicsEngine.visibleObjects[index]->GetModel();

	tempVec = tempMat * glm::vec4(0.0, 0.0, 0.0, 1.0);

	glUniform4f(m_spotLight, tempVec.x, tempVec.y + 80.0, tempVec.z, 1.0);
	glUniform4f(m_sAmbient, sl.ambient.r, sl.ambient.g, sl.ambient.b, sl.ambient.a);
	glUniform3f(m_lightDir, sl.incoming.r, sl.incoming.g, sl.incoming.b);
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

//Camera functions
void Graphics::Rotate(float scalar) {
	m_camera->Rotate(scalar);
}

//Function to move the cube
void Graphics::PlungerFire()
{
	physicsEngine.PlungerFire(true);
}
//Function to operate flipper
void Graphics::LeftBumper()
{
	physicsEngine.LB();
}
void Graphics::RightBumper()
{
	physicsEngine.RB();
}

void Graphics::ZoomOut()
{
	m_camera->ZoomOut();
}


