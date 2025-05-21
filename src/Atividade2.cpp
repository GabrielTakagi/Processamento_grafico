#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// Cores para cada triângulo (RGBA)
std::vector<std::vector<float>> cores = {
    {1.0f, 0.0f, 0.0f, 1.0f}, // vermelho
    {0.0f, 1.0f, 0.0f, 1.0f}, // verde
    {0.0f, 0.0f, 1.0f, 1.0f}, // azul
    {1.0f, 1.0f, 0.0f, 1.0f}, // amarelo
    {1.0f, 0.0f, 1.0f, 1.0f}  // magenta
};

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
    //Inserir variavel cor
    "uniform vec4 inputColor;\n"
    //Criar uma variável de outputs (não é pré-definida como o vertexShader)
    "out vec4 Color;\n"
    //função principal
    "void main()\n"
    "{\n"
        //Setar a variável de output para os próximos processos
        //Vamos deixar o output com a cor laranja
    "   Color = inputColor;\n"
    "}\n";

    GLuint createTriangle(float x0, float y0, float x1, float y1, float x2, float y2){
        
        //Coordenadas dos vértices do triângulo
        float vertices[] = { x0, y0, x1, y1, x2, y2 };

        //Criando objeto para o VBO e VAO
        GLuint VBO, VAO;

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

        //Ativando a instrução dada acima para a VAO de location 0
        glEnableVertexAttribArray(0);

        //Desvincular VBO para evitar ser modificado (Opcional)
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Desvincular VAO para evitar ser modificado (Opcional)
        glBindVertexArray(0);

        return VAO;
    }

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

    //Verificar se o shader foi um sucesso
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

    //Verificar se o fragmented foi um sucesso
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

    GLint colorLoc = glGetUniformLocation(shaderProgram, "inputColor");
    
    std::vector<GLuint> vaoList;
    vaoList.push_back(createTriangle(-0.9f,  0.8f, -0.7f,  0.5f, -0.5f, 0.8f));
    vaoList.push_back(createTriangle(0.5f,  0.8f, 0.7f,  0.5f, 0.9f, 0.8f));
    vaoList.push_back(createTriangle(-0.2f,  0.5f, 0.0f,  0.2f, 0.2f, 0.5f));
    vaoList.push_back(createTriangle(-0.2f, -0.5f, 0.0f, -0.2f, 0.2f, -0.5f));
    vaoList.push_back(createTriangle(-0.9f, -0.8f, -0.7f, -0.5f, -0.5f, -0.8f));
    
    while(!glfwWindowShouldClose(window)){
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        for (size_t i = 0; i < vaoList.size(); ++i){
            glBindVertexArray(vaoList[i]);

            // Define a cor do triângulo i
            glUniform4f(colorLoc, 0.5f, 0.3f, 1.0f, 1.0f);

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto vao : vaoList)
        glDeleteVertexArrays(1, &vao);

    //Exlcuindo Program.
    glDeleteProgram(shaderProgram);

    //Finalizando GLFW.
    glfwTerminate();
    return 0;

}