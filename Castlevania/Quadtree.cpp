#include "Quadtree.h"

void Quadtree::Split()
{
	this->level, this->region;
	long regionWidth = this->region->right - this->region->left;
	long regionHeight = this->region->bottom - this->region->top;

	RECT tl, tr, bl, br;
	tl.left = this->region->left;
	tl.top = this->region->top;
	tl.right = this->region->left + regionWidth / 2;
	tl.bottom = this->region->top + regionHeight / 2;

	tr.left = this->region->left + regionWidth / 2;
	tr.top = this->region->top;
	tr.right = this->region->right;
	tr.bottom = this->region->top + regionHeight / 2;

	bl.left = this->region->left;
	bl.top = this->region->top + regionHeight / 2;
	bl.right = this->region->left + regionWidth / 2;
	bl.bottom = this->region->bottom;

	br.left = this->region->left + regionWidth / 2;
	br.top = this->region->top + regionHeight / 2;
	br.right = this->region->right;
	br.bottom = this->region->bottom;

	if (this->nodes == nullptr)
	{
		this->nodes = new vector<Quadtree*>(4);
	}
	this->nodes->at(0) = new Quadtree(this->level + 1,
		tl);
	this->nodes->at(1) = new Quadtree(this->level + 1,
		tr);
	this->nodes->at(2) = new Quadtree(this->level + 1,
		bl);
	this->nodes->at(3) = new Quadtree(this->level + 1,
		br);
}
Quadtree::Quadtree(int pLevel, RECT pBounds)
{
	this->level = pLevel;
	this->entities_list = new vector<Entity*>();
	this->region = &pBounds;
	this->nodes = new vector<Quadtree*>(4);
}
Quadtree::~Quadtree()
{
	delete this->region;
	delete this->entities_list;
	delete this->nodes;
}
int Quadtree::getIndex(RECT * pRect)
{
	int index = -1;
	long regionWidth = this->region->right - this->region->left;
	long regionHeight = this->region->bottom - this->region->top;
	double verticalMidpoint = this->region->left + (regionWidth / 2);
	double horizontalMidpoint = this->region->top + (regionHeight / 2);

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
	this->entities_list->clear();

	for (int i = 0; i < this->nodes->size(); i++)
	{
		// replace nullptr with empty vector with same type
		if (this->nodes->at(i) != nullptr)
		{
			this->nodes->at(i)->Clear();
			this->nodes->at(i) = nullptr;
		}
	}
}

// check current node, find the correct index and add to the this->entities_list of node[index]
// Split
void Quadtree::Insert(Entity* entity)
{
	RECT *pRect = &entity->GetTriggerZone();
	if (this->nodes->at(0) != nullptr)
	{
		int index = getIndex(pRect);

		if (index != -1)
		{
			this->nodes->at(index)->Insert(entity);

			return;
		}
	}

	this->entities_list->push_back(entity);

	if (this->entities_list->size() > MAX_OBJECTS && this->level < MAX_LEVELS)
	{
		if (this->nodes->at(0) == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < this->entities_list->size())
		{
			int index = getIndex(&this->entities_list->at(i)->GetTriggerZone());
			if (index != -1)
			{
				this->nodes->at(index)->Insert(this->entities_list->at(i));
				this->entities_list->erase(this->entities_list->begin() + i);
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
	if (index != -1 && this->nodes->at(0) != nullptr)
	{
		this->nodes->at(index)->Retrieve(return_entities_list, entity);
	}

	return_entities_list->insert(return_entities_list->end(), this->entities_list->begin(), this->entities_list->end());
}

void Quadtree::RetrieveFromCamera(vector<Entity*> &return_entities_list)
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
	if (index != -1 && this->nodes->at(0) != nullptr)
	{
		this->nodes->at(index)->RetrieveFromCamera(return_entities_list);
	}

	return_entities_list.insert(return_entities_list.end(), this->entities_list->begin(), this->entities_list->end());
}
