#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <string>
#include <cstdio>
#include <btBulletDynamicsCommon.h>
#include "object.h"
#include "graphics_headers.h"

using namespace std;

class PhysicsEngine 
{
  public:
    PhysicsEngine();
    ~PhysicsEngine();

    bool SetUpPhysics();
    bool CreatePlane();
    bool CreateBall(btVector3 position, btScalar radius, btScalar mass);
    bool CreateCube(btVector3 position, btVector3 halfwayVectors, btScalar mass);
    bool CreateCylinder(btVector3 position, btVector3 halfwayVectors, btScalar mass);
    bool CreateWall(btVector3 position);

    void Update(unsigned int dt);
    vector<Object*> visibleObjects;
	  btDiscreteDynamicsWorld *dynamicsWorld;
    void PlungerFire();

  private:

    // world variables, needed to create the Bullet environment
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    

    
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

};

#endif

