#include "Quadtree.h"

Quadtree* Quadtree::__instance = NULL;
bool Quadtree::IsContain(CGameObject * object)
{
	float l, t, r, b;
	object->GetBoundingBox(l,t,r,b);

	return !(r < m_region->left ||
		b < m_region->top ||
		l > m_region->right ||
		t > m_region->bottom);
}
void Quadtree::Split()
{
	m_nodes = new Quadtree*[4];

	long regionWidth = m_region->right - m_region->left;
	long regionHeight = m_region->bottom - m_region->top;

	RECT tl, tr, bl, br;
	tl.left = m_region->left;
	tl.top = m_region->top;
	tl.right = m_region->left + regionWidth / 2;
	tl.bottom = m_region->top + regionHeight / 2;
	m_nodes[0] = new Quadtree(m_level + 1,
		tl);
	tr.left = m_region->left + regionWidth / 2;
	tr.top = m_region->top;
	tr.right = m_region->right;
	tr.bottom = m_region->top + regionHeight / 2;
	m_nodes[1] = new Quadtree(m_level + 1,
		tr);
	bl.left = m_region->left;
	bl.top = m_region->top + regionHeight / 2;
	bl.right = m_region->left + regionWidth / 2;
	bl.bottom = m_region->bottom;
	m_nodes[2] = new Quadtree(m_level + 1,
		bl);
	br.left = m_region->left + regionWidth / 2;
	br.top = m_region->top + regionHeight / 2;
	br.right = m_region->right;
	br.bottom = m_region->bottom;
	m_nodes[3] = new Quadtree(m_level + 1,
		br);
}
Quadtree::Quadtree()
{
	m_level = 1;
	m_region->top = 0;
	m_region->left = 0;
	m_region->bottom = 600;
	m_region->right = 800;
	m_objects_list = NULL;
	m_nodes = NULL;
}
Quadtree::Quadtree(int level, RECT region)
{
	m_level = level;
	m_region->bottom = region.bottom;
	m_region->top = region.top;
	m_region->left = region.left;
	m_region->right = region.right;
}
Quadtree::~Quadtree()
{
}
void Quadtree::Clear()
{
	// Clear all nodes
	if (m_nodes)
	{
		for (int i = 0; i < 4; i++)
		{
			m_nodes[i]->Clear();
			delete m_nodes[i];
		}
		delete[] m_nodes;
	}

	// Clear current Quadtree
	m_objects_list->clear();

	delete m_objects_list;
	delete m_region;
}

void Quadtree::Insert(CGameObject* entity)
{
	// Insert entity into corresponding nodes
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(entity))
			m_nodes[0]->Insert(entity);
		if (m_nodes[1]->IsContain(entity))
			m_nodes[1]->Insert(entity);
		if (m_nodes[2]->IsContain(entity))
			m_nodes[2]->Insert(entity);
		if (m_nodes[3]->IsContain(entity))
			m_nodes[3]->Insert(entity);

		return; // Return here to ignore rest.
	}

	// Insert entity into current quadtree
	if (this->IsContain(entity))
		m_objects_list->push_back(entity);

	// Split and move all objects in list into itfs corresponding nodes
	// Condition: current node region is little bigger than viewport and there's at least two objects in that node
	if (m_objects_list->size() > MIN_OBJECT_NUMBER_TO_SPLIT && (m_region->right - m_region->left) > SCREEN_WIDTH && (m_region->bottom - m_region->top) > SCREEN_HEIGHT)
	{
		Split();

		while (!m_objects_list->empty())
		{
			if (m_nodes[0]->IsContain(m_objects_list->back()))
				m_nodes[0]->Insert(m_objects_list->back());
			if (m_nodes[1]->IsContain(m_objects_list->back()))
				m_nodes[1]->Insert(m_objects_list->back());
			if (m_nodes[2]->IsContain(m_objects_list->back()))
				m_nodes[2]->Insert(m_objects_list->back());
			if (m_nodes[3]->IsContain(m_objects_list->back()))
				m_nodes[3]->Insert(m_objects_list->back());

			m_objects_list->pop_back();
		}
	}
}

void Quadtree::Retrieve(vector<CGameObject*>* return_objects_list, CGameObject* entity)
{
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(entity))
			m_nodes[0]->Retrieve(return_objects_list, entity);
		if (m_nodes[1]->IsContain(entity))
			m_nodes[1]->Retrieve(return_objects_list, entity);
		if (m_nodes[2]->IsContain(entity))
			m_nodes[2]->Retrieve(return_objects_list, entity);
		if (m_nodes[3]->IsContain(entity))
			m_nodes[3]->Retrieve(return_objects_list, entity);

		return; // Return here to ignore rest.
	}

	// Add all entities in current region into return_objects_list
	if (this->IsContain(entity))
	{
		for (auto i = m_objects_list->begin(); i != m_objects_list->end(); i++)
		{
			// might as well check this if the pointer is right
			if (entity != *i)
				return_objects_list->push_back(*i);
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
