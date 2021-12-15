#include "physics.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

bool PhysicsEngine::SetUpPhysics() 
{
	//Sets up all the global Bullet variables that are needed for the simulation
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	
	dynamicsWorld->setGravity(btVector3(0, -9.81, 9.81));

	return true;
}

bool PhysicsEngine::CreatePlane()
{
	//make the physics object in this case a plane
	btCollisionShape* floorShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
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

	plane->Create("models/plane.obj", "textures/grass.jpg"); // attach a mesh and a texture to the model

	visibleObjects.push_back(plane); // Add the object to the visible objects list

	return true;
}

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
	body->setRestitution(1.0);

	//Limit balls movement to 2D plane
	body->setLinearFactor(btVector3(1.0,0.0,1.0));
	body->setAngularFactor(btVector3(1.0,1.0,1.0));

	dynamicsWorld->addRigidBody(body);

	Object* sphere = new Object();
	sphere->Create("models/sphere.obj", "textures/cracks.jpg");

	ballIndex = visibleObjects.size();
	visibleObjects.push_back(sphere);

	return true;
}

int PhysicsEngine::getBallIndex() {
	return ballIndex;
}

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
	body->setRestitution(1.0);

	dynamicsWorld->addRigidBody(body);


	Object* cube = new Object();
	cube->Create("models/cylinder.obj", "textures/cracks.jpg");
	visibleObjects.push_back(cube);

	return true;
}



bool PhysicsEngine::CreateWall(btVector3 position)
{
	
	btCollisionShape* shape = new btBoxShape(btVector3(60.0f, 3.0f, 0.5f));
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

	

	dynamicsWorld->addRigidBody(body);

	Object* cube = new Object();
	cube->Create("models/frontFacingWall.obj", "textures/cracks.jpg");
	visibleObjects.push_back(cube);

	return true;
}




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

}

void PhysicsEngine::PlungerFire()
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
				x = (body->getWorldTransform().getOrigin()).x();
	y = (body->getWorldTransform().getOrigin()).y();
	z = (body->getWorldTransform().getOrigin()).z();
	z-= 0.66; // move the cube in the negative z direction
	transform.setOrigin(btVector3(x,y,z));
	body->getMotionState()->setWorldTransform(transform);
	body->setCenterOfMassTransform(transform);
				body->activate();
}

