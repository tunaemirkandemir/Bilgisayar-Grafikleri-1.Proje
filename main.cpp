// Sokak Sahnesi - Çoklu Lamba, Bina ve Düzgün Kamera Hareketi
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

const unsigned int WIDTH = 1000;
const unsigned int HEIGHT = 800;

// === Kamera Konumu ===
glm::vec3 cameraPos = glm::vec3(0.0f, 3.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, -0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f; // Başlangıçta z-ekseni yönüne baksın
float pitch = 0.0f;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.1f;
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity; // y ekseni ters

    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    // pitch değerini sınırlıyoruz
    if (pitch > 89.0f)  pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Yeni yön vektörünü hesapla
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}


// === Vertexler (yol, kaldırımlar, lambalar, binalar) ===
std::vector<float> vertices = {
    // Yol (orta)
    -2.0f, 0.0f, -10.0f,
    2.0f, 0.0f, -10.0f,
    2.0f, 0.0f, 10.0f,
    2.0f, 0.0f, 10.0f,
    -2.0f, 0.0f, 10.0f,
    -2.0f, 0.0f, -10.0f,

     // Sol kaldırım
     -3.0f, 0.0f, -10.0f,
     -2.0f, 0.0f, -10.0f,
     -2.0f, 0.0f, 10.0f,
     -2.0f, 0.0f, 10.0f,
     -3.0f, 0.0f, 10.0f,
     -3.0f, 0.0f, -10.0f,

     // Sağ kaldırım
      2.0f, 0.0f, -10.0f,
      3.0f, 0.0f, -10.0f,
      3.0f, 0.0f, 10.0f,
      3.0f, 0.0f, 10.0f,
      2.0f, 0.0f, 10.0f,
      2.0f, 0.0f, -10.0f,

      // Sokak lambası direği (küçük bir dikdörtgen)
1.9f, 0.0f, 10.0f,
 2.1f, 0.0f, 10.0f,
 2.1f, 3.0f, 10.0f,
 2.1f, 3.0f, 10.0f,
1.9f, 3.0f, 10.0f,
1.9f, 0.0f, 10.0f,

// Lamba küresi (sokak lambasının üst kısmı)
 1.7f, 3.0f, 10.0f,
  2.3f, 3.0f, 10.0f,
  2.3f, 3.3f, 10.0f,
  2.3f, 3.3f, 10.0f,
 1.7f, 3.3f, 10.0f,
 1.7f, 3.0f, 10.0f,

      // Yeni direk
      1.9f, 0.0f, -10.0f,  
      2.1f, 0.0f, -10.0f,  
      2.1f, 3.0f, -10.0f,
      2.1f, 3.0f, -10.0f,   
      1.9f, 3.0f, -10.0f,  
      1.9f, 0.0f, -10.0f,

    //   Yeni lamba küresi
      1.7f, 3.0f, -10.0f,  
      2.3f, 3.0f, -10.0f,  
      2.3f, 3.3f, -10.0f,
      2.3f, 3.3f, -10.0f,   
      1.7f, 3.3f, -10.0f,  
      1.7f, 3.0f, -10.0f,

      // Yeni direk
1.9f, 0.0f, -0.0f,
2.1f, 0.0f, -0.0f,
2.1f, 3.0f, -0.0f,
2.1f, 3.0f, -0.0f,
1.9f, 3.0f, -0.0f,
1.9f, 0.0f, -0.0f,

//   Yeni lamba küresi
  1.7f, 3.0f, -0.0f,
  2.3f, 3.0f, -0.0f,
  2.3f, 3.3f, -0.0f,
  2.3f, 3.3f, -0.0f,
  1.7f, 3.3f, -0.0f,
  1.7f, 3.0f, -0.0f,

  // Yeni direk
-1.9f, 0.0f, -10.0f,
-2.1f, 0.0f, -10.0f,
-2.1f, 3.0f, -10.0f,
-2.1f, 3.0f, -10.0f,
-1.9f, 3.0f, -10.0f,
-1.9f, 0.0f, -10.0f,

//   Yeni lamba küresi
 -1.7f, 3.0f, -10.0f,
  -2.3f, 3.0f, -10.0f,
  -2.3f, 3.3f, -10.0f,
  -2.3f, 3.3f, -10.0f,
  -1.7f, 3.3f, -10.0f,
  -1.7f, 3.0f, -10.0f,

  // Yeni direk
-1.9f, 0.0f, 10.0f,
-2.1f, 0.0f, 10.0f,
-2.1f, 3.0f, 10.0f,
-2.1f, 3.0f, 10.0f,
-1.9f, 3.0f, 10.0f,
-1.9f, 0.0f, 10.0f,

//   Yeni lamba küresi
 -1.7f, 3.0f, 10.0f,
  -2.3f, 3.0f, 10.0f,
  -2.3f, 3.3f, 10.0f,
  -2.3f, 3.3f, 10.0f,
  -1.7f, 3.3f, 10.0f,
  -1.7f, 3.0f, 10.0f,

  // Yeni direk
        -1.9f, 0.0f, 0.0f,
        -2.1f, 0.0f, 0.0f,
        -2.1f, 3.0f, 0.0f,
        -2.1f, 3.0f, 0.0f,
        -1.9f, 3.0f, 0.0f,
        -1.9f, 0.0f, 0.0f,

        //   Yeni lamba küresi
        -1.7f, 3.0f, 0.0f,
        -2.3f, 3.0f, 0.0f,
        -2.3f, 3.3f, 0.0f,
        -2.3f, 3.3f, 0.0f,
        -1.7f, 3.3f, 0.0f,
        -1.7f, 3.0f, 0.0f,


        // Ön yüz
          -6.0f, 0.0f, -15.0f, 6.0f, 0.0f, -15.0f, 6.0f, 5.0f, -15.0f,
          6.0f, 5.0f, -15.0f, -6.0f, 5.0f, -15.0f, -6.0f, 0.0f, -15.0f,

          // Arka yüz
          -6.0f, 0.0f, -11.0f, 6.0f, 0.0f, -11.0f, 6.0f, 5.0f, -11.0f,
          6.0f, 5.0f, -11.0f, -6.0f, 5.0f, -11.0f, -6.0f, 0.0f, -11.0f,

          // Sol yüz
          -6.0f, 0.0f, -11.0f, -6.0f, 0.0f, -15.0f, -6.0f, 5.0f, -15.0f,
          -6.0f, 5.0f, -15.0f, -6.0f, 5.0f, -11.0f, -6.0f, 0.0f, -11.0f,

          // Sağ yüz
          6.0f, 0.0f, -11.0f, 6.0f, 0.0f, -15.0f, 6.0f, 5.0f, -15.0f,
          6.0f, 5.0f, -15.0f, 6.0f, 5.0f, -11.0f, 6.0f, 0.0f, -11.0f,

          // Alt yüz
          -6.0f, 0.0f, -11.0f, 6.0f, 0.0f, -11.0f, 6.0f, 0.0f, -15.0f,
          6.0f, 0.0f, -15.0f, -6.0f, 0.0f, -15.0f, -6.0f, 0.0f, -11.0f,

          // Üst yüz
          -6.0f, 5.0f, -11.0f, 6.0f, 5.0f, -11.0f, 6.0f, 5.0f, -15.0f,
          6.0f, 5.0f, -15.0f, -6.0f, 5.0f, -15.0f, -6.0f, 5.0f, -11.0f,

          //kapı
          -1.0f, 0.0f, -10.999f, 1.0f, 0.0f, -10.999f, 1.0f, 3.0f, -10.999f,
          1.0f, 3.0f, -10.999f, -1.0f, 3.0f, -10.999f, -1.0f, 0.0f, -10.999f,

          // Left slope
          -6.0f, 5.0f, -11.0f, 0.0f, 7.0f, -13.0f, -6.0f, 5.0f, -15.0f,
          // Right slope
          6.0f, 5.0f, -11.0f, 6.0f, 5.0f, -15.0f, 0.0f, 7.0f, -13.0f,

          -6.0f, 5.0f, -15.0f,
          6.0f, 5.0f, -15.0f,
          0.0f, 7.0f, -13.0f ,// Tepe noktası biraz önde
          
          
          
          - 6.0f, 5.0f, -11.0f,
            6.0f, 5.0f, -11.0f,
            0.0f, 7.0f, -13.0f  // Aynı tepe noktası, ortada

        
        
};

// === Fonksiyonlar ===
void framebuffer_size_callback(GLFWwindow* w, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    float speed = 7.0f * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= right * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += right * speed;
    if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        

}

unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
}

// === Shaderlar ===
const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 FragPos;
out vec3 Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = vec3(0.0, 1.0, 0.0);
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)glsl";

const char* fragmentShaderSource = R"glsl(
#version 330 core
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 lightPos[6];
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 result = vec3(0.0);
    for (int i = 0; i < 6; ++i) {
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        result += diff * lightColor * 0.5f;
    }
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
    vec3 finalColor = (ambient + result) * objectColor;
    FragColor = vec4(finalColor, 1.0);
}
)glsl";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sokak Sahnesi", NULL, NULL);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Shader
    unsigned int vShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    // VAO/VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO); glGenBuffers(1, &VBO);
    glBindVertexArray(VAO); glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);

    // Lamba pozisyonları
    glm::vec3 lights[6] = {
        glm::vec3(2.0f, 3.0f, -10.0f),
        glm::vec3(2.0f, 3.0f, 10.0f),
        glm::vec3(2.0f, 3.0f, 0.0f),
        glm::vec3(-2.0f, 3.0f , -10.0f),
        glm::vec3(-2.0f, 3.0f , 10.0f),
        glm::vec3(-2.0f, 3.0f , 0.0f)
    };

    while (!glfwWindowShouldClose(window)) {
        float current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(cameraPos));
        glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"), 1.0f, 1.0f, 0.8f);
        glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 6, glm::value_ptr(lights[0]));

        glBindVertexArray(VAO);

        // Yol ve kaldırımlar
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.3f, 0.3f, 0.3f); glDrawArrays(GL_TRIANGLES, 0, 6);
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.6f, 0.6f, 0.6f); glDrawArrays(GL_TRIANGLES, 6, 6);
        glDrawArrays(GL_TRIANGLES, 12, 6);

        // Lambalar ve direkler
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); glDrawArrays(GL_TRIANGLES, 18, 6);  // Direk
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); glDrawArrays(GL_TRIANGLES, 24, 6);  // Lamba Küresi

        //////////////////////////////////////////////////////////////////////////////////
        // Yeni direği çizmek
       glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); // Yeni direk rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 30, 6); // Yeni direği çizin (18. indexten başla, 6 vertex)

        // Yeni lambayı çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); // Yeni lamba rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 36, 6); // Yeni lambayı çizin (18. indexten başla, 6 vertex)
        ////////////////////////////////////////////////////////////////////////////////////
             // Yeni direği çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); // Yeni direk rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 42, 6); // Yeni direği çizin (18. indexten başla, 6 vertex)

        // Yeni lambayı çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); // Yeni lamba rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 48, 6); // Yeni lambayı çizin (18. indexten başla, 6 vertex)
        // Yeni direği çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); // Yeni direk rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 54, 6); // Yeni direği çizin (18. indexten başla, 6 vertex)

        // Yeni lambayı çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); // Yeni lamba rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 60, 6); // Yeni lambayı çizin (18. indexten başla, 6 vertex)
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); // Yeni direk rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 66, 6); // Yeni direği çizin (18. indexten başla, 6 vertex)

        // Yeni lambayı çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); // Yeni lamba rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 72, 6); // Yeni lambayı çizin (18. indexten başla, 6 vertex)
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.7f, 0.7f, 0.7f); // Yeni direk rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 78, 6); // Yeni direği çizin (18. indexten başla, 6 vertex)

        // Yeni lambayı çizmek
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 1.0f, 0.8f); // Yeni lamba rengi (örneğin sarı)
        glDrawArrays(GL_TRIANGLES, 84, 6); // Yeni lambayı çizin (18. indexten başla, 6 vertex)
          
        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 1.0f, 0.5f, 0.0f);
        glDrawArrays(GL_TRIANGLES, 90, 36); // 6 yüzey x 6 vertex = 36

        glUniform3f(glGetUniformLocation(shaderProgram, "objectColor"), 0.3f, 0.15f, 0.05f);
        glDrawArrays(GL_TRIANGLES, 126, 6);

        glUniform3f(glGetUniformLocation(shaderProgram, "objectcolor"), 0.4f, 0.2f, 0.1f);
        glDrawArrays(GL_TRIANGLES, 132, 6);

        glUniform3f(glGetUniformLocation(shaderProgram, "objectcolor"), 0.4f, 0.2f, 0.1f);
        glDrawArrays(GL_TRIANGLES, 138, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO); glDeleteBuffers(1, &VBO); glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
