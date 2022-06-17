void DisenaSuperficie(void);

// ----------------------------------------------------------------------------
// OBSERVACAO 1:
//     Definir as matrizes BASE
// ----------------------------------------------------------------------------

void MostrarUmPatch(int cc)
{
    int i, j;
    float t, v, s;
    f4d a, b, n, l;

    if (!ptsPatch)
        return;

    switch (tipoVisualisacao)
    {
    case GL_POINTS:
        glColor3f(0.0f, 0.0f, 0.7f);
        glPointSize(1.0);
        for (i = 0; i < ptsPatch->n; i++)
        {
            glBegin(tipoVisualisacao);
            for (j = 0; j < ptsPatch->m; j++)
                glVertex3fv(ptsPatch->ponto[i][j]);
            glEnd();
        }
        break;

    case GL_LINE_STRIP:
        glColor3f(0.0f, 0.0f, 0.7f);
        for (i = 0; i < ptsPatch->n; i++)
        {
            glBegin(tipoVisualisacao);
            for (j = 0; j < ptsPatch->m; j++)
                glVertex3fv(ptsPatch->ponto[i][j]);
            glEnd();
        }

        for (j = 0; j < ptsPatch->n; j++)
        {
            glBegin(tipoVisualisacao);
            for (i = 0; i < ptsPatch->m; i++)
                glVertex3fv(ptsPatch->ponto[i][j]);
            glEnd();
        }
        break;

    case GL_QUADS:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (i = 0; i < ptsPatch->n - 1; i++)
        {
            for (j = 0; j < ptsPatch->m - 1; j++)
            {

                // -----------------------------------------------------
                // OBSERVACAO 2: modificar
                //  Ver a melhor forma de criar triangulos 1ro e 2do
                // -----------------------------------------------------

                // criando 1ro triangulo do quadrilatero

                a[X] = ptsPatch->ponto[i + 1][j][X] - ptsPatch->ponto[i][j][X];
                a[Y] = ptsPatch->ponto[i + 1][j][Y] - ptsPatch->ponto[i][j][Y];
                a[Z] = ptsPatch->ponto[i + 1][j][Z] - ptsPatch->ponto[i][j][Z];

                b[X] = ptsPatch->ponto[i][j + 1][X] - ptsPatch->ponto[i][j][X];
                b[Y] = ptsPatch->ponto[i][j + 1][Y] - ptsPatch->ponto[i][j][Y];
                b[Z] = ptsPatch->ponto[i][j + 1][Z] - ptsPatch->ponto[i][j][Z];

                n[X] = a[Y] * b[Z] - a[Z] * b[Y];
                n[Y] = a[Z] * b[X] - a[X] * b[Z];
                n[Z] = a[X] * b[Y] - a[Y] * b[X];

                s = sqrt(n[X] * n[X] + n[Y] * n[Y] + n[Z] * n[Z]);

                n[X] /= s;
                n[Y] /= s;
                n[Z] /= s;

                l[X] = pView[X] - ptsPatch->ponto[i][j][X];
                l[Y] = pView[Y] - ptsPatch->ponto[i][j][Y];
                l[Z] = pView[Z] - ptsPatch->ponto[i][j][Z];

                s = n[X] * l[X] + n[Y] * l[Y] + n[Z] * l[Z];

                v = sqrt(l[X] * l[X] + l[Y] * l[Y] + l[Z] * l[Z]);
                t = s / v;

                if (t < 0.0f)
                    t *= -1.00f;

                glBegin(GL_POLYGON);
                glColor3f(t * vcolor[cc][X], t * vcolor[cc][Y], t * vcolor[cc][Z]);
                glNormal3fv(n);
                glVertex3fv(ptsPatch->ponto[i][j]);
                glVertex3fv(ptsPatch->ponto[i][j + 1]);
                glVertex3fv(ptsPatch->ponto[i + 1][j]);
                glEnd();

                // criando 2do triangulo

                a[X] = ptsPatch->ponto[i][j + 1][X] - ptsPatch->ponto[i + 1][j + 1][X];
                a[Y] = ptsPatch->ponto[i][j + 1][Y] - ptsPatch->ponto[i + 1][j + 1][Y];
                a[Z] = ptsPatch->ponto[i][j + 1][Z] - ptsPatch->ponto[i + 1][j + 1][Z];

                b[X] = ptsPatch->ponto[i + 1][j][X] - ptsPatch->ponto[i + 1][j + 1][X];
                b[Y] = ptsPatch->ponto[i + 1][j][Y] - ptsPatch->ponto[i + 1][j + 1][Y];
                b[Z] = ptsPatch->ponto[i + 1][j][Z] - ptsPatch->ponto[i + 1][j + 1][Z];

                n[X] = a[Y] * b[Z] - a[Z] * b[Y];
                n[Y] = a[Z] * b[X] - a[X] * b[Z];
                n[Z] = a[X] * b[Y] - a[Y] * b[X];

                s = sqrt(n[X] * n[X] + n[Y] * n[Y] + n[Z] * n[Z]);

                n[X] /= s;
                n[Y] /= s;
                n[Z] /= s;

                l[X] = pView[X] - ptsPatch->ponto[i + 1][j + 1][X];
                l[Y] = pView[Y] - ptsPatch->ponto[i + 1][j + 1][Y];
                l[Z] = pView[Z] - ptsPatch->ponto[i + 1][j + 1][Z];

                s = n[X] * l[X] + n[Y] * l[Y] + n[Z] * l[Z];

                v = sqrt(l[X] * l[X] + l[Y] * l[Y] + l[Z] * l[Z]);
                t = s / v;

                if (t < 0.0f)
                    t *= -1.00f;

                glBegin(GL_POLYGON);
                glColor3f(t * vcolor[cc][X], t * vcolor[cc][Y], t * vcolor[cc][Z]);
                glNormal3fv(n);
                glVertex3fv(ptsPatch->ponto[i][j + 1]);
                glVertex3fv(ptsPatch->ponto[i + 1][j + 1]);
                glVertex3fv(ptsPatch->ponto[i + 1][j]);
                glEnd();
            }
        }
        break;
    }
}
void MostrarPtosPoligControle(matriz *sup)
{
    int i, j;

    glColor3f(0.0f, 0.8f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, tipoVisualisacao);
    glPointSize(7.0);
    for (i = 0; i < sup->n; i++)
    {
        glBegin(GL_POINTS);
        for (j = 0; j < sup->m; j++)
            glVertex3fv(sup->ponto[i][j]);
        glEnd();

        glBegin(GL_LINE_STRIP);
        for (j = 0; j < sup->m; j++)
            glVertex3fv(sup->ponto[i][j]);
        glEnd();
    }

    for (i = 0; i < sup->m; i++)
    {
        glBegin(GL_LINE_STRIP);
        for (j = 0; j < sup->n; j++)
            glVertex3fv(sup->ponto[j][i]);
        glEnd();
    }
}

void DisenaSuperficie(void)
{
    int i, j, nn, mm, idCor;

    nn = pControle->n - 3; // numero de descolamentos (patchs)

    for (i = 0; i < nn; i++)
    {
        mm = pControle->m - 3;
        for (j = 0; j < mm; j++)
        {
            copiarPtosControlePatch(i, j, pcPatch); // copiar ptos de controle em matriz 4 x 4
            ptsSuperficie(pcPatch);                 // calculos pontos do PATCH com os ptos de Contrle em pcPatch
            idCor = (i + j) % 4;                    // indice de paleta de COR
            MostrarUmPatch(idCor);
        }
    }
}

void reshape(int w, int h)
{
    windW = w / 2;
    windH = h / 2;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
                10.0 * (GLfloat)h / (GLfloat)w, -10.0, 30.0);
    else
        glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
                10.0 * (GLfloat)w / (GLfloat)h, -10.0, 10.0, -10.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}
