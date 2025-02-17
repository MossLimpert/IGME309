#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> circle;
	vector3 pointyEnd = vector3(0.0f, 0.0f, a_fHeight);
	GLfloat currentAngle = 0;
	GLfloat changeInAngle = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------
	// add circle verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle), sin(currentAngle), 0.0f);
		currentAngle += changeInAngle;
		circle.push_back(temp);
	}

	// draw circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(ZERO_V3, circle[(i + 1) % a_nSubdivisions], circle[i]);
	}

	// connect circle to point using tri
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(circle[i], circle[(i + 1) % a_nSubdivisions], pointyEnd);
	}


	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> circle1;
	std::vector<vector3> circle2;
	GLfloat currentAngle = 0;
	GLfloat changeInAngle = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// add bottom circle verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle), sin(currentAngle), 0.0f);
		currentAngle += changeInAngle;
		circle1.push_back(temp);
	}
	// add top circle verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle), sin(currentAngle), a_fHeight);
		currentAngle += changeInAngle;
		circle2.push_back(temp);
	}

	// draw top circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(ZERO_V3, circle1[(i + 1) % a_nSubdivisions], circle1[i]);
	}
	// draw bottom circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(vector3(0.0f, 0.0f, a_fHeight), circle2[i], circle2[(i + 1) % a_nSubdivisions]);
	}
	// connect circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(circle1[i], circle1[(i + 1) % a_nSubdivisions], circle2[i], circle2[(i + 1) % a_nSubdivisions]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> bottomCircleOuter;
	std::vector<vector3> bottomCircleInner;
	std::vector<vector3> topCircleOuter;
	std::vector<vector3> topCircleInner;
	GLfloat currentAngle = 0;
	GLfloat changeInAngle = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------
	// add bottom circle OUTER verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle) * a_fOuterRadius, sin(currentAngle) * a_fOuterRadius, 0.0f);
		currentAngle += changeInAngle;
		bottomCircleOuter.push_back(temp);
	}
	// add bottom circler INNER verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle) * a_fInnerRadius, sin(currentAngle) * a_fInnerRadius, 0.0f);
		currentAngle += changeInAngle;
		bottomCircleInner.push_back(temp);
	}
	// add top circle OUTER verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle) * a_fOuterRadius, sin(currentAngle) * a_fOuterRadius, a_fHeight);
		currentAngle += changeInAngle;
		topCircleOuter.push_back(temp);
	}
	// add top circle INNER verts to array
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(currentAngle) * a_fInnerRadius, sin(currentAngle) * a_fInnerRadius, a_fHeight);
		currentAngle += changeInAngle;
		topCircleInner.push_back(temp);
	}

	// CONNECT
	// draw top circle
	/*for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(ZERO_V3, bottomCircleOuter[(i + 1) % a_nSubdivisions], bottomCircleOuter[i]);
	}*/
	// draw bottom circle
	/*for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(vector3(0.0f, 0.0f, a_fHeight), topCircleOuter[i], topCircleOuter[(i + 1) % a_nSubdivisions]);
	}*/
	// connect inner and outer rings BOTTOM
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(bottomCircleOuter[i], bottomCircleInner[i], bottomCircleOuter[(i + 1) % a_nSubdivisions]);
		AddTri(bottomCircleOuter[(i + 1) % a_nSubdivisions], bottomCircleInner[i], bottomCircleInner[(i + 1) % a_nSubdivisions]);
	}
	// connect inner and outer rings TOP
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri( topCircleInner[i], topCircleOuter[i], topCircleOuter[(i + 1) % a_nSubdivisions]);
		AddTri( topCircleInner[i], topCircleOuter[(i + 1) % a_nSubdivisions], topCircleInner[(i + 1) % a_nSubdivisions]);
	}
	// connect circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(bottomCircleOuter[i], bottomCircleOuter[(i + 1) % a_nSubdivisions], topCircleOuter[i], topCircleOuter[(i + 1) % a_nSubdivisions]);
	}
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddQuad(bottomCircleInner[(i + 1) % a_nSubdivisions], bottomCircleInner[i], topCircleInner[(i + 1) % a_nSubdivisions], topCircleInner[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
/// <summary>
/// Makes a Torus
/// </summary>
/// <param name="a_fOuterRadius">Distance from centerpoint the outer circles are on</param>
/// <param name="a_fInnerRadius">radius of the component circles</param>
/// <param name="a_nSubdivisionsA">number of outer circles</param>
/// <param name="a_nSubdivisionsB">how many tris each circle is broken up into</param>
/// <param name="a_v3Color">color</param>
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	std::vector<std::vector<vector3>> allCircles;
	GLfloat angleOuter = 0;
	GLfloat changeInAngleOuter = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisionsA));
	GLfloat angleInner = 0;
	GLfloat changeInAngleInner = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisionsB));
	vector3 center = ZERO_V3;
	matrix4 rotation = IDENTITY_M4;
	rotation = glm::rotate(rotation, changeInAngleOuter, vector3(0.0f, 1.0f, 0.0f));
	//matrix4 translation = IDENTITY_M4;
	rotation = glm::translate(rotation, vector3(cos(changeInAngleOuter), 0.0f, sin(changeInAngleOuter)));

	// create circles
	for (uint i = 0; i < a_nSubdivisionsA; i++)
	{
		// create a circle
		std::vector<vector3> tempList;
		for (uint j = 0; j < a_nSubdivisionsA; j++)
		{
			vector3 temp = vector3(cos(angleOuter), sin(angleOuter), 0.0f);
			angleOuter += changeInAngleOuter;
			tempList.push_back(temp);
		}
		

		// rotate the circle points i number of times
		for (uint k = 0; k < tempList.size(); k++)
		{
			//rotation = glm::rotate(rotation, changeInAngle * k, vector3(0.0f, 1.0f, 0.0f));
			//rotation = glm::translate(rotation, vector3(0.0f, 0.0f, 0.0f));
			for (uint m = 0; m < i; m++)
			{
				tempList[k] = rotation * vector4(tempList[k], 1.0f);
			}
			// translate each circle

		}
		angleOuter = 0;
		allCircles.push_back(tempList);
	}

	uint numCircles = allCircles.size();
	for (uint i = 0; i < numCircles; i++)
	{
		// j goes through the points of each circle
		for (uint j = 0; j < a_nSubdivisionsB; j++)
		{
			AddQuad(allCircles[(i + 1) % allCircles.size()][j], allCircles[i][j],  allCircles[(i + 1) % allCircles.size()][(j + 1) % a_nSubdivisionsB], allCircles[i][(j + 1) % a_nSubdivisionsB]);
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	std::vector<std::vector<vector3>> allCircles;
	GLfloat angle = 0;
	GLfloat changeInAngle = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));
	// from in class
	vector3 center = ZERO_V3;
	matrix4 rotation = IDENTITY_M4;
	rotation = glm::rotate(rotation, changeInAngle, vector3(0.0f, 1.0f, 0.0f));

	// create all circles
	for (uint i = 0; i < a_nSubdivisions; i++)
	{
		// create a circle
		std::vector<vector3> tempList;
		for (uint j = 0; j < a_nSubdivisions; j++)
		{
			vector3 temp = vector3(cos(angle), sin(angle), 0.0f);
			angle += changeInAngle;
			tempList.push_back(temp);
		}
		angle = 0;
		
		// rotate the circle points i number of times
		for (uint k = 0; k < tempList.size(); k++)
		{
			//rotation = glm::rotate(rotation, changeInAngle * k, vector3(0.0f, 1.0f, 0.0f));
			//rotation = glm::translate(rotation, vector3(0.0f, 0.0f, 0.0f));
			for (uint m = 0; m < i; m++)
			{
				tempList[k] = rotation * vector4(tempList[k], 1.0f);
			}
		}

		allCircles.push_back(tempList);
	}

	// draw circles 
	// i goes through each circle
	uint numCircles = allCircles.size();
	for (uint i = 0; i < numCircles; i++)
	{
		// j goes through the points of each circle
		for (uint j = 0; j < a_nSubdivisions; j++)
		{
			AddQuad(allCircles[i][j], allCircles[(i + 1) % allCircles.size()][j], allCircles[i][(j + 1) % a_nSubdivisions], allCircles[(i + 1) % allCircles.size()][(j + 1) % a_nSubdivisions]);
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}