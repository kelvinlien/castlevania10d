#include <list>
#include "GameObject.h"
#include "Define.h"


#define MIN_OBJECT_NUMBER_TO_SPLIT 1

class Quadtree
{
	static Quadtree* __instance;
	int            m_level;
	RECT*          m_region;
	vector<CGameObject*>*         m_objects_list;
	Quadtree**     m_nodes;

	bool           IsContain(CGameObject* object);
	void           Split();
public:
	Quadtree();
	Quadtree(int level, RECT region);
	~Quadtree();

	void           Clear();
	void           Insert(CGameObject* entity);
	void          Retrieve(vector<CGameObject*>* return_objects_list, CGameObject* entity);

	static Quadtree* GetInstance();
};

