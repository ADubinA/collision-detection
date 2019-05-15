#include "InputManager.h"
#include "glm\glm.hpp"
#include "Menu.h"
//#include "imgui\imgui_impl_opengl3.h"

int main(int argc,char *argv[])
{
	const int DISPLAY_WIDTH = 1200;
	const int DISPLAY_HEIGHT = 800;
	const float zFar = 100.0f;
	const float zNear = 1.0f;
	const float CAM_ANGLE = 60.0f;
	const float relation = (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT;

	Game *scn = new Game(glm::vec3(0.0f, 0.0f, -1.0f), CAM_ANGLE, relation, zNear,zFar);
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	init(display);
	
	scn->Init();
	
	scn->addShader("../res/shaders/basicShader");
	scn->addShader("../res/shaders/pickingShader");	
	
	display.setScene(scn);

	Menu* menu = new Menu(&display, scn);

	

	while(!display.closeWindow())
	{
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		scn->Draw(0,0,true);
		scn->Motion(menu->f);
		if(scn->menu_mode)
		{
			if (!menu->created)
			{
				menu->create();
				init(display);
			}
			menu->DrawMenu();

		}
		else
		{
			if (menu->created)
			{
				menu->destroy();
				init(display);
			}
		}



		


		display.SwapBuffers();
		display.PollEvents();
	}
	delete scn;
	glfwTerminate();

	return 0;
}
