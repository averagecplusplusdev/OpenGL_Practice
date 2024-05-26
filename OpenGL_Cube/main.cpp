// YOU WERE AT 1:04:42 ON THE OPENGL_CRASHCOURSE

/*
OPENGL CUBE!!
██╗░░░░░░░██╗ ███████╗ ██╗ ██████╗░ ███████╗   ░██████╗░ ░█████╗░ ██╗ ███╗░░██╗ ░██████╗░   ██████╗░ ██████╗░ ██╗ ██╗
██║░░██╗░░██║ ██╔════╝ ╚█║ ██╔══██╗ ██╔════╝   ██╔════╝░ ██╔══██╗ ██║ ████╗░██║ ██╔════╝░   ╚════██╗ ██╔══██╗ ██║ ██║
╚██╗████╗██╔╝ █████╗░░ ░╚╝ ██████╔╝ █████╗░░   ██║░░██╗░ ██║░░██║ ██║ ██╔██╗██║ ██║░░██╗░   ░█████╔╝ ██║░░██║ ██║ ██║
░████╔═████║░ ██╔══╝░░ ░░░ ██╔══██╗ ██╔══╝░░   ██║░░╚██╗ ██║░░██║ ██║ ██║╚████║ ██║░░╚██╗   ░╚═══██╗ ██║░░██║ ╚═╝ ╚═╝
░╚██╔╝░╚██╔╝░ ███████╗ ░░░ ██║░░██║ ███████╗   ╚██████╔╝ ╚█████╔╝ ██║ ██║░╚███║ ╚██████╔╝   ██████╔╝ ██████╔╝ ██╗ ██╗
░░╚═╝░░░╚═╝░░ ╚══════╝ ░░░ ╚═╝░░╚═╝ ╚══════╝   ░╚═════╝░ ░╚════╝░ ╚═╝ ╚═╝░░╚══╝ ░╚═════╝░   ╚═════╝░ ╚═════╝░ ╚═╝ ╚═╝
*/

//regular includes
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//project includes
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
//typedef for easy access
typedef uint32_t uint32;
typedef uint16_t uint16;

//window height and width

uint16 height = 800;
uint16 width = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f, 0.5f,      0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // (top down bottom layer) bottom left 0	
	-0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,  5.0f, 0.0f, // (top down bottom layer) top left 1
	0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,  0.0f, 0.0f, // (top down bottom layer) top right 2
	0.5f, 0.0f, 0.5f,      0.83f, 0.70f, 0.44f,  5.0f, 0.0f, // (top down bottom layer) bottom right 3 
	-0.5f, 1.0f, 0.5f,      0.92f, 0.86f, 0.76f,  2.5f, 5.0f, // (top down top layer) bottom left 4
	-0.5f, 1.0f, -0.5f,      0.92f, 0.86f, 0.76f,  2.5f, 5.0f, // (top down top layer) bottom right 5
	0.5f, 1.0f, -0.5f,      0.92f, 0.86f, 0.76f,  2.5f, 5.0f, // (top down top layer) top left 6
	0.5f, 1.0f, 0.5f,      0.92f, 0.86f, 0.76f,  2.5f, 5.0f, // (top down top layer) top right 7
};


// Indices for vertices array
GLuint indices[] =
{
	0,1,2,
	0,2,3,
	4,5,6,
	4,7,6,
	3,7,4,
	3,0,4,
	7,6,2,
	7,3,2,
	0,4,5,
	0,1,5,
	6,2,1,
	6,5,1
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_3D", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO (i have no idea what the math is for lol) 
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them while running the program
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Original code from the tutorial
	Texture TCPP("TCPP.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	TCPP.texUnit(shaderProgram, "tex0", 0);

	//GLM 1stuff

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	//GL INIT DEPTH
	
	glEnable(GL_DEPTH_TEST);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(2.4f, 0.33f, 2.55f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		//GLM stuff

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.1f;
			prevTime - crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.5f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		TCPP.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	TCPP.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}