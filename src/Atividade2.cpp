#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

const char *vertexShaderSource =
    //Versão do OpenGL (3.3) e core-profile
    "#version 330 core\n"
    //Receber dado da VAO de location 0
    "layout (location = 0) in vec3 aPos;\n"
    //Função principal
    "void main()\n"
    "{\n"
        //Setar o gl_Position. Ele vai levar o vértice para os proximos processos (output)
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";


const char *fragmentShaderSource =
    //Versão do OpenGL (3.3) e core-profile
    "#version 330 core\n"
    //Criar uma variável de outputs (não é pré-definida como o vertexShader)
    "out vec4 FragColor;\n"
    //função principal
    "void main()\n"
    "{\n"
        //Setar a variável de output para os próximos processos
        //Vamos deixar o output com a cor laranja
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

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

    if(sucessVertex == false){
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;

        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    //#Fragmented shader
    unsigned int fragmentedShader;
    fragmentedShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentedShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentedShader);

    int sucessfragmented;
    glGetShaderiv(fragmentedShader, GL_COMPILE_STATUS, &sucessfragmented);

    if(sucessfragmented == false){
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;

        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    //linkar o vertex e fragment 
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentedShader);
    glLinkProgram(shaderProgram);
    
    //deletar vertex e fragment porque temos o program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentedShader);
    
    //Coordenadas dos vértices do triângulo
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // esquerda
         0.5f, -0.5f, 0.0f, // direita
         0.0f,  0.5f, 0.0f, // cima
    };

    //Criando objeto para o VBO e VAO
    unsigned int VBO, VAO;

    //Gerando VBO e VAO com os objetos declarados acima. Recebendo ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Ligar o VAO. Ele quem administra a VBO e os vértices
    glBindVertexArray(VAO);

    //Ligar VBO como um Buffer de Array. Ele quem armazena os vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Passar o array de vertices criado para nosso VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Instruindo como o VAO de location 0 deve administrar esses vértices passados
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //Ativando a instrução dada acima para a VAO de location 0
    glEnableVertexAttribArray(0);

    //Desvincular VBO para evitar ser modificado (Opcional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Desvincular VAO para evitar ser modificado (Opcional)
    glBindVertexArray(0);
    
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    //Excluindo VAO.
    glDeleteVertexArrays(1, &VAO);

    //Excluindo VBO.
    glDeleteBuffers(1, &VBO);

    //Exlcuindo Program.
    glDeleteProgram(shaderProgram);

    //Finalizando GLFW.
    glfwTerminate();
    return 0;

}