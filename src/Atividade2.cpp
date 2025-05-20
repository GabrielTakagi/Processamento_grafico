#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar *vertexShaderSource = R"(
 #version 400
 layout (location = 0) in vec3 position;
 void main()
 {
	 gl_Position = vec4(position.x, position.y, position.z, 1.0);
 }
 )";

// Código fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar *fragmentShaderSource = R"(
 #version 400
 uniform vec4 color;
 out vec4 color;
 void main()
 {
	 color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
 }
 )";

int main(){

    // Inicialização da GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Criacao da janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Atividade 2", nullptr, nullptr);
    if (!window) {

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //Vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int sucessVertex;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucessVertex);

    //#Fragmented shader
    unsigned int fragmentedShader;
    fragmentedShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentedShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentedShader);

    int sucessfragmented;
    glGetShaderiv(fragmentedShader, GL_COMPILE_STATUS, &sucessfragmented);

    //linkar o vertex e fragment 
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentedShader);
    glLinkProgram(shaderProgram);
    
    //deletar vertex e fragment porque temos o program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentedShader);
    
    //Vertices do triangulo 
    float vertices[] = {
    -0.5f, -0.5f , 0.0f,
    0.5f, 0.5f , 0.0f,
    0.0f, 0.5f , 0.0f,
    };
    
    //VBO e VAO
    unsigned int VBOname, VAOname;
    glGenBuffers(1, &VBOname);
    glGenVertexArrays(1, &VAOname);

    glBindVertexArray(VAOname);

    glBindBuffer(GL_ARRAY_BUFFER, VBOname);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOname);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}