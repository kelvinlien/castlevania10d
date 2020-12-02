#include <list>
#include "GameObject.h"
#include "Entity.h"
#include "Define.h"


#define MIN_OBJECT_NUMBER_TO_SPLIT 1

class Quadtree
{
	static Quadtree* __instance;
	int            m_level;
	RECT*          m_region;
	vector<Entity*>*         entities_list;
	Quadtree**     m_nodes;

	bool           IsContain(Entity* entity);
	void           Split();
public:
	Quadtree();
	Quadtree(int level, RECT region);
	~Quadtree();

	void           Clear();
	void           Insert(Entity* entity);
	void          Retrieve(vector<Entity*>* return_objects_list, Entity* entity);

	static Quadtree* GetInstance();
};

