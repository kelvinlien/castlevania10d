#include <list>
#include "GameObject.h"
#include "Entity.h"
#include "Define.h"
#include "Camera.h"


#define MIN_OBJECT_NUMBER_TO_SPLIT 1

class Quadtree
{
	static Quadtree* __instance;
	int            m_level;
	RECT          m_region;
	vector<Entity*>*         entities_list;
	Quadtree**     m_nodes;

	bool           IsContain(Entity* entity);
	bool	IsInsideCamera();
	void           Split();
public:
	Quadtree();
	Quadtree(int level, RECT region);
	~Quadtree();

	void           Clear();
	void           Insert(Entity* entity);
	void          Retrieve(vector<Entity*>* return_entities_list, Entity* entity);
	void          RetrieveFromCamera(vector<Entity*> return_entities_list);
	Quadtree** GetNodes() { return m_nodes; }

	static Quadtree* GetInstance();
};

