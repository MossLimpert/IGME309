#include "Octant.h"
using namespace BTX;
//  Octant
uint Octant::m_uOctantCount = 0;
uint Octant::m_uMaxLevel = 3;
uint Octant::m_uIdealEntityCount = 5;
Octant::Octant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
	/*
	* This constructor is meant to be used ONLY on the root node, there is already a working constructor
	* that will take a size and a center to create a new space
	*/
	Init();//Init the default values
	m_uOctantCount = 0;
	m_uMaxLevel = a_nMaxLevel;
	m_uIdealEntityCount = a_nIdealEntityCount;
	m_uID = m_uOctantCount;

	m_pRoot = this;
	m_lChild.clear();

	std::vector<std::vector<std::vector<vector3>>> myVar;

	//create a rigid body that encloses all the objects in this octant, it necessary you will need
	//to subdivide the octant based on how many objects are in it already an how many you IDEALLY
	//want in it, remember each subdivision will create 8 children for this octant but not all children
	//of those children will have children of their own

	//The following is a made-up size, you need to make sure it is measuring all the object boxes in the world

	// go through all entities, get max x, y, z, make vec 3 min and max
	// replace them in push_back below
	float minX = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMinGlobal().x;
	float minY = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMinGlobal().y;
	float minZ = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMinGlobal().z;
	float maxX = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMaxGlobal().x;
	float maxY = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMaxGlobal().y;
	float maxZ = this->m_pEntityMngr->GetEntity(0)->GetRigidBody()->GetMaxGlobal().z;

	//for (int i = 1; i < this->m_pEntityMngr->GetEntityCount(); i++)
	//{
	//	// x min
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().x < minX)
	//	{
	//		minX = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().x;
	//	}
	//	// x max
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().x > maxX)
	//	{
	//		maxX = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().x;
	//	}
	//	// y min
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().y < minY)
	//	{
	//		minY = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().y;
	//	}
	//	// y max
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().y > maxY)
	//	{
	//		maxY = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().y;
	//	}
	//	// z min
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().z < minZ)
	//	{
	//		minZ = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMinGlobal().z;
	//	}
	//	// z max
	//	if (this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().z)
	//	{
	//		maxZ = this->m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetMaxGlobal().z;
	//	}
	//}

	std::vector<vector3> lMinMax;
	//vector3 min = vector3(minX, minY, minZ);
	//vector3 max = vector3(maxX, maxY, maxZ);
	vector3 min = vector3(-40.0f);
	vector3 max = vector3(40.0f);
	lMinMax.push_back(min);
	lMinMax.push_back(max);
	RigidBody pRigidBody = RigidBody(lMinMax);


	//The following will set up the values of the octant, make sure the are right, the rigid body at start
	//is NOT fine, it has made-up values
	m_fSize = pRigidBody.GetHalfWidth().x * 2.0f;
	m_v3Center = pRigidBody.GetCenterLocal();
	m_v3Min = m_v3Center - pRigidBody.GetHalfWidth();
	m_v3Max = m_v3Center + pRigidBody.GetHalfWidth();

	m_uOctantCount++; //When we add an octant we increment the count
	ConstructTree(m_uMaxLevel); //Construct the children
}

bool Octant::IsColliding(uint a_uRBIndex)
{
	//EntityManager* m_pEntityMngr = nullptr; //So we can read the information for each entity

	//vector3 m_v3Center = vector3(0.0f); //Will store the center point of the octant
	//vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the octant
	//vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the octant

	//Octant* m_pParent = nullptr;// Will store the address of the parent of current octant
	//Octant* m_pChild[8] = { nullptr };//Will store the address of the children of the current octant

	//std::vector<uint> m_EntityList; //List of Entities under this octant (their index under Entity Manager)
	// 

	//Get how many objects there are in the world
	uint numObjects = this->m_pEntityMngr->GetEntityCount();


	//If the index given is larger than the number of elements in the bounding object there is no collision
	if (a_uRBIndex > numObjects)
	{
		return false;
	}

	//Entity toCheck = this->m_pEntityMngr->GetEntity(a_uRBIndex);

	//As the Octree will never rotate or scale this collision is as easy as an Axis Alligned Bounding Box
	//  The left edge x-position of [A] must be less than the right edge x-position of [B].
	/*	The right edge x - position of[A] must be greater than the left edge x - position of[B].
		The top edge y - position of[A] must be less than the bottom edge y - position of[B].
		The bottom edge y - position of[A] must be greater than the top edge y - position of[B].*/
	if (this->m_v3Min.x < this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMaxGlobal().x
		&& this->m_v3Max.x > this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMinGlobal().x
		&& this->m_v3Min.y < this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMaxGlobal().y
		&& this->m_v3Max.y > this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMinGlobal().y
		&& this->m_v3Min.z < this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMaxGlobal().z
		&& this->m_v3Max.z > this->m_pEntityMngr->GetEntity(a_uRBIndex)->GetRigidBody()->GetMinGlobal().z)
	{
		return true;
	}

	// CONTAINS AT LEAST METHOD
	// watch THIS when setting breakpoints
	// use private child constructor to make the children
	// use assign id to entity to add obj to octant entity managaer

	//As the Octree will never rotate or scale this collision is as easy as an Axis Alligned Bounding Box
	//  The left edge x-position of [A] must be less than the right edge x-position of [B].
	/*	The right edge x - position of[A] must be greater than the left edge x - position of[B].
		The top edge y - position of[A] must be less than the bottom edge y - position of[B].
		The bottom edge y - position of[A] must be greater than the top edge y - position of[B].*/


		//Get all vectors in global space (the octant ones are already in Global)

	return false; // for the sake of startup code
}
void Octant::Display(uint a_nIndex, vector3 a_v3Color)
{
	// Display the specified octant
	m_pModelMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_pChild[a_nIndex]->GetCenterGlobal()) *
		glm::scale(vector3(this->m_pChild[a_nIndex]->m_fSize)), a_v3Color);
}
void Octant::Display(vector3 a_v3Color)
{
	if (m_uChildren == 0)
	{
		return;
	}

	for (int i = 0; i < m_uChildren; i++)
	{
		this->Display(i, a_v3Color);
	}
	//this is meant to be a recursive method, in starter code will only display the root
	//even if other objects are created
	/*m_pModelMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fSize)), a_v3Color);*/
}
void Octant::PopulateEntity(uint childIndex)
{
	// go through each entity in this octant's entity manager, check if this octant contains it
	for (int i = 0; i < this->m_pEntityMngr->GetEntityCount(); i++)
	{
		bool contains = true;

		// AABB
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMaxGlobal().x < m_pChild[childIndex]->GetMinGlobal().x)
		{
			contains = false;
		}
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMinGlobal().x > m_pChild[childIndex]->GetMaxGlobal().x)
		{
			contains = false;
		}
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMaxGlobal().y < m_pChild[childIndex]->GetMinGlobal().y)
		{
			contains = false;
		}
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMinGlobal().y < m_pChild[childIndex]->GetMaxGlobal().y)
		{
			contains = false;
		}
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMaxGlobal().z < m_pChild[childIndex]->GetMinGlobal().z)
		{
			contains = false;
		}
		if (this->m_pEntityMngr->GetRigidBody(i)->GetMinGlobal().z < m_pChild[childIndex]->GetMaxGlobal().z)
		{
			contains = false;
		}

		// if the entity is in the child's space, add it to the child's entitty manager
		if (contains)
		{
			// get entity id
			String id = this->m_pEntityMngr->GetEntity(i)->GetUniqueID();
			// add to child's entity manager with its model and id
			//m_pChild[childIndex]->m_pEntityMngr->AddEntity(this->m_pEntityMngr->GetModel(i), id);
			//this->m_pEntityMngr->RemoveEntity(id);
			//m_pChild[childIndex]->m_pEntityMngr->AddEntry(this->m_pEntityMngr->GetEntity(i));
			//m_pChild[childIndex]->m_pEntityMngr->AddDimension(id, this->m_uLevel);
			//this->m_EntityList.push_back(i);
		}
	}
}
void Octant::Subdivide(void)
{
	//If this node has reach the maximum depth return without changes
	if (m_uLevel >= m_uMaxLevel)
		return;

	//If this node has been already subdivided return without changes
	if (m_uChildren != 0)
		return;

	//Subdivide the space and allocate 8 children
	float halfSize = this->m_fSize / 2;
	float quarterSize = halfSize / 2;


	// for each one we have to make a new size, and center
	vector3 center = ZERO_V3;

	// Octant::Octant(vector3 a_v3Center, float a_fSize)
	// first child --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x + quarterSize,
		this->m_v3Center.y + quarterSize,
		this->m_v3Center.z - quarterSize
	);
	m_pChild[0] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[0]);
	m_pChild[0]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(0);

	// second child ---------------------------------------------------
	center = vector3(
		this->m_v3Center.x - quarterSize,
		this->m_v3Center.y + quarterSize,
		this->m_v3Center.z - quarterSize
	);
	//Octant second = Octant(center, halfSize);
	m_pChild[1] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[1]);
	m_pChild[1]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(1);

	// third child --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x - quarterSize,
		this->m_v3Center.y - quarterSize,
		this->m_v3Center.z - quarterSize
	);
	m_pChild[2] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[2]);
	m_pChild[2]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(2);

	// fourth --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x + quarterSize,
		this->m_v3Center.y - quarterSize,
		this->m_v3Center.z - quarterSize
	);
	m_pChild[3] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[3]);
	m_pChild[3]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(3);

	// fifth --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x + quarterSize,
		this->m_v3Center.y + quarterSize,
		this->m_v3Center.z + quarterSize
	);
	m_pChild[4] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[4]);
	m_pChild[4]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(4);

	// sixth --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x - quarterSize,
		this->m_v3Center.y + quarterSize,
		this->m_v3Center.z + quarterSize
	);
	m_pChild[5] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[5]);
	m_pChild[5]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(5);

	// seventh --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x - quarterSize,
		this->m_v3Center.y - quarterSize,
		this->m_v3Center.z + quarterSize
	);
	m_pChild[6] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[6]);
	m_pChild[6]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(6);

	// eighth --------------------------------------------------------
	center = vector3(
		this->m_v3Center.x + quarterSize,
		this->m_v3Center.y - quarterSize,
		this->m_v3Center.z + quarterSize
	);
	m_pChild[7] = new Octant(center, halfSize);
	this->m_lChild.push_back(m_pChild[7]);
	m_pChild[7]->m_uLevel = this->m_uLevel + 1;
	// populate its entities
	//PopulateEntity(7);


	this->m_uChildren = 8;

	for (int i = 0; i < this->m_uChildren; i++) {
		this->GetChild(i)->Subdivide();
	}
}
bool Octant::ContainsAtLeast(uint a_nEntities)
{
	int num = this->m_pEntityMngr->GetEntityCount();

	if (a_nEntities < num) {
		return true;
	}
	//You need to check how many entity objects live within this octant
	return false; //return something for the sake of start up code
}
void Octant::AssignIDtoEntity(void)
{
	if (IsLeaf() == false)
	{
		for (int i = 0; i < m_uChildren; i++)
		{
			GetChild(i)->AssignIDtoEntity();
		}
	}
	else
	{
		uint count = m_pEntityMngr->GetEntityCount();
		for (int i = 0; i < count; i++)
		{
			if (IsColliding(i) == true)
			{
				m_EntityList.push_back(i);
				m_pEntityMngr->AddDimension(i, m_uID);
			}
		}
	}
	//Recursive method
	//Have to traverse the tree and make sure to tell the entity manager
	//what octant (space) each object is at
	//m_pEntityMngr->AddDimension(0, m_uID);//example only, take the first entity and tell it its on this space
	
}
//-------------------------------------------------------------------------------------------------------------------
// You can assume the following is fine and does not need changes, you may add onto it but the code is fine as is
// in the proposed solution.
void Octant::Init(void)
{
	m_uChildren = 0;

	m_fSize = 0.0f;

	m_uID = m_uOctantCount;
	m_uLevel = 0;

	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	m_pRoot = nullptr;
	m_pParent = nullptr;
	for (uint n = 0; n < 8; n++)
	{
		m_pChild[n] = nullptr;
	}
}
void Octant::Swap(Octant& other)
{
	std::swap(m_uChildren, other.m_uChildren);

	std::swap(m_fSize, other.m_fSize);
	std::swap(m_uID, other.m_uID);
	std::swap(m_pRoot, other.m_pRoot);
	std::swap(m_lChild, other.m_lChild);

	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_v3Min, other.m_v3Min);
	std::swap(m_v3Max, other.m_v3Max);

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	std::swap(m_uLevel, other.m_uLevel);
	std::swap(m_pParent, other.m_pParent);
	for (uint i = 0; i < 8; i++)
	{
		std::swap(m_pChild[i], other.m_pChild[i]);
	}
}
void Octant::Release(void)
{
	//this is a special kind of release, it will only happen for the root
	if (m_uLevel == 0)
	{
		KillBranches();
	}
	m_uChildren = 0;
	m_fSize = 0.0f;
	m_EntityList.clear();
	m_lChild.clear();
}
void Octant::ConstructTree(uint a_nMaxLevel)
{
	//If this method is tried to be applied to something else
	//other than the root, don't.
	if (m_uLevel != 0)
		return;

	m_uMaxLevel = a_nMaxLevel; //Make sure you mark which is the maximum level you are willing to reach
	m_uOctantCount = 1;// We will always start with one octant

	//If this was initialized before make sure its empty
	m_EntityList.clear();//Make sure the list of entities inside this octant is empty
	KillBranches();
	m_lChild.clear();

	//If we have more entities than those that we ideally want in this octant we subdivide it
	if (ContainsAtLeast(m_uIdealEntityCount))
	{
		Subdivide();
	}
	AssignIDtoEntity();//Add octant ID to Entities
	ConstructList();//construct the list of objects
}
//The big 3
Octant::Octant(vector3 a_v3Center, float a_fSize)
{
	//Will create the octant object based on the center and size but will not construct children
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	m_v3Min = m_v3Center - (vector3(m_fSize) / 2.0f);
	m_v3Max = m_v3Center + (vector3(m_fSize) / 2.0f);

	m_uOctantCount++;
}
Octant::Octant(Octant const& other)
{
	m_uChildren = other.m_uChildren;
	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_fSize = other.m_fSize;
	m_uID = other.m_uID;
	m_uLevel = other.m_uLevel;
	m_pParent = other.m_pParent;

	m_pRoot, other.m_pRoot;
	m_lChild, other.m_lChild;

	m_pModelMngr = ModelManager::GetInstance();
	m_pEntityMngr = EntityManager::GetInstance();

	for (uint i = 0; i < 8; i++)
	{
		m_pChild[i] = other.m_pChild[i];
	}
}
Octant& Octant::operator=(Octant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Octant temp(other);
		Swap(temp);
	}
	return *this;
}
Octant::~Octant() { Release(); };
//Accessors
float Octant::GetSize(void) { return m_fSize; }
vector3 Octant::GetCenterGlobal(void) { return m_v3Center; }
vector3 Octant::GetMinGlobal(void) { return m_v3Min; }
vector3 Octant::GetMaxGlobal(void) { return m_v3Max; }
uint Octant::GetOctantCount(void) { return m_uOctantCount; }
bool Octant::IsLeaf(void) { return m_uChildren == 0; }
Octant* Octant::GetParent(void) { return m_pParent; }
//--- other methods
Octant* Octant::GetChild(uint a_nChild)
{
	//if its asking for more than the 8th children return nullptr, as we don't have one
	if (a_nChild > 7) return nullptr;
	return m_pChild[a_nChild];
}
void Octant::KillBranches(void)
{
	/*This method has recursive behavior that is somewhat hard to explain line by line but
	it will traverse the whole tree until it reaches a node with no children and
	once it returns from it to its parent it will kill all of its children, recursively until
	it reaches back the node that called it.*/
	for (uint nIndex = 0; nIndex < m_uChildren; nIndex++)
	{
		m_pChild[nIndex]->KillBranches();
		delete m_pChild[nIndex];
		m_pChild[nIndex] = nullptr;
	}
	m_uChildren = 0;
}
void Octant::DisplayLeaves(vector3 a_v3Color)
{
	/*
	* Recursive method
	* it will traverse the tree until it find leaves and once found will draw them
	*/
	uint nLeafs = m_lChild.size(); //get how many children this will have (either 0 or 8)
	for (uint nChild = 0; nChild < nLeafs; nChild++)
	{
		m_lChild[nChild]->DisplayLeaves(a_v3Color);
	}
	//Draw the cube
	m_pModelMngr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, m_v3Center) *
		glm::scale(vector3(m_fSize)), a_v3Color);
}
void Octant::ClearEntityList(void)
{
	/*
	* Recursive method
	* It will traverse the tree until it find leaves and once found will clear its content
	*/
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->ClearEntityList();
	}
	m_EntityList.clear();
}
void Octant::ConstructList(void)
{
	/*
	* Recursive method
	* It will traverse the tree adding children
	*/
	for (uint nChild = 0; nChild < m_uChildren; nChild++)
	{
		m_pChild[nChild]->ConstructList();
	}
	//if we find a non-empty child add it to the tree
	if (m_EntityList.size() > 0)
	{
		m_pRoot->m_lChild.push_back(this);
	}
}
