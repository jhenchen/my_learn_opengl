//
//  main.cpp
//  firstopengl
//
//  Created by wjc on 2018/12/30.
//  Copyright © 2018年 wjc. All rights reserved.
//

#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(800,600,"LearnOpenGl", NULL, NULL);
    if (window == NULL) {
        std::cout << "failed to create gl window.\n";
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialise glad.\n";
        return -1;
    }
    
    glViewport(0,0,600,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    float vertices[] =
    {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };
    
    unsigned int my_traingle_vao;
    glGenVertexArrays(1,&my_traingle_vao);
    glBindVertexArray(my_traingle_vao);
    unsigned int my_traingle_vbo;
    glGenBuffers(1,&my_traingle_vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER,my_traingle_vbo);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    const char *vertexShaderSource =
    "#version 410 core \n"
    "layout (location = 0) in vec3 aPos; \n"
   " void main() \n"
   " { \n"
    "    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0); \n"
   " } \0";

    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    
    glCompileShader(vertexShader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource =
   " #version 410 core \n"
   " out vec4 FragColor;\n"
   "void main() \n"
    "{ FragColor = vec4(1.0f,0.5f,0.2f,1.0f); } \0";
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    
    
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "link failed.\n";
    }
    
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    while(!glfwWindowShouldClose(window))
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(my_traingle_vao);
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES,0,3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}
