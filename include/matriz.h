void MontaMatrizBase(int TipoDeSuperficie)
{
    if (TipoDeSuperficie == BEZIER)
    {
        MatBase[0][0] = -1.0f;
        MatBase[0][1] = 3.0f;
        MatBase[0][2] = -3.0f;
        MatBase[0][3] = 1.0f;
        MatBase[1][0] = 3.0f;
        MatBase[1][1] = -6.0f;
        MatBase[1][2] = 3.0f;
        MatBase[1][3] = 0.0f;
        MatBase[2][0] = -3.0f;
        MatBase[2][1] = 3.0f;
        MatBase[2][2] = 0.0f;
        MatBase[2][3] = 0.0f;
        MatBase[3][0] = 1.0f;
        MatBase[3][1] = 0.0f;
        MatBase[3][2] = 0.0f;
        MatBase[3][3] = 0.0f;
    }

    if (TipoDeSuperficie == BSPLINE)
    {
        MatBase[0][0] = -1.0f / 6.0;
        MatBase[0][1] = 3.0f / 6.0;
        MatBase[0][2] = -3.0f / 6.0;
        MatBase[0][3] = 1.0f / 6.0;
        MatBase[1][0] = 3.0f / 6.0;
        MatBase[1][1] = -6.0f / 6.0;
        MatBase[1][2] = 3.0f / 6.0;
        MatBase[1][3] = 0.0f;
        MatBase[2][0] = -3.0f / 6.0;
        MatBase[2][1] = 0.0f / 6.0;
        MatBase[2][2] = 3.0f / 6.0;
        MatBase[2][3] = 0.0f;
        MatBase[3][0] = 1.0f / 6.0;
        MatBase[3][1] = 4.0f / 6.0;
        MatBase[3][2] = 1.0f / 6.0;
        MatBase[3][3] = 0.0;
    }

    if (TipoDeSuperficie == CATMULLROM)
    {
        MatBase[0][0] = -1.0f / 2.0;
        MatBase[0][1] = 3.0f / 2.0;
        MatBase[0][2] = -3.0f / 2.0;
        MatBase[0][3] = 1.0f / 2.0;
        MatBase[1][0] = 2.0f / 2.0;
        MatBase[1][1] = -5.0f / 2.0;
        MatBase[1][2] = 4.0f / 2.0;
        MatBase[1][3] = -1.0f / 2.0;
        MatBase[2][0] = -1.0f / 2.0;
        MatBase[2][1] = 0.0f / 2.0;
        MatBase[2][2] = 1.0f / 2.0;
        MatBase[2][3] = 0.0f / 2.0;
        MatBase[3][0] = 0.0f / 2.0;
        MatBase[3][1] = 2.0f / 2.0;
        MatBase[3][2] = 0.0f / 2.0;
        MatBase[3][3] = 0.0f / 2.0;
    }
}

matriz *liberaMatriz(matriz *sup)
{
    int i;

    if (sup)
    {
        for (i = 0; i < sup->n; i++)
            free(sup->ponto[i]);

        free(sup->ponto);
        free(sup);
    }
    return NULL;
}

matriz *AlocaMatriz(int n, int m)
{
    matriz *matTemp;
    int j;

    if ((matTemp = (matriz *)malloc(sizeof(matriz))) == NULL)
    {
        printf("\n Error en alocacion de memoria para uma matriz");
        return 0;
    }

    matTemp->n = n;
    matTemp->m = m;
    matTemp->ponto = (f4d **)calloc(n, sizeof(f4d *));

    for (j = 0; j < matTemp->n; j++)
        matTemp->ponto[j] = (f4d *)calloc(m, sizeof(f4d));

    return matTemp;
}

void MatrizIdentidade()
{
    int a, b;
    for (a = 0; a < 4; a++)
    {
        for (b = 0; b < 4; b++)
        {
            if (a == b)
                matTransf[a][b] = 1;
            else
                matTransf[a][b] = 0;
        }
    }
}

void MultMatriz()
{
    int j, k;
    f4d aux;
    for (j = 0; j < pControle->n; j++)
    {
        for (k = 0; k < pControle->m; k++)
        {
            aux[X] = pControle->ponto[j][k][X];
            aux[Y] = pControle->ponto[j][k][Y];
            aux[Z] = pControle->ponto[j][k][Z];
            aux[W] = 1.0; // pControle->ponto[j][k][W];

            //  Pj = MatTransf4x4 . Pj  <--- transformada homogenea

            pControle->ponto[j][k][X] = matTransf[X][X] * aux[X] +
                                        matTransf[Y][X] * aux[Y] +
                                        matTransf[Z][X] * aux[Z] +
                                        matTransf[W][X] * aux[W];

            pControle->ponto[j][k][Y] = matTransf[X][Y] * aux[X] +
                                        matTransf[Y][Y] * aux[Y] +
                                        matTransf[Z][Y] * aux[Z] +
                                        matTransf[W][Y] * aux[W];

            pControle->ponto[j][k][Z] = matTransf[X][Z] * aux[X] +
                                        matTransf[Y][Z] * aux[Y] +
                                        matTransf[Z][Z] * aux[Z] +
                                        matTransf[W][Z] * aux[W];

            pControle->ponto[j][k][W] = matTransf[X][W] * aux[X] +
                                        matTransf[Y][W] * aux[Y] +
                                        matTransf[Z][W] * aux[Z] +
                                        matTransf[W][W] * aux[W];
        }
    }
}