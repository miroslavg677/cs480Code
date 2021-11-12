#include "physics.h"
#include <sys/time.h>

//Constructor
PhysicsEngine::PhysicsEngine()
{
}

//Destructor
PhysicsEngine::~PhysicsEngine()
{
}

//Basic Bullet setup
bool PhysicsEngine::SetUpPhysics() 
{
	//Sets up all the global Bullet variables that are needed for the simulation
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0.0, -9.75, 1.11));

	GameStart();

	return true;
}

void PhysicsEngine::GameStart() {
	score = 0;
	lives = 3;

	cout << "New Game!\n3 lives remaining\nScore: 0\n";
}

//Creates the physics object and the corresponding OpenGl rendered obect for the plane that has the art on it.
bool PhysicsEngine::CreatePlane()
{
	//make the physics object in this case a plane
	btCollisionShape* floorShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	collisionShapes.push_back(floorShape);

	//make the transform
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,0,1));

	btScalar mass(0.f); // set the gravity

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		floorShape->calculateLocalInertia(mass,localInertia); 
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}

	//make the ridgid body
	btDefaultMotionState* MotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, floorShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);

	dynamicsWorld->addRigidBody(body); // and add the ridgid body to the dynamics world

	Object* plane = new Object(); //uses the existing Object class to make a new object to be rendered

	plane->Create("models/board.obj", "textures/planeTex.jpg"); // attach a mesh and a texture to the model

	visibleObjects.push_back(plane); // Add the object to the visible objects list

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for the ball
bool PhysicsEngine::CreateBall(btVector3 position, btScalar radius, btScalar mass)
{
	
	btCollisionShape* sphereShape = new btSphereShape(radius);
	collisionShapes.push_back(sphereShape);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(position);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		sphereShape->calculateLocalInertia(mass,localInertia);
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}
	
	btDefaultMotionState* MotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, sphereShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	
	// make the ball bouncy 
	body->setRestitution(0.25);

	//Limit balls movement to 2D plane
	body->setLinearFactor(btVector3(1.0,0.0,1.0));
	body->setAngularFactor(btVector3(1.0,1.0,1.0));

	dynamicsWorld->addRigidBody(body);

	Object* sphere = new Object();
	sphere->Create("models/sphere.obj", "textures/pewterTex.jpg");

	ballIndex = visibleObjects.size();
	visibleObjects.push_back(sphere);

	return true;
}

int PhysicsEngine::getBallIndex() {
	return ballIndex;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The plunger
bool PhysicsEngine::CreateCube(btVector3 position, btVector3 halfwayVectors, btScalar mass)
{
	
	btCollisionShape* boxShape = new btBoxShape(halfwayVectors);
	collisionShapes.push_back(boxShape);

	// Create Dynamic Objects
	btTransform boxTransform;
	boxTransform.setIdentity();
	boxTransform.setOrigin(position);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		boxShape->calculateLocalInertia(mass,localInertia);
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(boxTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, boxShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/cube.obj", "textures/cracks.jpg");
	visibleObjects.push_back(cube);
	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The three bumpers
bool PhysicsEngine::CreateCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass)
{

	btCollisionShape* cylinderShape = new btCylinderShape(halfwayVectors);
	collisionShapes.push_back(cylinderShape);

	btTransform cylinderTransform;
	cylinderTransform.setIdentity();
	cylinderTransform.setOrigin(position);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		cylinderShape->calculateLocalInertia(mass,localInertia);
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(cylinderTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, cylinderShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(4.0);

	dynamicsWorld->addRigidBody(body);


	Object* cube = new Object();
	cube->Create("models/bumper.obj", "textures/woodTex.jpg");

	bumperIndex.push_back(visibleObjects.size());
	visibleObjects.push_back(cube);

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered object for both side walls
bool PhysicsEngine::CreateLeftWall(btVector3 position)
{
	
	btCollisionShape* shape = new btBoxShape(btVector3(0.5f, 3.0f, 60.0f));
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/sideWall.obj", "textures/stoneTex2.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates an "invibile" collider with a tiny cube mesh in the middle can be turned to desired angle, positioned
// and scaled as needed
bool PhysicsEngine::CreateBoxCollider(btVector3 position, btVector3 dimensions, btScalar X, btScalar Y, btScalar Z, bool backFlag) {	
	btCollisionShape* shape = new btBoxShape(dimensions);

	if (backFlag)
		backWallIndex = collisionShapes.size();

	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	btQuaternion rotation;
	rotation.setEuler(X,Y,Z);

	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	shapeTransform.setRotation(rotation);

	btScalar mass(0.0f);
	
	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);	


	Object* cube = new Object();
	cube->Create("models/cubeSmall.obj", "textures/stoneTex1.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The top wall of the pinball game
bool PhysicsEngine::CreateTopWall(btVector3 position, btVector3 dimensions)
{
	
	btCollisionShape* shape = new btBoxShape(btVector3(20,1,1));
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/topWall.obj", "textures/stoneTex1.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The bottom left corner
bool PhysicsEngine::CreateBottomLeft(btVector3 position)
{
	btCollisionShape* shape = new btBoxShape(btVector3(0.5,0.5,0.5));
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/bottomLeft.obj", "textures/stoneTex1.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The botton right corner
bool PhysicsEngine::CreateBottomRight(btVector3 position)
{
	btCollisionShape* shape = new btBoxShape(btVector3(0.5,0.5,0.5));
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/bottomRight.obj", "textures/stoneTex1.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
//The extra piece at the bottom
bool PhysicsEngine::CreateBottomThree(btVector3 position)
{
	
	btCollisionShape* shape = new btBoxShape(btVector3(5,3,.5));
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/bottomThree.obj", "textures/stoneTex1.jpg");
	visibleObjects.push_back(cube);

	return true;
}



//Creates the physics object and the corresponding OpenGl rendered obect for:
//The scoreboard
bool PhysicsEngine::CreateScoreboard(btVector3 position)
{
	
	btCollisionShape* shape = new btBoxShape(btVector3(0.1f,0.1f, 0.1f));
	collisionShapes.push_back(shape);

	btTransform shapeTransform;
	
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);

	btScalar mass(0.0f);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/scoreboard.obj", "models/backsplash1.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Creates the flippers that the player uses to push the ball
bool PhysicsEngine::CreateFlipper(btVector3 position, btVector3 dimensions, btScalar X, btScalar Y, btScalar Z)
{
	
	btCollisionShape* shape = new btBoxShape(dimensions);
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	btQuaternion rotation;
	rotation.setEuler(X,Y,Z);

	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	shapeTransform.setRotation(rotation);

	btScalar mass(0.0f);
	
	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/paddle.obj", "textures/woodTex.jpg");
	visibleObjects.push_back(cube);

	return true;
}

//Iterates through each physics object, runs the physics simulation, and calls the update function on each rendered object
void PhysicsEngine::Update(unsigned int dt)
{
	btCollisionObject* dynamicsWorldObject;
	btRigidBody* body;
	btTransform trans;
	btScalar m[16];

	dynamicsWorld->stepSimulation(dt, 2);

	for( int i = 0; i < visibleObjects.size(); i++)
	{
		dynamicsWorldObject = dynamicsWorld->getCollisionObjectArray()[i];
		body = btRigidBody::upcast(dynamicsWorldObject);

		
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		} else
		{
			trans = dynamicsWorldObject->getWorldTransform();
		}

		trans.getOpenGLMatrix(m);

		visibleObjects[i]->Update(glm::make_mat4(m));
		
	}

	if(sim) {
		collisionCheck();
	}
}

void PhysicsEngine::collisionCheck() {
	MyResultCallback callback;
	char pause;
	bool flag = true;
	btCollisionObject* bumperObject;
	btCollisionObject* ballObject = dynamicsWorld->getCollisionObjectArray()[ballIndex];
	btCollisionObject* backWallObject;

	btRigidBody* ballBody = btRigidBody::upcast(ballObject);

	// Get the ball object
	ballObject = dynamicsWorld->getCollisionObjectArray()[ballIndex];

	for(int i = 0; i < bumperIndex.size(); i++) {
		// Get the bumper objects
		bumperObject = dynamicsWorld->getCollisionObjectArray()[bumperIndex[i]];

		// Test for contact
		dynamicsWorld->contactPairTest(ballObject, bumperObject, callback);

		if (callback.bCollision) {
			score += 100;
			getScore();
		}
		callback.bCollision = false;
	}
	backWallObject = dynamicsWorld->getCollisionObjectArray()[backWallIndex];
	
	dynamicsWorld->contactPairTest(ballObject, backWallObject, callback);

	if (callback.bCollision) {
		lives--;
		btVector3 ballCoords = ballBody->getCenterOfMassPosition();
		btVector3 reset = btVector3(8.5, 0, 14) - ballCoords;

		if(lives) {
			cout << lives << " lives remaining." << endl;
			ballBody->setLinearVelocity(btVector3(0, 0, 0));
			ballBody->translate(reset);
		}
		else {
			cout << "Game Over. Thanks for playing" << endl;
			cout << "Your Final Score: " << score << endl;
			leaderboardPop();

			while (flag) {
				cout << "Restart? [Y/N]" << endl;
				cin >> pause;
				pause = tolower(pause);
				if (pause == 'y') {
					GameStart();
					ballBody->setLinearVelocity(btVector3(0, 0, 0));
					ballBody->translate(reset);
					flag = false;
				}
				else if (pause == 'n') {
					cout << "Have a nice day" << endl;
					flag = false;
					sim = false;
				}
				else
					cout << "please type Y or N only" << endl;
			}
		}
	}
}

void PhysicsEngine::getScore() {
	cout << "Score: " << score << endl;

	if (score > (10000 * liveMultiplier)) {
		cout << "Extra Life gained!" << endl;
		lives++;
		liveMultiplier++;
	}
}

void PhysicsEngine::leaderboardPop() {
	boardInfo thisScore;
	string name;

	do {
	cout << "Enter your initials! (3 letters): ";
	cin >> name;

	if (name.size() > 3)
		cout << "Three letters max" << endl;
	}while (name.size() > 3);

	thisScore.name = name;
	thisScore.score = score;

	leaderBoard.push_back(thisScore);

	sort(leaderBoard.begin(), leaderBoard.end());

	cout << "\n\nLeaderboard: " << endl;
	for (int i = 0; i < leaderBoard.size(); i++) {
		cout << leaderBoard[i].name << ": \t" << leaderBoard[i].score << endl;
	}
}

void PhysicsEngine::PlungerFire(bool temp)
{
	 //Moves the cube forward which fires the ball

	btCollisionObject* dynamicsWorldObject;
 	btRigidBody* body;
	dynamicsWorldObject = dynamicsWorld->getCollisionObjectArray()[1]; // Get the cube
	body = btRigidBody::upcast( dynamicsWorldObject );
	body->activate();

	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); // make the cube kinematic
	body->setActivationState(DISABLE_DEACTIVATION);
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
		float x;
		float y;
		float z;
	//Get world location of the plunger
	x = (body->getWorldTransform().getOrigin()).x();
	y = (body->getWorldTransform().getOrigin()).y();
	z = (body->getWorldTransform().getOrigin()).z();
	body->activate();

	if(!temp&&z>17)
	{
		z-= PlungerSpeed; // move the cube in the negative z direction
		transform.setOrigin(btVector3(x,y,z));
		body->getMotionState()->setWorldTransform(transform);
		body->setCenterOfMassTransform(transform);
			//body->activate();
	}
	else if(temp&&z<20)
	{
		z-= -0.06; // move the cube in the positive z direction
		transform.setOrigin(btVector3(x,y,z));
		body->getMotionState()->setWorldTransform(transform);
		body->setCenterOfMassTransform(transform);
		if(z>=5 && z<17)
		{
			PlungerSpeed = 0.01;
		}
		if(z>=17 && z<19)
		{
			PlungerSpeed = 0.20;
		}
		if(z>=19 && z<30)
		{
			PlungerSpeed = 0.99;
		}
	}
}

//Flipper fire
void PhysicsEngine::LB()
{
	btCollisionObject* dynamicsWorldObject;
 	btRigidBody* body;
	dynamicsWorldObject = dynamicsWorld->getCollisionObjectArray()[14]; // Get the cube
		body = btRigidBody::upcast( dynamicsWorldObject );
		body->activate();
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); // make the cube kinematic
		body->setActivationState(DISABLE_DEACTIVATION);
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
		float fx;
		float fy;
		float fz;
	//Get world location
	fx = (body->getWorldTransform().getOrigin()).x();
	fy = (body->getWorldTransform().getOrigin()).y();
	fz = (body->getWorldTransform().getOrigin()).z();
	body->activate();
	transform.setOrigin(btVector3(fx,fy,fz));
	btQuaternion quat;
	
	if(Lreverse==false)
	{
  	lx-=0.35;
	quat.setEuler(lx,ly,lz);
	transform.setRotation(quat);
	body->getMotionState()->setWorldTransform(transform);
	body->setCenterOfMassTransform(transform);
	Lreverse = true;
	}
	else if(Lreverse==true)
	{
	lx+=0.35;
	quat.setEuler(lx,ly,lz);
	transform.setRotation(quat);
	body->getMotionState()->setWorldTransform(transform);
	body->setCenterOfMassTransform(transform);
	Lreverse = false;
	}

	body->activate();
	

}
void PhysicsEngine::RB()
{
	btCollisionObject* dynamicsWorldObject;
 	btRigidBody* body;
	dynamicsWorldObject = dynamicsWorld->getCollisionObjectArray()[13]; // Get the cube
		body = btRigidBody::upcast( dynamicsWorldObject );
		body->activate();
	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); // make the cube kinematic
		body->setActivationState(DISABLE_DEACTIVATION);
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
		float fx;
		float fy;
		float fz;
	//Get world location
		fx = (body->getWorldTransform().getOrigin()).x();
	fy = (body->getWorldTransform().getOrigin()).y();
	fz = (body->getWorldTransform().getOrigin()).z();
	body->activate();
	transform.setOrigin(btVector3(fx,fy,fz));
	btQuaternion quat;
	
		if(Rreverse==false)
	{
  	rx-=0.25;
	
	//std::cout << x << std::endl;
	quat.setEuler(rx,ry,rz);
	transform.setRotation(quat);

	body->getMotionState()->setWorldTransform(transform);
	body->setCenterOfMassTransform(transform);

	
	Rreverse = true;
	}
	else if(Rreverse==true)
	{
	rx+=0.25;
	
	quat.setEuler(rx,ry,rz);
	transform.setRotation(quat);

	body->getMotionState()->setWorldTransform(transform);
	body->setCenterOfMassTransform(transform);
	Rreverse = false;
	}

	body->activate();
}

