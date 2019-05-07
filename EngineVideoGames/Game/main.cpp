#include "InputManager.h"
#include "glm\glm.hpp"
#include "imgui\imgui.h"
#include"imgui\imgui_impl_glfw_gl3.h"
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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontGlobalScale = 4.0f;


	ImGui_ImplGlfwGL3_Init(display.get_window(), true);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();


	static bool move = false;


	while(!display.closeWindow())
	{
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		ImGui_ImplGlfwGL3_NewFrame();
		scn->Draw(0,0,true);
		scn->Motion();

		{
			static float f = 0.0f;
			ImGui::Begin("MainWindow");                          // Create a window called "Hello, world!" and append into it.
			ImGui::SetWindowSize("MainWindow", ImVec2((float)1400, (float)800));

			ImGui::Text("picked shape is: %d", scn->pickedShape);       
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				move = !move;
			ImGui::SameLine();
			ImGui::Text("target is moving: %d", move);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		


		display.SwapBuffers();
		display.PollEvents();
	}
	delete scn;
	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}
