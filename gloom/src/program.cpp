// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
using namespace Gloom;

//function wor creating a VAO and returning its ID. A VAO is an object that links the Input buffers to shaders
unsigned int setUpVertexArrayObject()
{
	unsigned int array = 0;
	glGenVertexArrays(1, &array);
	return array;
}

//function for creating a VBO and retirning its ID. A VBO holds the values for the vertices
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
		-0.1f, -0.1f, 0.0f,
		1.0f, -0.1f, 1.0f,
		0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2, 3, 4, 5
	};

	//setting up a VAO and binding it witch can be compared with opening a textfile so you can write to it
	unsigned int arrayID = setUpVertexArrayObject();
	glBindVertexArray(arrayID);
	//setting up a VBO witch is a space in the memory for holding the values for the vertices
	glBindBuffer(GL_ARRAY_BUFFER, setUpVertexBufferObject());
	//sending the vertices data to the GPU by telling OpenGl that the space must be sufficient for n floatingpoint numbers corresponding to the vertices
	// - ,giving it the vertices and tellign it that their values are going to be static since its not changing much(at all)
	glBufferData(GL_ARRAY_BUFFER, (18*sizeof(float)) , &vertices, GL_STATIC_DRAW);
	//stride is 0 because we only have one entry type in the vertex array, so we dont have to tell the number of bytes between each entery
	//Pointer is 0 because it the entries starts at 0 in the buffer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//setting up a buffer for the indeces so we can tell opengl witch vertices who overlap and therefore can be drawn only one time
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, setUpVertexBufferObject());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

	//making a shader object from the Shader.hpp file, and loading,linking and compiling the vert and frag shaders
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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		



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
