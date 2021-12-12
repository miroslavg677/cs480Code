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
		if (cp.m_distance1 < 0.05)
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

struct Projectile
{
	float lifetime;
	int dynamicWorldIndex;
	int visualIndex;

};
struct enemy
{
	float respawn;
	int dynamicWorldIndex;
	int enemyIndex;
	float x;
	float y;
	float z;
	int position;
};
struct spawn
{
	float x;
	float y;
	float z;
	bool taken=false;
	//int index;
};

class PhysicsEngine 
{
  public:
	PhysicsEngine();
	~PhysicsEngine();

	bool SetUpPhysics();
	bool CreatePlane();
	bool CreatePlayer(btVector3, btVector3, btScalar);
	bool CreateEnemy(btVector3, btVector3, btScalar);
	bool CreateEnemyToBeSpawned(float, btVector3, btScalar);
	bool CreateGun();
	void FireBullet(btVector3, btVector3, btScalar, const btVector3);
	void DeleteBullet(int , int , int); 
	bool CreateBoxCollider(btVector3 position, btVector3 dimensions, btScalar X, btScalar Y, btScalar Z);
	bool CreateObject(btVector3 position, btVector3 ColliderSize, btScalar mass, 
								 						btScalar X, btScalar Y, btScalar Z,
								 						const char* OBJ_FileName, bool isWall);

	void Update(unsigned int dt, GLFWwindow*, glm::vec3&, glm::vec3&);
	vector<Object*> visibleObjects;
	vector<Object*> enemyPhys;
	int getBallIndex();
	vector<int> getBumperIndex();
	btDiscreteDynamicsWorld *dynamicsWorld;
	btRigidBody* BolterBT_Ref;

	void playerMove(unsigned int, GLFWwindow* window);
	/*void PlungerFire(bool temp);
	void LB();
	void RB();*/

	void GameStart();
	void collisionCheck();
	bool getGameOver();
	void iframeCount(unsigned int);
	void switchIFrameCount(unsigned int);
	bool GetLightSwitch();
  	private:

	// world variables, needed to create the Bullet environment
	btBroadphaseInterface *broadphase;
	btDefaultCollisionConfiguration *collisionConfiguration;
	btCollisionDispatcher *dispatcher;
	btSequentialImpulseConstraintSolver *solver;

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	//Doomed Crusade stuff
	int playerIndex;
	int switchIndex;
	int GunIndex;
	int GunMeshIndex;
	float angle = 3.14/2.0f;
	btVector3 direction;
	btVector3 position = btVector3(0, 0, 0);
	bool hasFired = false;
	vector<Projectile> BulletList;
	vector<enemy> enemyList;
	int numEnemys=15;
	spawn spawnlist[15];

	bool gameOverFlag = false;
	bool iframes = false;
	int iframeCounter = 1000;
	bool switchToggle = false;
	bool switchIFrames = false;
	int switchIFrameCounter = 1000;

	//pinball stuff? to be checked & deleted as needed
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

