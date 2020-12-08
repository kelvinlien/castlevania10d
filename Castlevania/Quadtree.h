#include <list>
#include "GameObject.h"
#include "Entity.h"
#include "Define.h"
#include "Camera.h"


#define MIN_OBJECT_NUMBER_TO_SPLIT 1

class Quadtree
{
	static Quadtree* __instance;
	int            level = 0;
	RECT*          region;
	vector<Entity*>*         entities_list;
	vector<Quadtree*>*    nodes;

	bool           IsContain(Entity* entity);
	bool	IsInsideCamera();
	void           Split();
public:
	Quadtree();
	Quadtree(int pLevel, RECT *pBounds);
	~Quadtree();

	void           Clear();
	void           Insert(Entity* entity);
	void          Retrieve(vector<Entity*>* return_entities_list, Entity* entity);
	void          RetrieveFromCamera(vector<Entity*> return_entities_list);
	Quadtree** GetNodes() { return nodes; }

	static Quadtree* GetInstance();
};

