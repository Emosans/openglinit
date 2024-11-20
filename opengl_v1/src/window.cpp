#include "../dependencies/include/glew.h"
#include "../dependencies/include/glfw3.h"
#include "../headers/VertexBuffer.h";
#include "../headers/IndexBuffer.h";
#include "../headers/Renderer.h";
#include "../headers/VertexArray.h"
#include "../headers/VertexBufferLayout.h"
#include "../headers/Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int main(void)
{
    float time = 0.0f;
    
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    // create array of positions
    float positions[] = {
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5
    };

    // creating an index buffer
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    if (glewInit() != GLEW_OK) {
        cout << "Error";
    }

    {
    VertexArray vao;
    VertexBuffer vb(positions, 8 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    vao.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.setUniform4f("u_color", 0.8f, 0.3f, 0.5f, 1.0f);

    vao.Unbind();
    vb.UnBind();
    ib.UnBind();
    shader.Unbind();

    float r = 0.0f;
    float increment = 0.05f;

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            shader.Bind();
            shader.setUniform4f("u_color", r, 0.3f, 0.5f, 1.0f);
            vao.Bind();
            ib.Bind();

            // draw arrays
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f) {
                increment = -0.05f;
            }
            else if (r < 0.0f) {
                increment = 0.05f;
            }
            r += increment;

            glfwSwapBuffers(window);

            glfwPollEvents();

            time += 0.01f;
        }
    }
    glfwTerminate();
    return 0;
}