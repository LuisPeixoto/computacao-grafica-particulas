#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>

#include "./include/global.h"
#include "./include/matriz.h"
#include "./include/carregaPontos.h"
#include "./include/menu.h"
#include "./include/teclado.h"
#include "./include/operacoes.h"
#include "./include/mostra.h"
#include "./include/particula.h"

void display(void) // Desenha a superficie
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    if (pControle)
    {
        MostrarPtosPoligControle(pControle); // mostrando pontos de controle
        DisenaSuperficie();
        desenhaTudo();
        // disenhando un objeto
    }

    glutSwapBuffers();
}

void motion(int x, int y)
{
    int deltaX, deltaY;
    if (bot == GLUT_LEFT_BUTTON)
    { // Rotação
        deltaX = x_ini - x;
        deltaY = y_ini - y;

        rotX = rotX_ini - deltaY / SENS_ROT;
        rotY = rotY_ini - deltaX / SENS_ROT;
    }
    else if (bot == GLUT_RIGHT_BUTTON)
    { // Zoom
        int deltaZ = y_ini - y;
        obsZ = obsZ_ini + deltaZ / SENS_OBS;
    }
    else if (bot == GLUT_MIDDLE_BUTTON)
    { // Correr
        deltaX = x_ini - x;
        deltaY = y_ini - y;

        obsX = obsX_ini + deltaX / SENS_TRANS;
        obsY = obsY_ini + deltaY / SENS_TRANS;
    }
    posicionaObservador();
    glutPostRedisplay();
}

void redesenhaPrimitivas(GLsizei largura, GLsizei altura)
{
    if (altura == 0)
        altura = 1;

    glViewport(0, 0, largura, altura); // defina tamanho de viewport - canvas

    ASPECTO = (GLfloat)largura / (GLfloat)altura; // calcula acorrecao de aspecto

    especificaParametrosVisuais();
}

void idleF(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);        // cor de fundo
    glEnable(GL_DEPTH_TEST);                 // habilita teste de profundidade
    glEnable(GL_MAP2_VERTEX_3);              // habilita mapa de função de vértices
    glEnable(GL_AUTO_NORMAL);                // habilita normal automática
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); // define grade de mapa

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    ANGULO = 45;

    rotX = 0;
    rotY = 0;

    obsX = 1;
    obsY = 1;
    obsZ = 40;

    escalaX = 1;
    escalaY = 1;
    escalaZ = 1;

    iniciaParticulas();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv); // inicializa o glut

    glutInitWindowSize(700, 700); // define tamanho da janela
    glutInitWindowPosition(3, 3);
    glutCreateWindow("Sistema de Particulas");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutReshapeFunc(reshape);  // define função de redimensionamento
    glutSpecialFunc(keyboard); // define função de teclado

    glutDisplayFunc(display); // define função de desenho
    createGLUTMenus();        // cria menus

    // glutReshapeFunc(redesenhaPrimitivas);
    //   glutMouseFunc(mouse);
    //  glutMotionFunc(motion);
    glutIdleFunc(idleF); // fun?ão de animacao

    init(); // inicializa a cena

    glutMainLoop();

    return 0;
}