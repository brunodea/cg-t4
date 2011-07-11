/*
    Bruno Romero de Azevedo
    2910098
 */
#include "glfw.h"
#include <cstdlib>

#include "macros.h"
#include "Controller/Controller.h"

/*
 * Callback functions
 */
void GLFWCALL keyEventCallback(int key, int state)
{
    CONTROLLER->onKeyPressed(key, state);
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.f,(float)width/(float)height,0.1,5000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallBacks()
{
    glfwSetKeyCallback(keyEventCallback);
    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGLLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    GLfloat mat_env[] = {1.f,1.f,1.f,1.f}; //material ambiente.
    GLfloat mat_dif[] = {.7f,.4f,.0f,1.f}; //material difusa.
    //GLfloat mat_spe[] = {1.f,1.f,1.f,1.f}; //material especular.
    GLfloat mat_shi = 50.f; //material brilho.

    GLfloat light_pos[] = {100.f,100.f,100.f,1.f}; //posicao da luz.
    GLfloat light_env[] = {.1f,.1f,.1f,1.f}; //luz ambiente.
    GLfloat light_dif[] = {1.f,1.f,1.f,1.f}; //luz difusa.
    GLfloat light_spe[] = {1.f,1.f,1.f,1.f}; //luz especular.

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_env);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spe);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shi);
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_env);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spe);
}

void initOpenGL()
{
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    initOpenGLLighting();
    glClearColor(0.f, 0.f, 0.f, 1.f);
}

void clear()
{
    delete CONTROLLER;
}

void help()
{
    std::cout << "<<<<<<<<<<<<<<<<< Munck Munk >>>>>>>>>>>>>>>>>\n";
    std::cout << "                    Help                      \n";
    std::cout << "-------------------- Bruno Romero de Azevedo -\n";
    std::cout << "1)Braco:\n";
    std::cout << "1.1)Braco ativo: Braco pintado de VERDE.\n";
    std::cout << "1.2)Cima/Baixo: Muda o braco ativo.\n";
    std::cout << "1.3)Esquerda/Direita: Rotaciona o braco ativo.\n";
    std::cout << "1.4)CtrlDireita/CtrlEsquerda: Estica/encolhe o braco ativo.\n";

    std::cout << "2)Camera:\n";
    std::cout << "2.1)Tipos de camera:\n";
    std::cout << "2.1.1)F2: Camera livre (sem rotacao).\n";
    std::cout << "2.1.1.1)W/S/A/D: Move para frente/tras e esquerda/direita a camera.\n";
    std::cout << "2.1.1.2)Z/X: Move para Cima/Baixo a camera.\n";
    std::cout << "2.1.2)F3: Camera do lado caminhao.\n";
    std::cout << "2.1.3)F4: Camera por tras do caminhao.\n";

    std::cout << "3)Caminhao:\n";
    std::cout << "3.1)I/K: Para frente/tras.\n";
    std::cout << "3.2)J/L: Rotaciona para esquerda/direita.\n";
    std::cout << "3.3)1/2: Rotaciona os bracos.\n";
    std::cout << "3.4)PageUp/PageDown: Adiciona/Remove um braco. (min=2)\n";

    std::cout << "4)Cena:\n";
    std::cout << "4.1)F1: wireframe->solid/solid->wireframe.\n";

    std::cout << "###########################################################\n";
}

int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    initOpenGL();
    setCallBacks();
    help();

    CONTROLLER->run();

    clear();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

