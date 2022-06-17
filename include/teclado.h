void keyboard(int key, int x, int y) //
{
    MatrizIdentidade(); // identidade em matTransf : matriz de transforma
    switch (comando)
    {
    case Escalar:
        if (key == GLUT_KEY_LEFT || key == GLUT_KEY_DOWN)
        {
            matTransf[0][0] = 0.95;
            matTransf[1][1] = 0.95;
            matTransf[2][2] = 0.95;
        }
        else if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP)
        {
            matTransf[0][0] = 1.05;
            matTransf[1][1] = 1.05;
            matTransf[2][2] = 1.05;
        }
        break;

    case Rotação:
        if (glutGetModifiers() == GLUT_ACTIVE_ALT) // se a tecla estiver pressionada rotaciona Z
        {
            if (key == GLUT_KEY_RIGHT)
            {
                matTransf[0][0] = cos(-0.01); // rotaciona em torno do eixo Z
                matTransf[0][1] = sin(-0.01);
                matTransf[1][0] = -sin(-0.01);
                matTransf[1][1] = cos(-0.01);
            }
            else if (key == GLUT_KEY_LEFT)
            {
                matTransf[0][0] = cos(0.01); // rotaciona em torno do eixo Z
                matTransf[0][1] = sin(0.01);
                matTransf[1][0] = -sin(0.01);
                matTransf[1][1] = cos(0.01);
            }
        }
        else
        {
            if (key == GLUT_KEY_DOWN)
            {
                matTransf[1][1] = cos(0.01); // rotaciona em torno do eixo Y
                matTransf[1][2] = sin(0.01);
                matTransf[2][1] = -sin(0.01);
                matTransf[2][2] = cos(0.01);
            }
            if (key == GLUT_KEY_UP)
            {
                matTransf[1][1] = cos(-0.01);
                matTransf[1][2] = sin(-0.01);
                matTransf[2][1] = -sin(-0.01);
                matTransf[2][2] = cos(-0.01);
            }
            if (key == GLUT_KEY_LEFT)
            {
                matTransf[0][0] = cos(-0.01); // rotaciona em torno do eixo X
                matTransf[0][2] = -sin(-0.01);
                matTransf[2][0] = sin(-0.01);
                matTransf[2][2] = cos(-0.01);
            }
            if (key == GLUT_KEY_RIGHT)
            {
                matTransf[0][0] = cos(0.01);
                matTransf[0][2] = -sin(0.01);
                matTransf[2][0] = sin(0.01);
                matTransf[2][2] = cos(0.01);
            }
        }
        break;

    case Translada: // translada

        if (glutGetModifiers() == GLUT_ACTIVE_ALT) // se a tecla estiver pressionada translada Z
        {
            if (key == GLUT_KEY_LEFT || key == GLUT_KEY_DOWN)
            {
                matTransf[0][0] = 0.99;
                matTransf[1][1] = 0.99;
                matTransf[2][2] = 0.99;
            }
            else if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP)
            {
                matTransf[0][0] = 1.01;
                matTransf[1][1] = 1.01;
                matTransf[2][2] = 1.01;
            }
        }
        else
        {
            if (key == GLUT_KEY_LEFT) // translada em torno do eixo X
                matTransf[3][0] = -0.10;
            else if (key == GLUT_KEY_RIGHT)
                matTransf[3][0] = 0.10;
            else if (key == GLUT_KEY_DOWN) // translada em torno do eixo Y
                matTransf[3][1] = -0.10;
            else if (key == GLUT_KEY_UP)
                matTransf[3][1] = 0.10;
        }
    }
    MultMatriz();        // multiplica matriz de transformação com os pontos
    glutPostRedisplay(); // redesenha a tela
}