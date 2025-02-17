#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUpward(
		vector3(0.0f, 3.0f, 20.0f), //Where my eyes are
		vector3(0.0f, 3.0f, 19.0f), //where what I'm looking at is
		AXIS_Y);					//what is up

	//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);
}
void Application::Update(void)
{
	// model matrices are glm matrices
	// 16 x how mamy
	// add and remove to render list
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	
	//Add objects to the Manager
	// soft bodies deform
	// rigid bodies do not change shape
	// rigid bodies need a way to communicate interact with one another
	// wireframes, points in space are used to calc collision data
	// bounding spheres are used for bounding calculations (rotations are handled nicely)
	// need: radius, center
	// center to vert that is farthest away
	// find verts that are farthest away from each other, 
	// don't find average
	// find min and max to get centers of points
	// TEST QUESTION
	// two radii added together < distance between two objects = range
	// aabb uses diff algo, transformations change the max and min

	uint nCount = 0;
	int nRange = 42;
	for (int j = -nRange; j < nRange; j += 2)
	{
		for (int i = -nRange; i < nRange; i += 2)
		{
			m_pMyMeshMngr->AddConeToRenderList(glm::translate(vector3(i, 0.0f, -20)));
			nCount++;
		}
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();

	// draw a skybox
	// instead of rendering, add to render list to create stamp (faster)
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the singleton
	MyMeshManager::ReleaseInstance();

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}