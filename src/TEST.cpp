#include <GL/glew.h>
#include <fstream>
#include <iostream>

//#include "Object.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/common.hpp>

//#include "Shader.h"
//#include "Camera.h"
//#include "Buffer.h"
//#include "VertexArray.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Renderer2D.h"
#include "Window.h"

int main() {
    float width = 1440.0f, height = 1000.0f; 
    std::shared_ptr<OrthographicCamera> MainCamera = std::make_shared<OrthographicCamera>();
    MainCamera->SetSpecs({ -width / 2,width / 2, -height / 2, height / 2 ,-10.0f,10.f });
    TestWindow* window = new TestWindow(width, height, "Nada3DRenderer"); 
    window->Init();

    window->AttatchCamera(MainCamera); 
    if (window == NULL)
        return 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 450");
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    glm::mat4 MVP{ 1.0f };
    
    int repx = 100;
    int repy = 100;
    PrimitiveObject::Quad* SimpleQuad = new PrimitiveObject::Quad({ width / repx, height / repy,glm::vec3{0.0f} });
    Texture tex("mario.png"); 
    Renderer2D::Init(); 
    // Main loop
    while (!glfwWindowShouldClose(window->GetWindow())){
                     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
            glEnable(GL_DEPTH_TEST); 

      ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
            {
                    static float roll, pitch, yaw = 0;

                    ImGui::Begin("Parameters Testing" );
                    ImGui::SliderFloat("x", &roll, 0.0f, 2.0f * 3.14f);            // Edit 1 float using a slider from 0.0f to 1.0f
                    ImGui::SliderFloat("y", &pitch, 0.0f,2.0f * 3.14f);            // Edit 1 float using a slider from 0.0f to 1.0f
                    ImGui::SliderFloat("z", &yaw, 0.0f,2.0f * 3.14f );            // Edit 1 float using a slider from 0.0f to 1.0f
                    MVP = glm::transpose(glm::eulerAngleXYZ(roll, pitch, yaw));
                    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                    ImGui::Text("Draw Calls: %d", Renderer2D::GetStats().m_DrawCalls); 
                    ImGui::Text("Draw Count: %d", Renderer2D::GetStats().m_DrawCount); 
                    ImGui::End();
                    
                }
             
        
               Renderer2D::GetShader()->UniformMatrix4("v_ViewProjection",glm::value_ptr(MainCamera->get_cameramatrix())); 
               Renderer2D::NewBatch(); 
           
                for (int x = 0; x < repx; x++) {
                   for (int y = 0; y < repy; y++) {
                       float xpos = (-width / 2.0f + width /(repx*2)+ (width / repx) * x); 
                       float ypos = (height / 2.0f - height / (repy*2) - (height / repy) * y);
                       glm::vec3 pos{xpos,ypos,0.0f};
                       SimpleQuad->MoveToPoint(pos); 
                       SimpleQuad->SetColor(glm::vec4{ 1.0f*(1-y)/(repy-1),1.0f*(x)/(repx-1),0.5f*(x+y)/(repx-1),1.0f });// r-y r down blue
                       //Renderer2D::DrawQuad(SimpleQuad); 
                       Renderer2D::DrawTexturedQuad(SimpleQuad, tex); 
                    }
               }
                
               Renderer2D::EndBatch(); 
               Renderer2D::Flush();


            ImGui::Render();
            int display_w, display_h;
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window->Update(); 
           }

    // Cleanup
    Renderer2D::Finish(); 
   delete SimpleQuad;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete window; 
       return 0;

}
