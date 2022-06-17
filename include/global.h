#define Linha -1
#define Solido -2
#define Pontos -3

#define X 0
#define Y 1
#define Z 2
#define W 3

#define Escalar 4 // Redimensionar

#define RotarX 5
#define RotarY 6
#define RotarZ 7
#define Rotação 71

#define TransladaX 8
#define TransladaY 9
#define TransladaZ 10
#define Translada 101

#define PontosControle 19
#define BEZIER 20
#define BSPLINE 21
#define CATMULLROM 22

#define sair 0
int windW, windH;
int gIndVert = -1;
bool preenchido = 0;  // se o poligono esta preenchido
typedef float f4d[4]; // 4d

typedef struct st_matriz
{
    int n, m;
    f4d **ponto;
} matriz;

int comando;

int tipoVisualisacao = GL_LINE_STRIP;

float local_scale = 0.22f; // Escala local

float VARIA = 0.1f; // Variação de escala

f4d matTransf[4]; // matriz transposta 4 x 4

f4d MatBase[4]; // matriz de base 4x4

f4d pView = {100.0, 10.0, -20.0, 0.0};

// ---------------------------------------------
// OBSERVACAO 0: cores
//       definir mais cores
// ---------------------------------------------

f4d vcolor[1] = {
    {0.0, 1.0, 0.0, 0.0},
};

matriz *pControle = NULL; // matriz de pontos de controle

matriz *pcPatch = NULL; // matriz de pontos para um patch

matriz *ptsPatch = NULL; // matriz de PONTOS na superficie PATCH

#define SENS_ROT 10.0 // Define = Valor constante em C
#define SENS_OBS 10.0
#define SENS_TRANS 10.0

#define PASSO_TEMP 0.1 // passo de tempo para integrar ODE por Euler

#define MAXPARTICULAS 10000
#define randomico() ((float)rand() / RAND_MAX) // Numero aleatorio entre 0 e 1

GLfloat ASPECTO,
    ANGULO;
GLfloat obsX, obsY, obsZ;             // posicao do observador (obsX, obsY, obsZ)
GLfloat rotX, rotY;                   // Angulos de Orientacao x , y (rotX, rotY) na naiz do observador
GLfloat obsX_ini, obsY_ini, obsZ_ini; // caso de transformacao (posicao inicia para se obter nova posicao)
GLfloat rotX_ini, rotY_ini;           // angulos de orientacao inicial para transformacao
GLfloat escalaX, escalaY, escalaZ;    // fatores de escala para trasnformacao

int x_ini, y_ini, bot;
int origemX, origemY;

// PARTÍCULAS=======================================================================================
typedef struct
{
    GLfloat pos[3];
    GLfloat vel[3];
    GLfloat ace[3];
    GLfloat massa;
    GLfloat cor[3];
    GLfloat tempoVida;
    GLfloat transparencia;
} part2;

part2 Particulas[MAXPARTICULAS];