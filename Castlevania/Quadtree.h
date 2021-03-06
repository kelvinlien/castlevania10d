#include <list>
#include "GameObject.h"
#include "Entity.h"
#include "Define.h"
#include "Camera.h"

#define MIN_OBJECT_NUMBER_TO_SPLIT 1

class Quadtree
{
	//static Quadtree* __instance;
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 5;
	int            level = 0;
	RECT          region;
	vector<Entity*>         entities_list;
	vector<Quadtree*>    nodes;

	void           Split();
public:
	//Quadtree();
	Quadtree(int pLevel, RECT pBounds);
	~Quadtree();

	vector<int> getIndexesForCamera(RECT *pRect);
	int getIndex(RECT* pRect);
	void           Clear();
	void           Insert(Entity* entity);
	void          Retrieve(vector<Entity*>* return_entities_list, Entity* entity);
	void          RetrieveFromCamera(vector<Entity*> &return_entities_list);
	vector<Quadtree*> GetNodes() { return nodes; }

	//static Quadtree* GetInstance();
};

