// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
using namespace Gloom;


unsigned int setUpVertexArrayObject()
{
	unsigned int array = 0;
	glGenVertexArrays(1, &array);
	return array;

}
unsigned int setUpVertexBufferObject()
{
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	return buffer;
}


void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.4f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
	float vertices[] = {
		-0.6f, -0.6f, 0.0f,
		0.6f, -0.6f, 0.6f,
		0.0f,  0.0f, 0.0f,
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};

	


	unsigned int arrayID = setUpVertexArrayObject();
	glBindVertexArray(arrayID);

	glBindBuffer(GL_ARRAY_BUFFER, setUpVertexBufferObject());
	//9 = array length
	glBufferData(GL_ARRAY_BUFFER, (9*sizeof(float)) , &vertices, GL_STATIC_DRAW);
	//stride is 0 because we only have one entry type in the vertex array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, setUpVertexBufferObject());
	//9 = array length
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

	
	Shader shader;
	shader.makeBasicShader("C:/git/TDT4195/gloom/gloom/shaders/simple.vert","C:/git/TDT4195/gloom/gloom/shaders/simple.frag");
	
    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
		shader.activate();
		glBindVertexArray(arrayID);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		



        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}


void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
