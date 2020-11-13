#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <windows.h>
#include <cstring>
#include <stb_image.h>
#include "src/shader.h"

#include <math.h>
// 定义顶点着色器 输出为gl_Position
//const char *vertexShaderSource = "#version 330 core\n"
//                                 "layout (location = 0) in vec3 aPos;\n"//定点属性
//                                 "layout (location = 1) in vec3 aColor; "// 颜色变量的属性位置值为 1
//                                 "layout (location = 2) in vec2 aTexCoord;\n"
//                                 "out vec3 ourColor;\n"
//                                 "out vec2 TexCoord;\n"
//                                 //"out vec4 vertexColor;\n"//输出vertexColor并且传递到片段着色器上
//                                 "void main()\n"
//                                 "{\n"
//                                 "   gl_Position = vec4(aPos, 1.0);\n"
//                                 //"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
//
//                                 "ourColor=vec3(aColor.xyz);\n"
//                                 " TexCoord = aTexCoord;\n"
//                                 "}\0";

//定义片段着色器输出为FragColor
//const char *fragmentShaderSource = "#version 330 core\n"
//                                   "out vec4 FragColor;\n"//输出
//                                   "in vec3 ourColor;\n"
//                                   "in vec2 TexCoord;\n"
//                                   "uniform sampler2D ourTexture;\n"
//                                   //"uniform vec4 ourColor;"//全局变量修饰uniform
//                                   "in vec4 vertexColor;\n"//输入由定点着色器导入
//                                   "void main()\n"
//                                   "{\n"
//                                   "   FragColor = texture(ourTexture,TexCoord);\n"
//                                   "}\n\0";
//片段着色器 fragcolor
//GLSL 有四个基本属性int、float、double、uint和bool 两个容器Vector和Matrix
/*
 * n取分量1,2,3,4
vecn	包含n个float分量的默认向量（常用）
bvecn	包含n个bool分量的向量
ivecn	包含n个int分量的向量
uvecn	包含n个unsigned int分量的向量
dvecn	包含n个double分量的向量
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
int main() {
    // glfw: initialize and configure
    // ------------------------------
//    glfwInit();//初始化glfw
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//加上主程序版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//最低版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);//是否可调整窗口大小
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//如果是mac平台必须加上
#endif
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);//配置窗口属性
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //必须要不然闪退 当前环境应用窗体
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//将窗体加入缓存中可调整窗体大小

    // glad: load all OpenGL function pointers
    // ---------------------------------------

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        glfwDestroyWindow(window);
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    //开启深度检测
    //着色器渲染
    Shader ourShader("../texture.vs", "../texture.fs");
    //定义顶点位置坐标数组
//    float vertices[] = {
//            //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f,   // 右上
//            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,   // 右下
//            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
//            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
//    };
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    /**
     * 纹理
     */
//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3,  // second triangle
//
//    };
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO, EBO;

    // 创建一个内存对象
    glGenBuffers(1, &VBO);
    // 创建一个顶点数组对象
    glGenVertexArrays(1, &VAO);
    // 首先绑定顶点数组对象，，。
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    // 然后将内存对象绑定为顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 向缓冲内存写入数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 然后配置顶点属性，告诉OpenGL如何把顶点数据链接到顶点着色器的顶点属性上
    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  5 * sizeof(float), (void *) (3* sizeof(float)));
    glEnableVertexAttribArray(2);
    unsigned int texture1,texture2;
    //创建一个纹理内存对象
    glGenTextures(1, &texture1);
    //将纹理对象绑定到2d平面上
    glBindTexture(GL_TEXTURE_2D, texture1);
    //配置纹理属性
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
//        加载纹理图片
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //构建纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);//释放图像内存
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        //中有alpha通道必须渲染成这样
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    ourShader.use();
    ourShader.setInt("texture1",0);
    ourShader.setInt("texture2", 1); // 或者使用着色器类设置
    // 您可以在之后取消绑定VAO，以便其他VAO调用不会意外地修改此VAO，但这种情况很少发生。
    // 修改其他VAO需要调用glBindVertexArray，因此我们通常不会在不直接需要时取消绑定VAO（也不是VBO）。
    //    glBindVertexArray(0);
    // -----------
    /**
     * -----------------------------mtx测试--------------------------------------
     */
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示

    /**
   * -------------------------------------------------------------------------------------------
   */
    while (!glfwWindowShouldClose(window)) {
        // 处理输入事件
        processInput(window);

        // 清空背景颜色
        // 当调用glClear函数，清除颜色缓冲之后，
        // 整个颜色缓冲都会被填充为glClearColor里所设置的颜色
        // 在这里，我们将屏幕设置为了类似黑板的深蓝绿色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//        float timeValue = glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//查找全局变量
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 激活着色器程序
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//        glm::mat4 trans;
//        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model=glm::rotate(model, (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//        view=glm::translate(view,glm::vec3(0.0f,0.0f,3.0f));
        view = glm::lookAt(cameraPos,
                           cameraPos + cameraFront,
                           cameraUp);
        projection=glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
//        找到对应的id中uniform全局变量
        unsigned int modeLoc=glGetUniformLocation(ourShader.ID,"model");
        unsigned int viewLoc=glGetUniformLocation(ourShader.ID,"view");
        glUniformMatrix4fv(modeLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
//        全局变量中写入指针
        ourShader.setMat4("projection", projection);//写入projection
        //更新之前必须使用着色器程序
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        // 因为我们只有一个VAO，所以不需要每次都绑定它，但我们会这样做，以使事情更有条理
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++){
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // 使用当前激活的着色器，之前定义的顶点属性配置，和VBO的顶点数据（通过VAO间接绑定）来绘制图元。
//        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwPollEvents();
        glfwSwapBuffers(window);
//        Sleep(1);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
