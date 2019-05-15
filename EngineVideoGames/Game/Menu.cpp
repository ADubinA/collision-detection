#include "Menu.h"



Menu::Menu(Display *display, Scene *scn)
{
	this->display = display;
	this->scn = scn;
	this->created = false;
	this->move = false;


	show_demo_window = true;
	show_another_window = false;
	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void Menu::create()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.FontGlobalScale = 4.0f;

	ImGui_ImplGlfwGL3_Init(display->get_window(), true);
	ImGui::StyleColorsDark();
	this->created = true;

}

void Menu::DrawMenu()
{
	ImGui_ImplGlfwGL3_NewFrame();

	static float f = 0.0f;
	ImGui::Begin("MainWindow");                          // Create a window called "Hello, world!" and append into it.
	ImGui::SetWindowSize("MainWindow", ImVec2((float)1400, (float)800));

	ImGui::Text("picked shape is: %d", scn->pickedShape);
	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		this->move = !this->move;
	ImGui::SameLine();
	ImGui::Text("target is moving: %d", this->move);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::destroy()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	this->created = false;

}


