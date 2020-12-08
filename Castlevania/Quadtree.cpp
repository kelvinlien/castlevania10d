#include "Quadtree.h"

Quadtree* Quadtree::__instance = NULL;
bool Quadtree::IsContain(Entity * entity)
{
	float l, t, r, b;
	entity->GetTriggerZone(l,t,r,b);

	return !(r < region.left ||
		b < region.top ||
		l > region.right ||
		t > region.bottom);
}
bool Quadtree::IsInsideCamera()
{
	Camera* cam = Camera::GetInstance();
	float l, t, r, b;
	l = cam->GetCamX();
	t = cam->GetCamY();
	r = l + 800;
	b = t + 508;
	return !(r < region.left ||
		b < region.top ||
		l > region.right ||
		t > region.bottom);
}
void Quadtree::Split()
{
	nodes = new Quadtree*[4];

	long regionWidth = region.right - region.left;
	long regionHeight = region.bottom - region.top;

	RECT tl, tr, bl, br;
	tl.left = region.left;
	tl.top = region.top;
	tl.right = region.left + regionWidth / 2;
	tl.bottom = region.top + regionHeight / 2;
	nodes[0] = new Quadtree(level + 1,
		tl);
	tr.left = region.left + regionWidth / 2;
	tr.top = region.top;
	tr.right = region.right;
	tr.bottom = region.top + regionHeight / 2;
	nodes[1] = new Quadtree(level + 1,
		tr);
	bl.left = region.left;
	bl.top = region.top + regionHeight / 2;
	bl.right = region.left + regionWidth / 2;
	bl.bottom = region.bottom;
	nodes[2] = new Quadtree(level + 1,
		bl);
	br.left = region.left + regionWidth / 2;
	br.top = region.top + regionHeight / 2;
	br.right = region.right;
	br.bottom = region.bottom;
	nodes[3] = new Quadtree(level + 1,
		br);
}
Quadtree::Quadtree(int pLevel, RECT *pBounds)
{
	level = pLevel;
	entities_list = new vector<Entity*>();
	region = pBounds;
	nodes = new vector<Quadtree*>(4);
}
Quadtree::~Quadtree()
{
	delete region;
}
void Quadtree::Clear()
{
	entities_list->clear();

	for (int i = 0; i < nodes->size(); i++)
	{
		// replace nullptr with empty vector with same type
		if (nodes[i] != vector<Quadtree*>())
		{
			nodes[i]->clear();
			nodes[i] = vector<Quadtree*>();
		}
	}
}

void Quadtree::Insert(Entity* entity)
{
	// Insert entity into corresponding nodes
	if (nodes)
	{
		if (nodes[0]->IsContain(entity))
			nodes[0]->Insert(entity);
		if (nodes[1]->IsContain(entity))
			nodes[1]->Insert(entity);
		if (nodes[2]->IsContain(entity))
			nodes[2]->Insert(entity);
		if (nodes[3]->IsContain(entity))
			nodes[3]->Insert(entity);

		return; // Return here to ignore rest.
	}

	// Insert entity into current quadtree
	if (this->IsContain(entity))
		entities_list->push_back(entity);

	// Split and move all objects in list into itfs corresponding nodes
	// Condition: current node region is little bigger than viewport and there's at least two objects in that node
	if (entities_list->size() > MIN_OBJECT_NUMBER_TO_SPLIT && (region.right - region.left) > SCREEN_WIDTH && (region.bottom - region.top) > SCREEN_HEIGHT)
	{
		Split();

		while (!entities_list->empty())
		{
			if (nodes[0]->IsContain(entities_list->back()))
				nodes[0]->Insert(entities_list->back());
			if (nodes[1]->IsContain(entities_list->back()))
				nodes[1]->Insert(entities_list->back());
			if (nodes[2]->IsContain(entities_list->back()))
				nodes[2]->Insert(entities_list->back());
			if (nodes[3]->IsContain(entities_list->back()))
				nodes[3]->Insert(entities_list->back());

			entities_list->pop_back();
		}
	}
}

void Quadtree::Retrieve(vector<Entity*>* return_entities_list, Entity* entity)
{
	if (nodes)
	{
		if (nodes[0]->IsContain(entity))
			nodes[0]->Retrieve(return_entities_list, entity);
		if (nodes[1]->IsContain(entity))
			nodes[1]->Retrieve(return_entities_list, entity);
		if (nodes[2]->IsContain(entity))
			nodes[2]->Retrieve(return_entities_list, entity);
		if (nodes[3]->IsContain(entity))
			nodes[3]->Retrieve(return_entities_list, entity);

		return; // Return here to ignore rest.
	}

	// Add all entities in current region into return_objects_list
	if (this->IsContain(entity))
	{
		for (auto i = entities_list->begin(); i != entities_list->end(); i++)
		{
			// might as well check this if the pointer is right
			if (entity != *i)
				return_entities_list->push_back(*i);
		}
	}
}

void Quadtree::RetrieveFromCamera(vector<Entity*> return_entities_list)
{
	Camera* cam = Camera::GetInstance();
	if (nodes)
	{
		if (nodes[0]->IsInsideCamera())
			nodes[0]->RetrieveFromCamera(return_entities_list);
		if (nodes[1]->IsInsideCamera())
			nodes[1]->RetrieveFromCamera(return_entities_list);
		if (nodes[2]->IsInsideCamera())
			nodes[2]->RetrieveFromCamera(return_entities_list);
		if (nodes[3]->IsInsideCamera())
			nodes[3]->RetrieveFromCamera(return_entities_list);

		return; // Return here to ignore rest.
	}

	// Add all entities in current region into return_entities_list
	if (this->IsInsideCamera())
	{
		for (auto i = entities_list->begin(); i != entities_list->end(); i++)
		{
			return_entities_list.push_back(*i);
		}
	}
}

Quadtree * Quadtree::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Quadtree();
	}
	return __instance;
}
