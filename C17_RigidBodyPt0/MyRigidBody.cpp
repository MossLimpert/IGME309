#include "MyRigidBody.h"
using namespace BTX;
//Accessors
bool MyRigidBody::GetVisible(void) { return m_bVisible; }
float MyRigidBody::GetRadius(void) { return m_fRadius; }
vector3 MyRigidBody::GetColor(void) { return m_v3Color; }
void MyRigidBody::SetColor(vector3 a_v3Color) { m_v3Color = a_v3Color; }
vector3 MyRigidBody::GetCenterLocal(void) { return m_v3Center; }
vector3 MyRigidBody::GetMinLocal(void) { return m_v3MinL; }
vector3 MyRigidBody::GetMaxLocal(void) { return m_v3MaxL; }
vector3 MyRigidBody::GetCenterGlobal(void){	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f)); }
vector3 MyRigidBody::GetMinGlobal(void) { return m_v3MinG; }
vector3 MyRigidBody::GetMaxGlobal(void) { return m_v3MaxG; }
vector3 MyRigidBody::GetHalfWidth(void) { return m_v3HalfWidth; }
matrix4 MyRigidBody::GetModelMatrix(void) { return m_m4ToWorld; }}
void MyRigidBody::SetModelMatrix(matrix4 a_m4ModelMatrix) { 
	
	m_m4ToWorld = a_m4ModelMatrix; 
	// check axis re-aligned bounding boxes

	// find max for x y z, divide by 2, and average
	std::vector<vector3> cornerList;
	cornerList.push_back(vector3(m_v3MinL.x, m_v3MinL.y, m_v3MinL.z));
	cornerList.push_back(vector3(m_v3MinL.x, m_v3MinL.y, m_v3MaxL.z));
	cornerList.push_back(vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MinL.z));
	cornerList.push_back(vector3(m_v3MinL.x, m_v3MaxL.y, m_v3MaxL.z));
	cornerList.push_back(vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z));
	cornerList.push_back(vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z));
	cornerList.push_back(vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z));
	cornerList.push_back(vector3(m_v3MaxL.x, m_v3MinL.y, m_v3MinL.z));


}
//Allocation
void MyRigidBody::Init(void)
{
	m_pMeshMngr = ModelManager::GetInstance();
	m_bVisible = true;

	m_fRadius = 0.0f;

	m_v3Color = C_WHITE;

	m_v3Center = ZERO_V3;
	m_v3MinL = ZERO_V3;
	m_v3MaxL = ZERO_V3;

	m_v3MinG = ZERO_V3;
	m_v3MaxG = ZERO_V3;

	m_v3HalfWidth = ZERO_V3;

	m_m4ToWorld = IDENTITY_M4;
}
void MyRigidBody::Swap(MyRigidBody& other)
{
	std::swap(m_pMeshMngr , other.m_pMeshMngr);
	std::swap(m_bVisible , other.m_bVisible);

	std::swap(m_fRadius, other.m_fRadius);

	std::swap(m_v3Color , other.m_v3Color);

	std::swap(m_v3Center , other.m_v3Center);
	std::swap(m_v3MinL , other.m_v3MinL);
	std::swap(m_v3MaxL , other.m_v3MaxL);

	std::swap(m_v3MinG , other.m_v3MinG);
	std::swap(m_v3MaxG , other.m_v3MaxG);

	std::swap(m_v3HalfWidth , other.m_v3HalfWidth);

	std::swap(m_m4ToWorld , other.m_m4ToWorld);
}
void MyRigidBody::Release(void)
{
	m_pMeshMngr = nullptr;
}
//The big 3
MyRigidBody::MyRigidBody(std::vector<vector3> a_pointList)
{
	Init();
	uint uCount = a_pointList.size();

	if (uCount < 1)
		return;

	//Finding the center by average (WRONG)
	m_v3Center = a_pointList[0];
	for (uint i = 1; i < uCount; i++)
	{
		m_v3Center += a_pointList[i];
	}
	m_v3Center /= static_cast<float> (uCount);

	//Finding the center by max and min

	m_v3MinL = m_v3MaxL = a_pointList[0];
	for (uint i = 1; i < uCount; i++)
	{
		if (m_v3MinL.x > a_pointList[i].x)
			m_v3MinL.x = a_pointList[i].x;
		if (m_v3MinL.y > a_pointList[i].y)
			m_v3MinL.y = a_pointList[i].y;
		if (m_v3MinL.z > a_pointList[i].z)
			m_v3MinL.z = a_pointList[i].z;

		if (m_v3MaxL.x < a_pointList[i].x)
			m_v3MaxL.x = a_pointList[i].x;
		if (m_v3MaxL.y < a_pointList[i].y)
			m_v3MaxL.y = a_pointList[i].y;
		if (m_v3MaxL.z < a_pointList[i].z)
			m_v3MaxL.z = a_pointList[i].z;
	}
	m_v3Center = (m_v3MaxL + m_v3MinL) / 2.0f;
	
	//Finding largest distance from center to any point
	m_fRadius = 0.0f;
	for (uint i = 0; i < uCount; i++)
	{
		float fDistance = glm::distance(m_v3Center, a_pointList[i]);
		if (m_fRadius < fDistance)
			m_fRadius = fDistance;

		//m_fRadius = glm::max(m_fRadius, fDistance);
	}
	m_fRadius = glm::distance(m_v3Center, m_v3MaxL);//Bounding Sphere of bounting box
	m_v3HalfWidth = (m_v3MaxL - m_v3MinL) / 2.0f;


}
MyRigidBody::MyRigidBody(MyRigidBody const& other)
{
	m_pMeshMngr = m_pMeshMngr;
	m_bVisible = m_bVisible;

	m_fRadius = m_fRadius;

	m_v3Color = m_v3Color;

	m_v3Center = m_v3Center;
	m_v3MinL = m_v3MinL;
	m_v3MaxL = m_v3MaxL;

	m_v3MinG = m_v3MinG;
	m_v3MaxG = m_v3MaxG;

	m_v3HalfWidth = m_v3HalfWidth;

	m_m4ToWorld = m_m4ToWorld;
}
MyRigidBody& MyRigidBody::operator=(MyRigidBody const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		MyRigidBody temp(other);
		Swap(temp);
	}
	return *this;
}
MyRigidBody::~MyRigidBody(){Release();};

//--- Non Standard Singleton Methods
void MyRigidBody::AddToRenderList(void)
{
	if (!m_bVisible)
		return;
	matrix4 m4Transform = m_m4ToWorld * glm::translate(vector3(m_v3Center));
	m4Transform = m4Transform * glm::scale(vector3(m_v3HalfWidth * 2));
	//m_pMeshMngr->AddWireSphereToRenderList(m4Transform, m_v3Color);
	m_pMeshMngr->AddWireCubeToRenderList(m4Transform, m_v3Color);
}
bool MyRigidBody::IsColliding(MyRigidBody* const other)
{
	bool bColliding = true;

	vector3 thisCenter = m_m4ToWorld * vector4(this->m_v3Center, 1.0f);
	vector3 otherCenter = m_m4ToWorld * vector4(other->m_v3Center, 1.0f);
	float f_Sum = glm::distance(thisCenter, otherCenter);
	float f_Radii = this->m_fRadius + other->m_fRadius;
	bColliding = f_Radii > f_Sum;

	bColliding = false;


	//vector4 model = this->m_m4ToWorld;

	// get corners
	// globalize max and min
	// 

	// box around box. recalc every update
	// AABB
	// ARBB
	// OBB
	// BS

	this->m_v3MinG = this->m_m4ToWorld * vector4(this->m_v3MinG, 1.0f);
	this->m_v3MaxG = this->m_m4ToWorld * vector4(this->m_v3MaxG, 1.0f);

	other->m_v3MinG = other->m_m4ToWorld * vector4(other->m_v3MinG, 1.0f);
	other->m_v3MaxG = other->m_m4ToWorld * vector4(other->m_v3MaxG, 1.0f);

	

	if (m_v3MinG.x > other->m_v3MaxG.x)
	{
		bColliding = false;
	}
	if (m_v3MinG.x < other->m_v3MaxG.x)
	{
		bColliding = false;
	}

	if (m_v3MinG.y > other->m_v3MaxG.y)
	{
		bColliding = false;
	}
	if (m_v3MinG.y < other->m_v3MaxG.y)
	{
		bColliding = false;
	}

	if (m_v3MinG.z > other->m_v3MaxG.z)
	{
		bColliding = false;
	}
	if (m_v3MinG.z < other->m_v3MaxG.z)
	{
		bColliding = false;
	}


	if (bColliding) 
	{
		this->m_v3Color = vector3(1.0f, 0.0f, 0.0f);
		other->m_v3Color = vector3(1.0f, 0.0f, 0.0f);
	}
	


	return false;
}