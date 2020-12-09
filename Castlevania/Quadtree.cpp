#include "Quadtree.h"

//Quadtree* Quadtree::__instance = NULL;
bool Quadtree::IsContain(Entity * entity)
{
	float l, t, r, b;
	entity->GetTriggerZone(l,t,r,b);

	return !(r < region->left ||
		b < region->top ||
		l > region->right ||
		t > region->bottom);
}
bool Quadtree::IsInsideCamera()
{
	Camera* cam = Camera::GetInstance();
	float l, t, r, b;
	l = cam->GetCamX();
	t = cam->GetCamY();
	r = l + 800;
	b = t + 508;
	return !(r < region->left ||
		b < region->top ||
		l > region->right ||
		t > region->bottom);
}
void Quadtree::Split()
{
	nodes = new vector<Quadtree*>(4);

	long regionWidth = region->right - region->left;
	long regionHeight = region->bottom - region->top;

	RECT tl, tr, bl, br;
	tl.left = region->left;
	tl.top = region->top;
	tl.right = region->left + regionWidth / 2;
	tl.bottom = region->top + regionHeight / 2;
	nodes->at(0) = new Quadtree(level + 1,
		&tl);
	tr.left = region->left + regionWidth / 2;
	tr.top = region->top;
	tr.right = region->right;
	tr.bottom = region->top + regionHeight / 2;
	nodes->at(1) = new Quadtree(level + 1,
		&tr);
	bl.left = region->left;
	bl.top = region->top + regionHeight / 2;
	bl.right = region->left + regionWidth / 2;
	bl.bottom = region->bottom;
	nodes->at(2) = new Quadtree(level + 1,
		&bl);
	br.left = region->left + regionWidth / 2;
	br.top = region->top + regionHeight / 2;
	br.right = region->right;
	br.bottom = region->bottom;
	nodes->at(3) = new Quadtree(level + 1,
		&br);
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
int Quadtree::getIndex(RECT * pRect)
{
	int index = -1;
	long regionWidth = region->right - region->left;
	long regionHeight = region->bottom - region->top;
	double verticalMidpoint = region->left + (regionWidth / 2);
	double horizontalMidpoint = region->top + (regionHeight / 2);

	long pRectWidth = pRect->right - pRect->left;
	long pRectHeight = pRect->bottom - pRect->top;

	// Object can completely fit within the top quadrants
	bool topQuadrant = (pRect->top < horizontalMidpoint && pRect->top + pRectHeight < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (pRect->top > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (pRect->left < verticalMidpoint && pRect->left + pRectWidth < verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (pRect->left > verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}
	}
	return index;
}
void Quadtree::Clear()
{
	entities_list->clear();

	for (int i = 0; i < nodes->size(); i++)
	{
		// replace nullptr with empty vector with same type
		if (nodes->at(i) != nullptr)
		{
			nodes->at(i)->Clear();
			nodes->at(i) = nullptr;
		}
	}
}

void Quadtree::Insert(Entity* entity)
{
	RECT *pRect = &entity->GetTriggerZone();
	if (nodes->at(0) != nullptr)
	{
		int index = getIndex(pRect);

		if (index != -1)
		{
			nodes->at(index)->Insert(entity);

			return;
		}
	}

	entities_list->push_back(entity);

	if (entities_list->size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes->at(0) == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < entities_list->size())
		{
			int index = getIndex(&entities_list->at(i)->GetTriggerZone());
			if (index != -1)
			{
				nodes->at(index)->Insert(entities_list->at(i));
				entities_list->erase(entities_list->begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void Quadtree::Retrieve(vector<Entity*>* return_entities_list, Entity* entity)
{
	RECT* pRect = &entity->GetTriggerZone();
	int index = getIndex(pRect);
	if (index != -1 && nodes->at(0) != nullptr)
	{
		nodes->at(index)->Retrieve(return_entities_list, entity);
	}

	return_entities_list->insert(return_entities_list->end(), entities_list->begin(), entities_list->end());
}

void Quadtree::RetrieveFromCamera(vector<Entity*> return_entities_list)
{
	Camera* cam = Camera::GetInstance();
	float l, t, r, b;
	l = cam->GetCamX();
	t = cam->GetCamY();
	r = l + 800;
	b = t + 508;
	RECT pRect;
	pRect.left = l;
	pRect.top = t;
	pRect.right = r;
	pRect.bottom = b;
	int index = getIndex(&pRect);
	if (index != -1 && nodes->at(0) != nullptr)
	{
		nodes->at(index)->RetrieveFromCamera(return_entities_list);
	}

	return_entities_list.insert(return_entities_list.end(), entities_list->begin(), entities_list->end());
}

//void Quadtree::RetrieveFromCamera(vector<Entity*> return_entities_list)
//{
//	Camera* cam = Camera::GetInstance();
//	if (nodes)
//	{
//		if (nodes[0]->IsInsideCamera())
//			nodes[0]->RetrieveFromCamera(return_entities_list);
//		if (nodes[1]->IsInsideCamera())
//			nodes[1]->RetrieveFromCamera(return_entities_list);
//		if (nodes[2]->IsInsideCamera())
//			nodes[2]->RetrieveFromCamera(return_entities_list);
//		if (nodes[3]->IsInsideCamera())
//			nodes[3]->RetrieveFromCamera(return_entities_list);
//
//		return; // Return here to ignore rest.
//	}
//
//	// Add all entities in current region into return_entities_list
//	if (this->IsInsideCamera())
//	{
//		for (auto i = entities_list->begin(); i != entities_list->end(); i++)
//		{
//			return_entities_list.push_back(*i);
//		}
//	}
//}

//Quadtree * Quadtree::GetInstance()
//{
//	if (__instance == NULL)
//	{
//		__instance = new Quadtree();
//	}
//	return __instance;
//}
