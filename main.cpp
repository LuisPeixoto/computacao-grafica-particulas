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

// ---------------------------------------------
// OBSERVACAO 0: cores
//       definir mais cores
// ---------------------------------------------

// ----------------------------------------------------------------------------
// OBSERVACAO 1:
//     Definir as matrizes BASE
// ----------------------------------------------------------------------------

// -----------------------------------------------------
// OBSERVACAO 2: modificar
//  Ver a melhor forma de criar triangulos 1ro e 2do
// -----------------------------------------------------

//-------------------------------------------------------
// OBSERVACAO 3:
// Considerar Rotacao no eixo Y  e  Z
// -----------------------------------------------------

//-------------------------------------------------------
// OBSERVACAO 4:
// Considerar Tranlacao no eixo X  y  Z
// -----------------------------------------------------

// -----------------------------------------------------
// OBSERVACAO 5:
// colocar opcao para CatmullRom
// -----------------------------------------------------

// ----------------------------------------------------
// OBSERVACAO 6:
// Considerar opcao de Rotacao em Y e Z
// ------------------------------------------------------

// ----------------------------------------------------
// OBSERVACAO 7:
// Considerar opcao de Translacao em Y e Z
// ------------------------------------------------------

void conceberParticulas(int i)
{
    // GLfloat r, alpha;   //Raio, Angulo
    GLfloat alpha, beta;
    GLfloat raio = 0.1 * randomico() + 0.06;
    alpha = 2 * M_PI * randomico();
    beta = M_PI * randomico();

    // Coordenadas do ponto de origem da particulas
    Particulas[i].pos[0] = rand() % 8 - 4;
    ;                                      // posicao em x
    Particulas[i].pos[1] = 5.0;            // posicao em y
    Particulas[i].pos[2] = rand() % 2 - 2; // posicao em z

    Particulas[i].vel[0] = raio * cos(alpha) * sin(beta); // velocidade em x
    Particulas[i].vel[1] = raio * cos(beta);              // velocidade em y
    Particulas[i].vel[2] = raio * sin(alpha) * sin(beta); // velocidade em z

    Particulas[i].ace[0] = 0.0;   // acelera em x
    Particulas[i].ace[1] = 0.025; // acelera em y
    Particulas[i].ace[2] = 0.0;   // acelera em z

    Particulas[i].massa = 0.01 * randomico(); // massa da particula

    Particulas[i].cor[0] = randomico();       // R
    Particulas[i].cor[1] = 0.1 * randomico(); // G
    Particulas[i].cor[2] = 0.01 * randomico();
    ; // B

    Particulas[i].tempoVida = 0.8 + 0.98 * randomico(); // define o tempo de vida da particula
    Particulas[i].transparencia = 1.0;                  // grau de transaperencia da particula
}

void extinguirParticulas(int i)
{
    if (Particulas[i].tempoVida < 0.001)
    {
        conceberParticulas(i);
    }
}

void iniciaParticulas(void)
{
    int i;

    for (i = 0; i < MAXPARTICULAS; i++)
    {
        conceberParticulas(i);
    }
}

void posicionaObservador(void)
{
    glMatrixMode(GL_MODELVIEW); // Coordenadas na matrix de visualizacao
    glLoadIdentity();

    // Posiciona e orienta o observador
    glTranslatef(-obsX, -obsY, -obsZ); // Translata a camera para essas variaveis
    glRotatef(rotX, 1, 0, 0);          // Rotacionar a camera para essas coordenadas
    glRotatef(rotY, 0, 1, 0);
}

void especificaParametrosVisuais(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(ANGULO, ASPECTO, 0.5, 500);

    posicionaObservador();
}

void disco(GLfloat raioInf, GLfloat raioSup, GLfloat alt)
{
    GLUquadricObj *q = gluNewQuadric();
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluQuadricTexture(q, GL_TRUE);
    gluCylinder(q, raioInf, raioSup, alt, 60, 60);
    gluDeleteQuadric(q);
}

void desenhaPlano()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5); // Desenha na cor cinza
    glMatrixMode(GL_MODELVIEW);

    glutWireCube(10.0); // desenha cubo com tamanho igual a 10

    glFlush();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix(); // empilha a matriz de operacao
    glColor3f(0.5f, 0.7f, 0.6f);
    glTranslatef(0.0, 5.0, 0.0);               // Translada (x,y,z)
    glRotatef(-90.0, 1.0, 0.0, 0.0);           // Rotaciona (1,0,0) en Angulo
    glScalef(escalaX, escalaY - 0.5, escalaZ); // Escala
    disco(4.0, 0.0, 0.0);                      // gera um disco (cilinro) de raio inferio 4, raio sup 0 e altura 0
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void desenhaParticula2(void)
{
    int i;

    glDisable(GL_DEPTH_TEST);                          //"Rastro"
    glEnable(GL_BLEND);                                // Habilita a transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                 // Ativa a Transparência
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Perspectiva

    for (i = 0; i < MAXPARTICULAS; i++)
    {
        glColor4f(Particulas[i].cor[0], Particulas[i].cor[1], Particulas[i].cor[2], Particulas[i].transparencia);
        glPointSize(2.0);
        glPushMatrix();
        glBegin(GL_POINTS);
        glVertex3f(Particulas[i].pos[0], Particulas[i].pos[1], Particulas[i].pos[2]);
        glEnd();
        glPopMatrix();

        // calculando EDO com Euler
        Particulas[i].pos[0] += PASSO_TEMP * Particulas[i].vel[0];
        Particulas[i].pos[1] += PASSO_TEMP * Particulas[i].vel[1];
        Particulas[i].pos[2] += PASSO_TEMP * Particulas[i].vel[2];

        Particulas[i].vel[0] += PASSO_TEMP * Particulas[i].ace[0];
        Particulas[i].vel[1] += PASSO_TEMP * Particulas[i].ace[1];
        Particulas[i].vel[2] += PASSO_TEMP * Particulas[i].ace[2];

        Particulas[i].tempoVida -= 0.01;
        Particulas[i].transparencia -= 0.01;
        extinguirParticulas(i);
    }
    glDisable(GL_BLEND);
}

void desenhaTudo(void)
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //  desenhaPlano();
    desenhaParticula2();
    glutSwapBuffers();
}

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