#include "Quadtree.h"
#include "Define.h"

void Quadtree::Split()
{
	level, region;
	long regionWidth = region.right - region.left;
	long regionHeight = region.bottom - region.top;

	RECT tl, tr, bl, br;
	tl.left = region.left;
	tl.top = region.top;
	tl.right = region.left + regionWidth / 2;
	tl.bottom = region.top + regionHeight / 2;

	tr.left = region.left + regionWidth / 2;
	tr.top = region.top;
	tr.right = region.right;
	tr.bottom = region.top + regionHeight / 2;

	bl.left = region.left;
	bl.top = region.top + regionHeight / 2;
	bl.right = region.left + regionWidth / 2;
	bl.bottom = region.bottom;

	br.left = region.left + regionWidth / 2;
	br.top = region.top + regionHeight / 2;
	br.right = region.right;
	br.bottom = region.bottom;

	if (nodes.empty())
	{
		nodes = vector<Quadtree*>(4);
	}
	nodes.at(0) = new Quadtree(level + 1,
		tl);
	nodes.at(1) = new Quadtree(level + 1,
		tr);
	nodes.at(2) = new Quadtree(level + 1,
		bl);
	nodes.at(3) = new Quadtree(level + 1,
		br);
}
Quadtree::Quadtree(int pLevel, RECT pBounds)
{
	level = pLevel;
	entities_list = vector<Entity*>();
	region = pBounds;
	nodes = vector<Quadtree*>(4);
}
Quadtree::~Quadtree()
{
	//delete region;
	//delete entities_list;
	//delete nodes;
}

//OUTPUT: an array of quadrant indexes
vector<int> Quadtree::getIndexesForCamera(RECT * pRect)
{
	vector<int> indexes = vector<int>();
	long regionWidth = region.right - region.left;
	long regionHeight = region.bottom - region.top;
	double verticalMidpoint = region.left + (regionWidth / 2);
	double horizontalMidpoint = region.top + (regionHeight / 2);

	long pRectWidth = pRect->right - pRect->left;
	long pRectHeight = pRect->bottom - pRect->top;

	// Object can completely fit within the top quadrants
	//bool topQuadrant = (pRect->top < horizontalMidpoint && pRect->top + pRectHeight < horizontalMidpoint);
	bool topHalf = ((pRect->top <= region.top && pRect->bottom >= region.top) || (pRect->top >= region.top && pRect->top <= horizontalMidpoint));
	// Object can completely fit within the bottom quadrants
	//bool bottomQuadrant = (pRect->top > horizontalMidpoint);
	bool bottomHalf = ((pRect->bottom >= region.bottom && pRect->top <= region.bottom) || (pRect->bottom <= region.bottom && pRect->bottom >= horizontalMidpoint));
	bool leftHalf = ((pRect->left <= region.left && pRect->right >= region.left) || (pRect->left >= region.left && pRect->left <= verticalMidpoint));
	bool rightHalf = ((pRect->right >= region.right && pRect->left <= region.right) || (pRect->right <= region.right && pRect->right >= horizontalMidpoint));

	// Object can completely fit within the left quadrants
	if (leftHalf && topHalf)
	{
		indexes.push_back(0);
	}
	if (leftHalf && bottomHalf)
	{
		indexes.push_back(2);
	}
	// Object can completely fit within the right quadrants
	if (rightHalf && topHalf)
	{
		indexes.push_back(1);
	}
	if (rightHalf && bottomHalf)
	{
		indexes.push_back(3);
	}
	return indexes;
}
int Quadtree::getIndex(RECT * pRect)
{
	int index = -1;
	long regionWidth = region.right - region.left;
	long regionHeight = region.bottom - region.top;
	double verticalMidpoint = region.left + (regionWidth / 2);
	double horizontalMidpoint = region.top + (regionHeight / 2);

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
			index = 0;
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
			index = 1;
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
	entities_list.clear();

	for (int i = 0; i < nodes.size(); i++)
	{
		// replace nullptr with empty vector with same type
		if (nodes.at(i) != nullptr)
		{
			nodes.at(i)->Clear();
			nodes.at(i) = nullptr;
		}
	}
}

// check current node, find the correct index and add to the entities_list of node[index]
// Split
void Quadtree::Insert(Entity* entity)
{
	RECT *pRect = &entity->GetTriggerZone();
	if (nodes.at(0) != nullptr)
	{
		int index = getIndex(pRect);

		if (index != -1)
		{
			nodes.at(index)->Insert(entity);

			return;
		}
	}

	entities_list.push_back(entity);

	if (entities_list.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes.at(0) == nullptr)
		{
			Split();
		}

		int i = 0;
		while (i < entities_list.size())
		{
			int index = getIndex(&entities_list.at(i)->GetTriggerZone());
			if (index != -1)
			{
				nodes.at(index)->Insert(entities_list.at(i));
				entities_list.erase(entities_list.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

//void Quadtree::Retrieve(vector<Entity*>* return_entities_list, Entity* entity)
//{
//	RECT* pRect = &entity->GetTriggerZone();
//	vector<int> indexes = getIndex(pRect);
//	if (!indexes.empty() && nodes.at(0) != nullptr)
//	{
//		for (int i = 0; i < indexes.size(); i++)
//		{
//			int index = indexes[i];
//			nodes.at(index)->Retrieve(return_entities_list, entity);
//		}
//	}
//
//	return_entities_list->insert(return_entities_list->end(), entities_list.begin(), entities_list.end());
//}

void Quadtree::RetrieveFromCamera(vector<Entity*> &return_entities_list)
{
	Camera* cam = Camera::GetInstance();
	float l, t, r, b;
	l = cam->GetCamX();
	t = cam->GetCamY();
	r = l + SCREEN_WIDTH;
	b = t + SCREEN_HEIGHT;
	RECT pRect;
	pRect.left = l;
	pRect.top = t;
	pRect.right = r;
	pRect.bottom = b;
	vector<int> indexes = getIndexesForCamera(&pRect);
	if (!indexes.empty() && nodes.at(0) != nullptr)
	{
		for (int i = 0; i < indexes.size(); i++)
		{

			int index = indexes[i];
			nodes.at(index)->RetrieveFromCamera(return_entities_list);
		}
	}

	return_entities_list.insert(return_entities_list.end(), entities_list.begin(), entities_list.end());
}
