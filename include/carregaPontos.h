int CarregaPontos(char *arch)
{
    FILE *fobj;
    char token[40];
    float px, py, pz;
    int i, j, n, m;

    printf(" \n ler  %s  \n", arch);

    if ((fobj = fopen(arch, "rt")) == NULL)
    {
        printf("Error en la apertura del archivo %s \n", arch);
        return 0;
    }

    fgets(token, 40, fobj);
    fscanf(fobj, "%s %d %d", token, &n, &m);

    if (pControle)
        pControle = liberaMatriz(pControle);

    pControle = AlocaMatriz(n, m);

    fscanf(fobj, "%s", token); // leitura da linha 0

    for (j = 0; j < pControle->n; j++)
    {
        for (i = 0; i < pControle->m; i++)
        {
            fscanf(fobj, "%s %f %f %f", token, &px, &py, &pz);

            pControle->ponto[j][i][0] = px * local_scale;
            pControle->ponto[j][i][1] = py * local_scale;
            pControle->ponto[j][i][2] = pz * local_scale;
            pControle->ponto[j][i][3] = 1.0f;
        }
        fscanf(fobj, "%s", token); // leitura da linha j+1;
    }

    // espaco de matriz para um patch
    if (pcPatch)
        pcPatch = liberaMatriz(pcPatch);
    pcPatch = AlocaMatriz(4, 4);
}

int GeraPontosAleatorios()
{
    // int random_number = rand() % 50 + 0;
    FILE *fobj;
    char token[40];
    float px, py, pz;
    int i, j, n, m;

    n = 4;
    m = 4;

    if (pControle)
        pControle = liberaMatriz(pControle);

    pControle = AlocaMatriz(n, m);

    for (j = 0; j < pControle->n; j++)
    {
        for (i = 0; i < pControle->m; i++)
        {

            pControle->ponto[j][i][0] = (px + rand() % 50 + 0 - (rand() % 50 + 0)) * local_scale;
            pControle->ponto[j][i][1] = (py + rand() % 50 + 0 - (rand() % 50 + 0)) * local_scale;
            pControle->ponto[j][i][2] = (pz + rand() % 50 + 0 - (rand() % 50 + 0)) * local_scale;
            pControle->ponto[j][i][3] = 1.0f;
        }
    }

    // espaco de matriz para um patch
    if (pcPatch)
        pcPatch = liberaMatriz(pcPatch);
    pcPatch = AlocaMatriz(4, 4);
}