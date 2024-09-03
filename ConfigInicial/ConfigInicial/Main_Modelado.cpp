/*
Practica 3: Modelado Geometrico
Alumno: Mejia Alba Israel Hipolito
Fecha de entrega: 02-09-24
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-8.0f; 
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Mejia Alba Israel Hipolito | P3: Modelado geometrico", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.8f, 0.8f, 0.8f, //Front
		0.5f, -0.5f, 0.5f,  0.8f, 0.8f, 0.8f, //Cara gris claro
		0.5f,  0.5f, 0.5f,  0.8f, 0.8f, 0.8f,
		0.5f,  0.5f, 0.5f,  0.8f, 0.8f, 0.8f,
		-0.5f,  0.5f, 0.5f, 0.8f, 0.8f, 0.8f,
		-0.5f, -0.5f, 0.5f, 0.8f, 0.8f, 0.8f,
		
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f, //Back
		 0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f, //Cara gris Rojo
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 1.0f, 0.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.0f,0.0f,
		
		//cara Izquierda del ghast
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, //Cara gis medio
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  -0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
      
		//cara derecha del ghast
		-0.5f,  0.5f,  0.5f,  0.2f, 0.2f, 0.2f, //Cara gris oscuro
		-0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
		-0.5f, -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
		-0.5f, -0.5f, -0.5f,  0.2f, 0.2f, 0.2f,
		-0.5f, -0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
		-0.5f,  0.5f,  0.5f,  0.2f, 0.2f, 0.2f,
		
		-0.5f, -0.5f, -0.5f, 0.15f, 0.15f, 0.15f ,
		0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f ,
		0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f ,
		0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f ,
		-0.5f, -0.5f,  0.5f, 0.15f, 0.15f, 0.15f , //cara inferior
		-0.5f, -0.5f, -0.5f, 0.15f, 0.15f, 0.15f ,
		
		-0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f ,
		0.5f,  0.5f, -0.5f,    0.5f, 0.5f, 0.5f ,
		0.5f,  0.5f,  0.5f,    0.5f, 0.5f, 0.5f ,
		0.5f,  0.5f,  0.5f,    0.5f, 0.5f, 0.5f ,  // cara superior
		-0.5f,  0.5f,  0.5f,   0.5f, 0.5f, 0.5f ,
		-0.5f,  0.5f, -0.5f,   0.5f, 0.5f, 0.5f ,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
  
	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 0.5f, 0.2f, 0.05f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		//Cabeza entera del Ghast
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(3.0f, 2.8f, 2.0f)); // ancho grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

			//Ojo Izq
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.65f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(-0.87f, 8.8f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		//BordeSuperior Ojo
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(-1.27f, 9.7f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		// OjoRojo
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.35f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(-1.52f, 8.67f, 3.53f));
		model = glm::rotate(model, 3.0f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

			//Lagrima Ojo Izq 
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.65f, 0.15f, 0.25f));
		model = glm::translate(model, glm::vec3(-0.87f, 10.6f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
				//gota lagrima
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.15f, 0.55f, 0.25f));
		model = glm::translate(model, glm::vec3(-3.6f, 2.5f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
				//gota pequeña lagrima
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.25f));
		model = glm::translate(model, glm::vec3(-2.0f, 5.9f, 3.55f)); 
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		//Ojo Derecho
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.65f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(0.87f, 8.8f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		//BordeSuperior Ojo
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(1.27f, 9.7f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		// OjoRojo
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.35f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(1.28f, 8.67f, 3.53f));
		model = glm::rotate(model, 3.0f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		//Lagrima Ojo Der 
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.65f, 0.15f, 0.25f));
		model = glm::translate(model, glm::vec3(0.85f, 10.6f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
			//gota lagrima
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.15f, 0.55f, 0.25f));
		model = glm::translate(model, glm::vec3(3.6f, 2.5f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
			//gota pequeña lagrima
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.15f, 0.25f, 0.25f));
		model = glm::translate(model, glm::vec3(2.0f, 5.9f, 3.55f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, -0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara


			//Boca
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.45f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(0.0f, 4.5f, 3.52f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.45f, 0.6f, 0.25f));
		model = glm::translate(model, glm::vec3(-0.2f, 0.89f, 3.52f));
		model = glm::rotate(model, 3.0f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.25f));
		model = glm::translate(model, glm::vec3(-0.95f, 0.89f, 3.52f));
		model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.25f)); 
		model = glm::translate(model, glm::vec3(0.85f, 0.89f, 3.52f));
		model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
		 

		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.45f, 0.2f, 0.25f));
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 3.6f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		
		
		//pata Anterior derecha  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 1.5f, 0.25f));
		model = glm::translate(model, glm::vec3(-3.0f, -0.49f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		//pata Posterior derecha  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 1.5f, 0.25f));
		model = glm::translate(model, glm::vec3(-3.0f, -0.49f, -2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara


		//pata Anterior media  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 2.2f, 0.25f));
		model = glm::translate(model, glm::vec3(0.0f, -0.49f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		//pata Posterior media  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 2.2f, 0.25f));
		model = glm::translate(model, glm::vec3(0.0f, -0.49f, -2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara


		//pata Anterior Izq  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 2.2f, 0.25f));
		model = glm::translate(model, glm::vec3(3.0f, -0.49f, 2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
			
			//Detalle gris pata  izq
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.25f));
		model = glm::translate(model, glm::vec3(3.0f, -2.23f, 2.92f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

		//pata Posterior Izq  del Ghast
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 2.2f, 0.25f));
		model = glm::translate(model, glm::vec3(3.0f, -0.49f, -2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara
			
			//Detalle gris pata  izq
		model = glm::mat4(1.0f); //matriz unitaria de punto de partida para la pata de la mesa
		model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.25f));
		model = glm::translate(model, glm::vec3(3.0f, -2.23f, -2.89f));
		model = glm::rotate(model, 1.555f, glm::vec3(0.0f, 0.57f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // se manda modelo al shader
		glDrawArrays(GL_TRIANGLES, 0, 36); //dibujamos la caja con 2 triangulos por cara

	 

		glBindVertexArray(0); // al final de la creacion de los modelos
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.01f;	 
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.01f;

	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.01f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot +=0.025f;;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -=0.025f;;
 }


