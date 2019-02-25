#include <glm/gtc/matrix_transform.hpp>

#include "./common/OpenGLWindow.h"

#include "./common/shader.h"
#include "./common/shaderProgram.h"
#include "./common/vertexBufferObject.h"
#include "staticGeometry.h"
#include "./common/flyingCamera.h"

Shader vertexShader, fragmentShader;
ShaderProgram mainProgram;
VertexBufferObject shapesVBO;
VertexBufferObject colorsVBO;

GLuint mainVAO;

//FlyingCamera camera(glm::vec3(0.0f, 8.0f, 20.0f), glm::vec3(0.0f, 8.0f, 19.0f), glm::vec3(0.0f, 1.0f, 0.0f));
FlyingCamera camera(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
float rotationAngleRad; // in radians

void OpenGLWindow::initializeScene()
{
    glClearColor(0.0f, 0.28f, 0.57f, 1.0f);

    vertexShader.loadShaderFromFile("data/shaders/tut004/shader.vert", GL_VERTEX_SHADER);
    fragmentShader.loadShaderFromFile("data/shaders/tut004/shader.frag", GL_FRAGMENT_SHADER);

    if (!vertexShader.isLoaded() || !fragmentShader.isLoaded())
    {
        closeWindow(true);
        return;
    }

    mainProgram.createProgram();
    mainProgram.addShaderToProgram(vertexShader);
    mainProgram.addShaderToProgram(fragmentShader);

    if (!mainProgram.linkProgram())
    {
        closeWindow(true);
        return;
    }

    glGenVertexArrays(1, &mainVAO); // Creates one Vertex Array Object
    glBindVertexArray(mainVAO);

    // Setup vertex positions first

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
}

void OpenGLWindow::renderScene()
{
    shapesVBO.deleteVBO();
    shapesVBO.createVBO();
    shapesVBO.bindVBO();

    shapesVBO.addData(static_geometry::armLines, sizeof(static_geometry::armLines));
    shapesVBO.addData(static_geometry::armSpheres, sizeof(static_geometry::armSpheres));

    shapesVBO.addData(static_geometry::jointsPolygonVertices, sizeof(static_geometry::jointsPolygonVertices));

    shapesVBO.addData(static_geometry::fingerThumbBonesLines, sizeof(static_geometry::fingerThumbBonesLines));
    shapesVBO.addData(static_geometry::fingerIndexBonesLines, sizeof(static_geometry::fingerIndexBonesLines));
    shapesVBO.addData(static_geometry::fingerMiddleBonesLines, sizeof(static_geometry::fingerMiddleBonesLines));
    shapesVBO.addData(static_geometry::fingerRingBonesLines, sizeof(static_geometry::fingerRingBonesLines));
    shapesVBO.addData(static_geometry::fingerPinkyBonesLines, sizeof(static_geometry::fingerPinkyBonesLines));

    shapesVBO.addData(static_geometry::fingerThumbJointSphere, sizeof(static_geometry::fingerThumbJointSphere));
    shapesVBO.addData(static_geometry::fingerIndexJointSphere, sizeof(static_geometry::fingerIndexJointSphere));
    shapesVBO.addData(static_geometry::fingerMiddleJointSphere, sizeof(static_geometry::fingerMiddleJointSphere));
    shapesVBO.addData(static_geometry::fingerRingJointSphere, sizeof(static_geometry::fingerRingJointSphere));
    shapesVBO.addData(static_geometry::fingerPinkyJointSphere, sizeof(static_geometry::fingerPinkyJointSphere));

    shapesVBO.uploadDataToGPU(GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    // Setup colors now
    colorsVBO.deleteVBO();
    colorsVBO.createVBO();
    colorsVBO.bindVBO();
    colorsVBO.addData(static_geometry::armLines, sizeof(static_geometry::armLines));
    colorsVBO.addData(static_geometry::armSpheres, sizeof(static_geometry::armSpheres));

    colorsVBO.addData(static_geometry::jointsPolygonColor, sizeof(static_geometry::jointsPolygonColor));

    colorsVBO.addData(static_geometry::fingerThumbBonesLinesColor, sizeof(static_geometry::fingerThumbBonesLinesColor));
    colorsVBO.addData(static_geometry::fingerIndexBonesLinesColor, sizeof(static_geometry::fingerIndexBonesLinesColor));
    colorsVBO.addData(static_geometry::fingerMiddleBonesLinesColor, sizeof(static_geometry::fingerMiddleBonesLinesColor));
    colorsVBO.addData(static_geometry::fingerRingBonesLinesColor, sizeof(static_geometry::fingerRingBonesLinesColor));
    colorsVBO.addData(static_geometry::fingerPinkyBonesLinesColor, sizeof(static_geometry::fingerPinkyBonesLinesColor));

    colorsVBO.addData(static_geometry::fingerThumbJointSphereColor, sizeof(static_geometry::fingerThumbJointSphereColor));
    colorsVBO.addData(static_geometry::fingerIndexJointSphereColor, sizeof(static_geometry::fingerIndexJointSphereColor));
    colorsVBO.addData(static_geometry::fingerMiddleJointSphere, sizeof(static_geometry::fingerMiddleJointSphereColor));
    colorsVBO.addData(static_geometry::fingerRingJointSphere, sizeof(static_geometry::fingerRingJointSphereColor));
    colorsVBO.addData(static_geometry::fingerPinkyJointSphere, sizeof(static_geometry::fingerPinkyJointSphereColor));

    colorsVBO.uploadDataToGPU(GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainProgram.useProgram();
    glBindVertexArray(mainVAO);

    mainProgram["matrices.projectionMatrix"] = getProjectionMatrix();
    mainProgram["matrices.viewMatrix"] = camera.getViewMatrix();

    // Render ground
    mainProgram["matrices.modelMatrix"] = glm::mat4(1.0);

    std::cout << "x: " << static_geometry::armLines[0].x
            << "y: " << static_geometry::armLines[0].y
            << "z: " << static_geometry::armLines[0].z
            << std::endl;
    glDrawArrays(GL_LINES,0,2); //arm lines
    glDrawArrays(GL_POINTS,2,2); // arm spheres
    glDrawArrays(GL_LINES,4,6); // thumb
    glDrawArrays(GL_LINES,10,8); // index
    glDrawArrays(GL_LINES,18,8); // middle
    glDrawArrays(GL_LINES,26,8); // ring
    glDrawArrays(GL_LINES,34,8); // pinky

    std::string windowTitleWithFPS = "006.) Camera pt. 2 - Flying Camera - Tutorial by Michal Bubnar (www.mbsoftworks.sk) - FPS: "
                                     + std::to_string(getFPS()) +
                                     ", VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off") + " (Press F3 to toggle)";
    glfwSetWindowTitle(getWindow(), windowTitleWithFPS.c_str());
}

void OpenGLWindow::releaseScene()
{
    mainProgram.deleteProgram();

    vertexShader.deleteShader();
    fragmentShader.deleteShader();

    shapesVBO.deleteVBO();
    colorsVBO.deleteVBO();

    glDeleteVertexArrays(1, &mainVAO);
}

void OpenGLWindow::handleInput()
{
    if (keyPressedOnce(GLFW_KEY_ESCAPE)) {
        closeWindow();
    }

    if (keyPressedOnce(GLFW_KEY_F3)) {
        setVerticalSynchronization(!isVerticalSynchronizationEnabled());
    }

    int posX, posY, width, height;
    glfwGetWindowPos(getWindow(), &posX, &posY);
    glfwGetWindowSize(getWindow(), &width, &height);
    camera.setWindowCenterPosition(glm::i32vec2(posX + width / 2, posY + height / 2));

    camera.update([this](int keyCode) {return this->keyPressed(keyCode); },
                  [this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
                  [this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); },
                  [this](float f) {return this->sof(f); });
}

void OpenGLWindow::onWindowSizeChanged(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
