
void processMenuEvents(int option) // processa eventos do menu
{
    MatrizIdentidade();   // reseta a matriz de transformação
    if (option == Solido) // se a opção for solido
        preenchido = 1;
    else
        preenchido = 0;

    switch (option) // processa a opção
    {
    case PontosControle: // se a opção for pontos de controle carrega o arquivo
        CarregaPontos("points.txt");
        break;

    case PontosControleAleatorio:
        GeraPontosAleatorios();
        break;

    case Pontos:
        tipoVisualisacao = GL_POINTS;
        break;

    case Linha:
        tipoVisualisacao = GL_LINE_STRIP;
        break;

    case Solido:
        tipoVisualisacao = GL_QUADS;
        break;

    case sair:
        exit(0);
        break;

    case BEZIER:
    case BSPLINE:
    case CATMULLROM:
        MontaMatrizBase(option);
        break;

    default:
        comando = option; // se não for nenhum dos casos acima, é uma operação
    }
    glutPostRedisplay(); // redesenha a tela
}

void processColorMenuEvents(int option) //
{
    switch (option)
    {
    case 1: // azul
        vcolor[0][0] = 0.0;
        vcolor[0][1] = 0.0;
        vcolor[0][2] = 1.0;
        if (preenchido == 1)
            processMenuEvents(-2);
        break;
    case 2: // verde
        vcolor[0][0] = 0.0;
        vcolor[0][1] = 1.0;
        vcolor[0][2] = 0.0;
        if (preenchido == 1)
            processMenuEvents(-2);
        break;
    case 3: // vermelho
        vcolor[0][0] = 1.0;
        vcolor[0][1] = 0.0;
        vcolor[0][2] = 0.0;

        if (preenchido == 1)
            processMenuEvents(-2);
        break;
    case 4: // amarelo
        vcolor[0][0] = 1.0;
        vcolor[0][1] = 1.0;
        vcolor[0][2] = 0.0;
        if (preenchido == 1)
            processMenuEvents(-2);
        break;
    case 5: // azul claro
        vcolor[0][0] = 0.5;
        vcolor[0][1] = 0.5;
        vcolor[0][2] = 1.5;
        if (preenchido == 1)
            processMenuEvents(-2);
        break;
    }
}

void createGLUTMenus()
{
    int menu, submenu, SUBmenuTransladar, SUBmenuGirar, SUBmenuSuperficie, SUBmenuPintar, SUBmenuCores;

    SUBmenuSuperficie = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Bezier", BEZIER);
    glutAddMenuEntry("B-Spline", BSPLINE);
    glutAddMenuEntry("Catmull-Rom", CATMULLROM);

    SUBmenuPintar = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Pontos", Pontos);
    glutAddMenuEntry("Malha", Linha);
    glutAddMenuEntry("Preenchido", Solido);

    SUBmenuCores = glutCreateMenu(processColorMenuEvents); // menu de core -----------------------
    glutAddMenuEntry("Azul", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Vermelho", 3);
    glutAddMenuEntry("Amarelo", 4);
    glutAddMenuEntry("Azul claro", 5);

    menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Carregar pontos de controle", PontosControle);
    glutAddMenuEntry("Gerar pontos aleatorios", PontosControleAleatorio);
    glutAddSubMenu("Superficies", SUBmenuSuperficie);
    glutAddSubMenu("Visualizacao de objeto", SUBmenuPintar);
    glutAddSubMenu("Cores", SUBmenuCores);
    glutAddMenuEntry("Escala", Escalar);
    glutAddMenuEntry("Rotacao", Rotação);
    glutAddMenuEntry("Translacao", Translada);
    glutAddMenuEntry("Sair", sair);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
