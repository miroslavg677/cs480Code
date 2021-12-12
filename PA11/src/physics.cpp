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
	//Setup possible spawn locations for enemies
	//First room
	spawnlist[0].x=15;
	spawnlist[0].z=-10;
	spawnlist[1].x=15;
	spawnlist[1].z=5;
	spawnlist[2].x=2;
	spawnlist[2].z=-8;
	spawnlist[3].x=5;
	spawnlist[3].z=12;
	spawnlist[4].x=-5;
	spawnlist[4].z=-10;
	//Second Room
	spawnlist[5].x=92;
	spawnlist[5].z=1;
	spawnlist[6].x=105;
	spawnlist[6].z=8;
	spawnlist[7].x=66;
	spawnlist[7].z=-25;
	spawnlist[8].x=84;
	spawnlist[8].z=-15;
	spawnlist[9].x=90;
	spawnlist[9].z=12;
	//Thrid Room
	spawnlist[10].x=84;
	spawnlist[10].z=110;
	spawnlist[11].x=66;
	spawnlist[11].z=100;
	spawnlist[12].x=105;
	spawnlist[12].z=72;
	spawnlist[13].x=72;
	spawnlist[13].z=88;
	spawnlist[14].x=100;
	spawnlist[14].z=120;

	//Sets up all the global Bullet variables that are needed for the simulation
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0.0, -9.8, 0.0));

	return true;
}

void PhysicsEngine::GameStart() {
	score = 0;
	lives = 3;

	cout << "New Game!\n3 lives remaining\nScore: 0\n";
}

//Creates the physics object and the corresponding OpenGl rendered obect for the plane that has the art on it.
bool PhysicsEngine::CreatePlane() {
	//make the physics object in this case a plane
	btCollisionShape* floorShape = new btStaticPlaneShape(btVector3(0, 0, 0), 1);
	collisionShapes.push_back(floorShape);

	//make the transform
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,0,0));

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

	plane->Create("models/board.obj"); // attach a mesh and a texture to the model

	visibleObjects.push_back(plane); // Add the object to the visible objects list

	return true;
}

//Creates the physics object and the corresponding OpenGl rendered obect for:
bool PhysicsEngine::CreatePlayer(btVector3 position, btVector3 halfwayVectors, btScalar mass) {
	btCollisionShape* playerShape = new btBoxShape(halfwayVectors);

	playerIndex = collisionShapes.size();

	collisionShapes.push_back(playerShape);

	// Create Dynamic Objects
	btTransform playerTransform;
	playerTransform.setIdentity();
	playerTransform.setOrigin(position);

	btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		playerShape->calculateLocalInertia(mass,localInertia);
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}

	btDefaultMotionState* MotionState = new btDefaultMotionState(playerTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, playerShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);

	body->activate();
	body->setActivationState(DISABLE_DEACTIVATION);
	body->setLinearFactor(btVector3(1.0,0.0,1.0));
	body->setAngularFactor(btVector3(1.0,1.0,1.0));

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/cubeSmall.obj");

	visibleObjects.push_back(cube);
	return true;
}


//Creates a physics object of user definded dimentions, position , rotation and also creates a corresponding visual object that is also user defined
//                                      Postion vv        Size vvvv              mass vvv
bool PhysicsEngine::CreateObject(btVector3 position, btVector3 ColliderSize, btScalar mass, 
								 						btScalar X, btScalar Y, btScalar Z, // X, Y and Z axis orientation
								 						const char* OBJ_FileName, bool isWall) 
														 //      name of the^^^        
														 //       Obj file
{
	if(isWall)
	{
		switchIndex = collisionShapes.size();
	}

	//Create the Bullet Collision Object
	btCollisionShape* shape = new btBoxShape(ColliderSize);
	collisionShapes.push_back(shape);
	btTransform shapeTransform;
	btQuaternion rotation;//create the rotation quaternion
	rotation.setEuler(X,Y,Z);

	//Set rotation, position and identity
	shapeTransform.setIdentity();
	shapeTransform.setOrigin(position);
	shapeTransform.setRotation(rotation);
	
	//Decide if the object is static or not
	btVector3 localInertia(0,0,0);
	if(mass != 0.f) 
	{
		shape->calculateLocalInertia(mass,localInertia);
	}
	else 
	{	
		
	}

	//Add the Bullet collision object to the dynamics world
	btDefaultMotionState* MotionState = new btDefaultMotionState(shapeTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	body->setRestitution(1.0);
	dynamicsWorld->addRigidBody(body);	


	//And finally create the visible object
	Object* cube = new Object();
	cube->Create(OBJ_FileName);
	visibleObjects.push_back(cube);

	return true;
}

//Create enemy object
bool PhysicsEngine::CreateEnemy(btVector3 position, btVector3 halfwayVectors, btScalar mass) {
	
	enemy Enemy;
	int temp[numEnemys];
	int tempIndexes=-1;
	int randomNumber;
	int randomAvailableIndex;
	for(int i=0;i<numEnemys;i++)
	{
		if(spawnlist[i].taken==false)
		{
			tempIndexes++;
			temp[tempIndexes] = i;
		}
	}
	randomNumber = (rand()%tempIndexes)+1;
	randomAvailableIndex = temp[randomNumber];
	position = (btVector3(spawnlist[randomAvailableIndex].x  , -1.0f, spawnlist[randomAvailableIndex].z));
    //cout << "SpawnIndex:" << randomAvailableIndex << std::endl;
	//cout << "SpawnX:" << spawnlist[randomAvailableIndex].x << "  ";
	//cout << "SpawnZ:" << spawnlist[randomAvailableIndex].z << std::endl;
	spawnlist[randomAvailableIndex].taken=true;
	Enemy.position=randomAvailableIndex;

	Enemy.dynamicWorldIndex = collisionShapes.size();
	Enemy.enemyIndex = enemyList.size();
	Enemy.respawn = -1000.0f;
	enemyList.push_back(Enemy);

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

	body->activate();
	body->setActivationState(DISABLE_DEACTIVATION);

	Object* enemy = new Object();
	enemy->Create("models/Enemy.obj");

	visibleObjects.push_back(enemy);
	visibleObjects[visibleObjects.size()-1]->isEnemy=true;
	//enemyPhys.push_back(enemy);
	return true;
}

bool PhysicsEngine::CreateEnemyToBeSpawned(float respawn, btVector3 halfwayVectors, btScalar mass) {
	
	enemy Enemy;
	int temp[numEnemys];
	int tempIndexes=-1;
	int randomNumber;
	int randomAvailableIndex;
	for(int i=0;i<numEnemys;i++)
	{
		if(spawnlist[i].taken==false)
		{
			tempIndexes++;
			temp[tempIndexes] = i;
		}
	}
	randomNumber = (rand()%tempIndexes)+1;
	randomAvailableIndex = temp[randomNumber];
	position = (btVector3(spawnlist[randomAvailableIndex].x  , -100.0f, spawnlist[randomAvailableIndex].z));
    //cout << "SpawnIndex:" << randomAvailableIndex << std::endl;
	//cout << "SpawnX:" << spawnlist[randomAvailableIndex].x << "  ";
	//cout << "SpawnZ:" << spawnlist[randomAvailableIndex].z << std::endl;
	spawnlist[randomAvailableIndex].taken=false;
	Enemy.position=randomAvailableIndex;

	Enemy.dynamicWorldIndex = collisionShapes.size();
	Enemy.enemyIndex = enemyList.size();
	Enemy.respawn = respawn;
	enemyList.push_back(Enemy);

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

	body->activate();
	body->setActivationState(DISABLE_DEACTIVATION);

	Object* enemy = new Object();
	enemy->Create("models/Enemy.obj");

	visibleObjects.push_back(enemy);
	visibleObjects[visibleObjects.size()-1]->isEnemy=true;
	//enemyPhys.push_back(enemy);
	return true;
}


//Creates the gun mesh, also records the index of the object in the visibleObjects array
//The gun does not have a collider and the positioning/rotation are handled in Object.cpp->Update()
bool PhysicsEngine::CreateGun() 
{
	//Creates a dumy Bullet object which isn't used for anything but it does keep the bullet object array and the visual objects array synced
	btCollisionShape* boxShape = new btBoxShape(btVector3(0.0f, 0.0f, 0.0f));
	collisionShapes.push_back(boxShape);
	btTransform boxTransform;
	boxTransform.setIdentity();
	boxTransform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
	btVector3 localInertia(0,0,0);
	btScalar mass = 0.0f;
	if(mass != 0.f){
		boxShape->calculateLocalInertia(mass,localInertia);
	}
	else{	
	}
	btDefaultMotionState* MotionState = new btDefaultMotionState(boxTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, boxShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	dynamicsWorld->addRigidBody(body);



	//Create the Gun model which moves with the player's movement
	Object* cube = new Object();
	cube->Create("models/Bolter.obj");
	GunMeshIndex = visibleObjects.size();
	cube->isGun = true;
	visibleObjects.push_back(cube);
	return true;
}

//Iterates through each physics object, runs the physics simulation, and calls the update function on each rendered object
void PhysicsEngine::Update(unsigned int dt, GLFWwindow* window, glm::vec3& playerDirection, glm::vec3& playerLocation) 
{
	MyResultCallback playerCallback;
	MyResultCallback callback;
	btCollisionObject* dynamicsWorldObject;
	btRigidBody* body;
	btTransform trans;
	btScalar m[16];
	int enemyIndex = 0;

	dynamicsWorld->stepSimulation(dt, 2);

	playerMove(dt, window);

	for( int i = 0; i < visibleObjects.size(); i++)
	{
		if(i != GunMeshIndex)
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

			visibleObjects[i]->Update(glm::make_mat4(m), position);
		}
		else
		{
			//Makes the gun follow the camera using the following steps:
			//Get the player's rigid body using Bullet 
			//Then get the player's transform 
			//Then make a OpenGL mat4 and pass it onto the gun
			//Also pass in the angle
			btCollisionObject* player;
			btRigidBody* playerBody;
			player = dynamicsWorld->getCollisionObjectArray()[playerIndex];	//Get the player object
			playerBody = btRigidBody::upcast(player);
			btTransform transform;
			if (playerBody && playerBody->getMotionState())
			{
				playerBody->getMotionState()->getWorldTransform(transform);
			} else
			{
				transform = player->getWorldTransform();
			}
			transform.getOpenGLMatrix(m);
			position = playerBody->getCenterOfMassPosition();
			visibleObjects[GunMeshIndex]->SetAngle(sim ,angle);
			visibleObjects[GunMeshIndex]->Update(glm::make_mat4(m), position);
		}
		if(i == switchIndex) {
			MyResultCallback switchCallback;

			btCollisionObject* switchObject = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* enemyBody = btRigidBody::upcast(switchObject);
			btCollisionObject* playerObject = dynamicsWorld->getCollisionObjectArray()[playerIndex];
			btRigidBody* playerBody = btRigidBody::upcast(playerObject);

			if (!switchIFrames)
				dynamicsWorld->contactPairTest(switchObject, playerObject, switchCallback);

			if (switchCallback.bCollision) {
				switchToggle = !switchToggle;
				switchIFrames = true;
				switchCallback.bCollision = false;
			}
		}
		if(visibleObjects[i]->isEnemy==true)
		{
			char pause;
			bool flag = true;
			
			//cout << "Enemy index " << enemyIndex << endl;
			
			btCollisionObject* enemyObject=dynamicsWorld->getCollisionObjectArray()[i];
			//std::cout << "Enemy index: " << i << endl;
			btRigidBody* enemyBody= btRigidBody::upcast(enemyObject);
			//enemyBody->activate();
			btCollisionObject* playerObject=dynamicsWorld->getCollisionObjectArray()[0];
			btRigidBody* playerBody= btRigidBody::upcast(playerObject);

			if (!iframes)
				dynamicsWorld->contactPairTest(playerObject, enemyObject,playerCallback);

			if (playerCallback.bCollision) 
			{
					iframes = true;
					//std::cout << "enemy hit"<< endl;
					float x;
        			float y;
        			float z;

					//Get world location of the enemy
        			x = (enemyBody->getWorldTransform().getOrigin()).x();
					y = (enemyBody->getWorldTransform().getOrigin()).y();
					z = (enemyBody->getWorldTransform().getOrigin()).z();
					btTransform transform;
					enemyBody->getMotionState()->getWorldTransform(transform);
					transform.setOrigin(btVector3(x,y-100.0,z));
					enemyBody->getMotionState()->setWorldTransform(transform);
					enemyBody->setCenterOfMassTransform(transform);
					enemyBody->activate();
					enemyBody->setWorldTransform(transform);
					enemyList[enemyIndex].respawn = 5000;
					spawnlist[enemyList[enemyIndex].position].taken = false;

					//Decrease lives
					lives--;
					std::cerr << "Lives Remaining: " << lives << std::endl;
					if(lives == 0)
					{
						//game over
						cout<< "Game Over" << std::endl;
						gameOverFlag = true;	
					}
					playerCallback.bCollision = false;
			}

			for(int j = 0; j < BulletList.size(); j++)
    		{
        		btCollisionObject* bullet;
        		btRigidBody* bulletBody;
        		bullet = dynamicsWorld->getCollisionObjectArray()[BulletList[j].dynamicWorldIndex];
				//bullet = dynamicsWorld->getCollisionObjectArray()[5];  
        		bulletBody = btRigidBody::upcast(bullet);
				//std::cout<< enemyList[enemyIndex].respawn<< endl;
			
				dynamicsWorld->contactPairTest(bullet, enemyObject, callback);
				if (callback.bCollision) 
				{
					//std::cout << "enemy hit"<< endl;
					DeleteBullet(BulletList[j].dynamicWorldIndex, BulletList[j].visualIndex, j);
					float x;
        			float y;
        			float z;
					//Get world location of the enemy
        			x = (enemyBody->getWorldTransform().getOrigin()).x();
					y = (enemyBody->getWorldTransform().getOrigin()).y();
					z = (enemyBody->getWorldTransform().getOrigin()).z();
					btTransform transform;
					enemyBody->getMotionState()->getWorldTransform(transform);
					transform.setOrigin(btVector3(x,y-100.0,z));
					enemyBody->getMotionState()->setWorldTransform(transform);
					enemyBody->setCenterOfMassTransform(transform);
					enemyBody->activate();
					enemyBody->setWorldTransform(transform);
					enemyList[enemyIndex].respawn = 5000;
					spawnlist[enemyList[enemyIndex].position].taken = false;
					//Increase score
					score+=50;
					std::cout << "Score: " << score << std::endl;
				}

				
		
			}
			enemyIndex++;
		}
	}
	//UpdateGunPos();
	playerLocation = glm::vec3(position.x(), position.y(), position.z());
	playerDirection = glm::vec3(direction.x(), direction.y(), direction.z());

	for(int i = 0; i < BulletList.size(); i++)
	{
		if(BulletList[i].lifetime <= 0.0f)
		{
			DeleteBullet(BulletList[i].dynamicWorldIndex, BulletList[i].visualIndex, i);
		}
		else
		{
			BulletList[i].lifetime -= dt * 1.0;
		}
	}
	for(int i = 0; i < enemyList.size(); i++)
	{
		if(enemyList[i].respawn <= 0.0f && enemyList[i].respawn>-100)
		{
			//std::cout << "respawn" << std::endl;
			btCollisionObject* enemyObject=dynamicsWorld->getCollisionObjectArray()[enemyList[i].dynamicWorldIndex];
			btRigidBody* enemyBody= btRigidBody::upcast(enemyObject);
			float x;
        	float y;
        	float z;
			//Select random respawn point
			btVector3 newPosition;
			int temp[numEnemys];
			int tempIndexes=-1;
			int randomNumber;body->setLinearFactor(btVector3(1.0,0.0,1.0));
	body->setAngularFactor(btVector3(1.0,1.0,1.0));
			int randomAvailableIndex;
			for(int i=0;i<numEnemys;i++)
			{
				if(spawnlist[i].taken==false)
				{
					tempIndexes++;
					temp[tempIndexes] = i;
					
				}
			}	
			randomNumber = (rand()%tempIndexes)+1;
			randomAvailableIndex = temp[randomNumber];
			//std::cout << "tempIndexes: " <<tempIndexes <<std::endl;
			//std::cout <<"RandomAvail: " <<randomAvailableIndex << std::endl;
			newPosition = (btVector3(spawnlist[randomAvailableIndex].x, -1.0f, spawnlist[randomAvailableIndex].z));
    		//std::cout << "SpawnIndex:" << randomAvailableIndex << std::endl;
			//std::cout << "SpawnX:" << spawnlist[randomAvailableIndex].x << "  ";
			//std::cout << "SpawnZ:" << spawnlist[randomAvailableIndex].z << std::endl;
			spawnlist[randomAvailableIndex].taken=true;
			enemyList[i].position=randomAvailableIndex;
			btTransform transform;
			enemyBody->getMotionState()->getWorldTransform(transform);
			transform.setOrigin(btVector3(spawnlist[randomAvailableIndex].x, -1.0 ,spawnlist[randomAvailableIndex].z));
			enemyBody->getMotionState()->setWorldTransform(transform);
			enemyBody->setCenterOfMassTransform(transform);
			enemyBody->activate();
			enemyBody->setWorldTransform(transform);
			enemyList[i].respawn= -1000;
		}
		else if(enemyList[i].respawn>0)
		{
			enemyList[i].respawn -= dt * 1.0;
			//std::cout<< enemyList[i].respawn<< endl;
		}
	}

	iframeCount(dt);
	switchIFrameCount(dt);
}

void PhysicsEngine::iframeCount(unsigned int dt) {
	if (iframes)
		iframeCounter -= dt * 1.0;

	if (iframeCounter <= 0.0) {
		iframes = false;
		iframeCounter = 1000;
	}
		
}
void PhysicsEngine::switchIFrameCount(unsigned int dt) {
	if (switchIFrames)
		switchIFrameCounter -= dt * 1.0;

	if (switchIFrameCounter <= 0.0) {
		switchIFrames = false;
		switchIFrameCounter = 1000;
	}
}

bool PhysicsEngine::GetLightSwitch() {
	return switchToggle;
}

bool PhysicsEngine::getGameOver() {
	return gameOverFlag;
}
/*
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
}*/

// Moves the player forward or backward, depending on the button pressed
void PhysicsEngine::playerMove(unsigned int dt, GLFWwindow* window) {

	btCollisionObject* player;
	btRigidBody* playerBody;
	player = dynamicsWorld->getCollisionObjectArray()[playerIndex];	//Get the player object
	playerBody = btRigidBody::upcast(player);
	playerBody->activate();

	btTransform transform;
	transform.getIdentity();
	playerBody->getMotionState()->getWorldTransform(transform);

	if (!gameOverFlag) {
		//Rotate Left
		if (glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS){
			angle += 0.05f;
		}
		//Rotate Right
		if (glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS){
			angle -= 0.05f;
		}
		btVector3 movement = btVector3(0, 0, 0);

		//direction = x and z components of the angle
		direction = btVector3(sin(angle), 0,  cos(angle));
		//right = 90 degrees right of the angle (for strafing)
		btVector3 right = btVector3(sin(angle - 3.14f/2.0f), 0, cos(angle - 3.14f/2.0f));

		if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
			movement += (direction * 10);
		}
		// Move backward
		if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
			movement -= (direction * 10);
		}
		// Strafe right
		if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
			movement += (right * 10);
		}
		// Strafe left
		if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
			movement -= (right * 10);
		}
		if (glfwGetKey( window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS){
			FireBullet(position, btVector3(1.0, 1.0, 1.0), 0.0, direction);
		}

		if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS)
		{
			if(!hasFired)
			{
				FireBullet(position, btVector3(1.0, 1.0, 1.0), 1.0, btVector3(direction.x(), direction.y() + 0.1, direction.z()));
				hasFired = true;
			}
		}
		if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_RELEASE)
		{
			hasFired = false;
		}

		playerBody->setLinearVelocity(movement);
		playerBody->getMotionState()->setWorldTransform(transform);
		playerBody->setCenterOfMassTransform(transform);
		position = playerBody->getCenterOfMassPosition();
	}
	else {
		playerBody->setLinearVelocity(btVector3(0.0, -0.5, 0.0));
		playerBody->getMotionState()->setWorldTransform(transform);
		playerBody->setCenterOfMassTransform(transform);
		position = playerBody->getCenterOfMassPosition();
	}	
}



// Creates the physics body 
void PhysicsEngine::FireBullet(btVector3 position, btVector3 ColliderSize, btScalar mass, const btVector3 direction) 
{
	//Add the bullet onto the list of bullets
	Projectile bullet;
	bullet.dynamicWorldIndex = collisionShapes.size();
	bullet.visualIndex = visibleObjects.size();
	bullet.lifetime = 4000.0f;
	BulletList.push_back(bullet);

	btScalar radius = ColliderSize.x();
	//First create the Bullet collision object for the projectile
	btCollisionShape* sphereShape = new btSphereShape(radius);
	collisionShapes.push_back(sphereShape);
	// Create Dynamic Objects
	btTransform boxTransform;
    btQuaternion rotation;
    btScalar X = angle;
    rotation.setEuler(X, 0.0, 0.0);
    boxTransform.setIdentity();
	btVector3 direction1 = btVector3(sin(angle), 0,  cos(angle));
	position += (direction1 * 1.0f);
    boxTransform.setOrigin(position);
    boxTransform.setRotation(rotation);
    btVector3 localInertia(0,0,0);
	if(mass != 0.f) // if the mass of the object is not 0 make the object dynamic
	{
		sphereShape->calculateLocalInertia(mass,localInertia);
	}
	else //if the mass is 0 make it static 
	{	
		//ie do nothing
	}
	btDefaultMotionState* MotionState = new btDefaultMotionState(boxTransform);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyInfo(mass, MotionState, sphereShape, localInertia);
	btRigidBody* body = new btRigidBody(RigidBodyInfo);
	dynamicsWorld->addRigidBody(body);
	body->activate();
	body->setActivationState(DISABLE_DEACTIVATION);

	//Now make the rendered object and add it to the visible objects 
	Object* cube = new Object();
	cube->Create("models/Projectile.obj");
	visibleObjects.push_back(cube);

	//Now shoot the bullet forward
	btVector3 Vel = btVector3(sin(angle * (M_PI / 180.0)), 0.0, cos(angle * (M_PI / 180.0)));
	btVector3 velocity = direction;
	velocity.normalize();
	velocity *= 70.0f;
	body->setLinearVelocity(velocity);
}

void PhysicsEngine::DeleteBullet(int BulletIndex, int VisualIndex, int ListIndex)
{
	btCollisionObject* bullet = dynamicsWorld->getCollisionObjectArray()[BulletIndex];
	btRigidBody* bulletBody;
	bullet = dynamicsWorld->getCollisionObjectArray()[BulletIndex];	//Get the player object
	bulletBody = btRigidBody::upcast(bullet);
	btTransform transform;
	bulletBody->getMotionState()->getWorldTransform(transform);
	transform.setOrigin(btVector3(0.0,-100.0, 0.0));
	bulletBody->activate();
	bulletBody->setWorldTransform(transform);
	bulletBody->setActivationState(DISABLE_SIMULATION);
	bulletBody->setGravity(btVector3(0.0, 0.0, 0.0));
	auto elemToRemove = BulletList.begin() + ListIndex;
	BulletList.erase(elemToRemove); 

}

//Creates an "invibile" collider with a tiny cube mesh in the middle can be turned to desired angle, positioned
// and scaled as needed
bool PhysicsEngine::CreateBoxCollider(btVector3 position, btVector3 dimensions, btScalar X, btScalar Y, btScalar Z) 
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
    body->setRestitution(1.0);

    dynamicsWorld->addRigidBody(body);


    Object* cube = new Object();
    cube->Create("models/cubeSmall.obj");
    visibleObjects.push_back(cube);

    return true;
}

