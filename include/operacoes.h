void prod_VetParam_MatBase(float t, float *tt, float *vr) // produto vetorial parametrizado por uma matriz base
{
    int i, j;

    // Vr = [t^3  t^2  t  1] [MatBase]4x4  <-- base avaliado em t.
    // ---------------------------------------------------------
    tt[0] = pow(t, 3);
    tt[1] = pow(t, 2);
    tt[2] = t;
    tt[3] = 1.0;

    for (i = 0; i < 4; i++)
    {
        vr[i] = 0.0f;
        for (j = 0; j < 4; j++)
            vr[i] += MatBase[j][i] * tt[j];
    }
}

void prod_VetMatriz(float *v, f4d **pc, f4d *vr) //  produto vetorial da matriz
{
    int i, j;

    // Vr = V . P   <----- combinacao linear
    // --------------------------------------
    for (i = 0; i < 4; i++)
    {
        vr[i][0] = vr[i][1] = vr[i][2] = 0.0;
        for (j = 0; j < 4; j++)
        {
            vr[i][0] += v[j] * pc[j][i][0];
            vr[i][1] += v[j] * pc[j][i][1];
            vr[i][2] += v[j] * pc[j][i][2];
        }
    }
}

void ptsSuperficie(matriz *pcPatch) // calcula os pontos da superficie
{
    int i, j, h, n, m;
    float t, s;
    float tmp[4], vsm[4], vtm[4];
    f4d va[4];

    if (!pcPatch)
        return;

    // calcular o tamanho (n,m) da matriz de pontos de PATCH
    // em função do VARIA

    n = 0;

    for (s = 0; s <= 1.01; s += VARIA)
        n += 1;

    m = n;

    // define o espaço de um patch

    if (ptsPatch)
        ptsPatch = liberaMatriz(ptsPatch);

    ptsPatch = AlocaMatriz(n, m);

    // Gera uma matriz de ptsPatch de n x m pontos de cada PATCH
    // para  ( 0 <= s <= 1 , 0 <= s <= 1 )

    s = 0.0f;
    for (i = 0; i < ptsPatch->n; i++)
    {
        t = 0.0f;
        for (j = 0; j < ptsPatch->m; j++)
        {
            // calcula cada ponto: p(s, t) = S G P G^t T

            prod_VetParam_MatBase(s, tmp, vsm); // vsm = S G
            prod_VetParam_MatBase(t, tmp, vtm); // vtm = G^t T

            prod_VetMatriz(vsm, pcPatch->ponto, va); // va = S G P = vsm P

            ptsPatch->ponto[i][j][0] = 0.0f;
            ptsPatch->ponto[i][j][1] = 0.0f;
            ptsPatch->ponto[i][j][2] = 0.0f;

            for (h = 0; h < 4; h++) // p = S G P G^t T = va vtm
            {
                ptsPatch->ponto[i][j][0] += va[h][0] * vtm[h];
                ptsPatch->ponto[i][j][1] += va[h][1] * vtm[h];
                ptsPatch->ponto[i][j][2] += va[h][2] * vtm[h];
            }
            t += VARIA;
        }
        s += VARIA;
    }
}

void copiarPtosControlePatch(int i0, int j0, matriz *pcPat) // copia os pontos de controle de uma patch
{
    int i, j, jj, ii;

    // copiar n x m pontos desde (i0, j0) apartir da matriz pControle
    for (i = 0; i < pcPat->n; i++)
    {
        ii = i0 + i;
        for (j = 0; j < pcPat->m; j++)
        {
            jj = j0 + j;
            pcPat->ponto[i][j][0] = pControle->ponto[ii][jj][0];
            pcPat->ponto[i][j][1] = pControle->ponto[ii][jj][1];
            pcPat->ponto[i][j][2] = pControle->ponto[ii][jj][2];
            pcPat->ponto[i][j][3] = pControle->ponto[ii][jj][3];
        }
    }
}