#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);

		
}
void Application::Update(void)
{
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
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	static float fDisp = 0.0f;
	matrix4 m4Model = glm::translate(IDENTITY_M4, vector3(fDisp, 0.0f, 0.0f));


	// alien block positions
	// there are 46 blocks
	// this seems like a lot.
	vector3 v3_positions[8][11] = {
		{ZERO_V3, ZERO_V3, vector3(2.0f,0.0f,0.0f), ZERO_V3, ZERO_V3, ZERO_V3, ZERO_V3, ZERO_V3, vector3(8.0f, 0.0f, 0.0f), ZERO_V3, ZERO_V3},
		{ZERO_V3, ZERO_V3, ZERO_V3, vector3(3.0f, 1.0f, 0.0f), ZERO_V3, ZERO_V3, ZERO_V3, vector3(7.0f, 1.0f, 0.0f), ZERO_V3, ZERO_V3, ZERO_V3},
		{ZERO_V3, ZERO_V3, vector3(2.0f, 2.0f, 0.0f), vector3(3.0f,2.0f, 0.0f), vector3(4.0f,2.0f, 0.0f), vector3(5.0f, 2.0f, 0.0f), vector3(6.0f,2.0f, 0.0f), vector3(7.0f,2.0f, 0.0f), vector3(8.0f,2.0f, 0.0f), ZERO_V3, ZERO_V3},
		{ZERO_V3, vector3(1.0f, 3.0f, 0.0f), vector3(2.0f, 3.0f, 0.0f), ZERO_V3, vector3(4.0f, 3.0f, 0.0f), vector3(5.0f, 3.0f, 0.0f), vector3(6.0f, 3.0f, 0.0f), ZERO_V3, vector3(8.0f, 3.0f, 0.0f), vector3(9.0f, 3.0f, 0.0f), ZERO_V3},
		{vector3(0.0f, 4.0f, 0.0f), vector3(1.0f, 4.0f, 0.0f), vector3(2.0f, 4.0f, 0.0f), vector3(3.0f, 4.0f, 0.0f), vector3(4.0f, 4.0f, 0.0f), vector3(5.0f, 4.0f, 0.0f), vector3(6.0f, 4.0f, 0.0f), vector3(7.0f, 4.0f, 0.0f), vector3(8.0f, 4.0f, 0.0f), vector3(9.0f, 4.0f, 0.0f), vector3(10.0f, 4.0f, 0.0f)},
		{vector3(0.0f, 5.0f, 0.0f), ZERO_V3, vector3(2.0f, 5.0f, 0.0f), vector3(3.0f, 5.0f, 0.0f), vector3(4.0f, 5.0f, 0.0f), vector3(5.0f, 5.0f, 0.0f), vector3(6.0f, 5.0f, 0.0f), vector3(7.0f, 5.0f, 0.0f), vector3(8.0f, 5.0f, 0.0f), ZERO_V3, vector3(10.0f, 5.0f, 0.0f)},
		{vector3(0.0f, 6.0f, 0.0f), ZERO_V3, vector3(2.0f, 6.0f, 0.0f), ZERO_V3, ZERO_V3, ZERO_V3, ZERO_V3, ZERO_V3, vector3(8.0f, 6.0f, 0.0f), ZERO_V3, vector3(10.0f, 6.0f, 0.0f)},
		{ZERO_V3, ZERO_V3, ZERO_V3, vector3(3.0f, 7.0f, 0.0f), vector3(4.0f, 7.0f, 0.0f), ZERO_V3, vector3(6.0f, 7.0f, 0.0f), vector3(7.0f, 7.0f, 0.0f), ZERO_V3, ZERO_V3, ZERO_V3}
	};

	//m_pMesh->Render(m4Projection, m4View, ToMatrix4(m_qArcBall));
	for (uint i = 0; i < 8; i++) 
	{
		for (uint j = 0; j < 11; j++)
		{
			if (v3_positions[i][j] != ZERO_V3)
			{
				m_pMesh->Render(m4Projection, m4View, glm::translate(m4Model, v3_positions[i][j]));
			}
		}
	}
	
	fDisp += 0.01f;

	// draw a skybox
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
	//Release meshes
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}