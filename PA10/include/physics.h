#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <string>
#include <cstdio>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "object.h"
#include "graphics_headers.h"


using namespace std;

struct MyResultCallback : public btCollisionWorld::ContactResultCallback {

    bool bCollision = false;

    btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
    {
		if (cp.m_distance1 < 0.15)
			bCollision = true;
		return cp.m_distance1;
    }
};

struct boardInfo {
	int score;
	string name;    

	bool operator < (const boardInfo& lb) const
    {
        return (score > lb.score);
    }
};

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
    bool CreateScoreboard(btVector3 position);
    bool CreateLeftWall(btVector3 position);
    bool CreateBoxCollider(btVector3, btVector3, btScalar, btScalar, btScalar, bool);
    bool CreateTopWall(btVector3 position, btVector3);
    bool CreateBottomLeft(btVector3 position);
    bool CreateBottomRight(btVector3 position);
    bool CreateBottomThree(btVector3 position);
    bool CreateFlipper(btVector3, btVector3, btScalar, btScalar, btScalar);

    void Update(unsigned int dt);
    vector<Object*> visibleObjects;
	int getBallIndex();
	vector<int> getBumperIndex();
	btDiscreteDynamicsWorld *dynamicsWorld;
    void PlungerFire(bool temp);
    void LB();
    void RB();

	void GameStart();
	void collisionCheck();
	void getScore();
	void leaderboardPop();
  private:

    // world variables, needed to create the Bullet environment
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;

    btAlignedObjectArray<btCollisionShape*> collisionShapes;
	int ballIndex;
	int backWallIndex;
	bool sim = true;
	vector<int> bumperIndex;
	vector<boardInfo> leaderBoard;
    float PlungerSpeed;
    bool Lreverse=true;
    bool Rreverse=false;
    btScalar lx=-.3, ly=0, lz=0;
    btScalar rx=.3, ry=0, rz=0;

	int score = 0;
	int liveMultiplier = 1;
	int lives = 3;
};

#endif

