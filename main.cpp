#include <glut.h>
#include <cmath>
#include <time.h>
#include <iostream>
// gcc main.cpp -o main -lGL -lGLU -lglut -- para rodar

void desenhaCubo(float x, float y, float z, float lado, GLfloat borda[3], GLfloat cor[3])
{
    glColor3f(borda[0], borda[1], borda[2]);
    glBegin(GL_LINE_STRIP);

    glVertex3f(x, y, z);
    glVertex3f(x + lado, y, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x, y + lado, z);

    glVertex3f(x, y, z + lado);
    glVertex3f(x, y + lado, z + lado);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x + lado, y, z + lado);

    glVertex3f(x, y, z);
    glVertex3f(x, y, z + lado);
    glVertex3f(x + lado, y, z + lado);
    glVertex3f(x + lado, y, z);

    glVertex3f(x, y + lado, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x, y + lado, z + lado);

    glVertex3f(x, y, z);
    glVertex3f(x, y + lado, z);
    glVertex3f(x, y + lado, z + lado);
    glVertex3f(x, y, z + lado);

    glVertex3f(x + lado, y, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x + lado, y, z + lado);
    glEnd();
    glColor3f(cor[0], cor[1], cor[2]);
    glBegin(GL_QUADS);

    glVertex3f(x, y, z);
    glVertex3f(x + lado, y, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x, y + lado, z);

    glVertex3f(x, y, z + lado);
    glVertex3f(x, y + lado, z + lado);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x + lado, y, z + lado);

    glVertex3f(x, y, z);
    glVertex3f(x, y, z + lado);
    glVertex3f(x + lado, y, z + lado);
    glVertex3f(x + lado, y, z);

    glVertex3f(x, y + lado, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x, y + lado, z + lado);

    glVertex3f(x, y, z);
    glVertex3f(x, y + lado, z);
    glVertex3f(x, y + lado, z + lado);
    glVertex3f(x, y, z + lado);

    glVertex3f(x + lado, y, z);
    glVertex3f(x + lado, y + lado, z);
    glVertex3f(x + lado, y + lado, z + lado);
    glVertex3f(x + lado, y, z + lado);
    glEnd();
};

float basePontos[8][3] =
    {
        {0.0, 0.0, 0.0}, // a {0,0,0}
        {8, 0, 0.0},     // b {x,0,0}
        {0.0, 12, 0.0},  // c {0,y,0}
        {8, 12, 0.0},    // d {x,y,0}
        {0.0, 0.0, 10},  // e {x,0,z}
        {8, 0, 10},      // f {0,y,z}
        {0.0, 12, 10},   // g {x,0,z}
        {8, 12, 10},     // h {x,y,z}
};

void base()
{
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(basePontos[0]);
    glVertex3fv(basePontos[1]);

    glVertex3fv(basePontos[1]);
    glVertex3fv(basePontos[3]);

    glVertex3fv(basePontos[3]);
    glVertex3fv(basePontos[2]);

    glVertex3fv(basePontos[2]);
    glVertex3fv(basePontos[0]);

    glVertex3fv(basePontos[0]);
    glVertex3fv(basePontos[4]);

    glVertex3fv(basePontos[1]);
    glVertex3fv(basePontos[5]);

    glVertex3fv(basePontos[2]);
    glVertex3fv(basePontos[6]);

    glVertex3fv(basePontos[3]);
    glVertex3fv(basePontos[7]);

    glVertex3fv(basePontos[4]);
    glVertex3fv(basePontos[5]);

    glVertex3fv(basePontos[5]);
    glVertex3fv(basePontos[7]);

    glVertex3fv(basePontos[7]);
    glVertex3fv(basePontos[6]);

    glVertex3fv(basePontos[6]);
    glVertex3fv(basePontos[4]);

    // Finaliza a definição das primitivas
    glEnd();
}

float comprimento = sqrt(pow(basePontos
                                     [1][0] -
                                 basePontos
                                     [0][0],
                             2) +
                         pow(basePontos
                                     [1][1] -
                                 basePontos
                                     [0][1],
                             2) +
                         pow(basePontos
                                     [1][2] -
                                 basePontos
                                     [0][2],
                             2));
float largura = sqrt(pow(basePontos
                                 [2][0] -
                             basePontos
                                 [0][0],
                         2) +
                     pow(basePontos
                                 [2][1] -
                             basePontos
                                 [0][1],
                         2) +
                     pow(basePontos
                                 [2][2] -
                             basePontos
                                 [0][2],
                         2));
float altura = sqrt(pow(basePontos
                                [4][0] -
                            basePontos
                                [0][0],
                        2) +
                    pow(basePontos
                                [4][1] -
                            basePontos
                                [0][1],
                        2) +
                    pow(basePontos
                                [4][2] -
                            basePontos
                                [0][2],
                        2));

float area()
{
    return comprimento * largura;
}

float mover_agua = 0;
void agua()
{
    for (float i = 0; i < comprimento; i += 0.5)
    {
        for (float k = 0; k < largura; k += 0.5)
        {
            GLfloat cor[3] = {31.0f / 255, 12.0f / 255, 243.0f / 255};
            GLfloat borda[3] = {1, 1, 1};
            desenhaCubo(i, k, cos(i * mover_agua) / 10 * sin(k * mover_agua), 0.5, borda, cor);
        }
    }
}

bool haCelulasLivres(bool **areaOcupada, int largura, int comprimento)
{
    for (int i = 0; i < largura; i++)
    {
        for (int j = 0; j < comprimento; j++)
        {
            if (!areaOcupada[i][j])
            {
                return true;
            }
        }
    }
    return false;
}

void arbusto(float x, float y, float z)
{
    GLfloat borda[3] = {1, 1, 1};
    GLfloat folha[3] = {0, 128, 0};

    desenhaCubo(x, y, z, 0.25, borda, folha);
}

float mover_folhas = 0;
void coqueiro(float x, float y, float z)
{

    GLfloat borda[3] = {1, 1, 1};
    GLfloat folha[3] = {0, 128, 0};
    GLfloat madeira[3] = {141.0f / 255, 90.0f / 255, 0.0f};

    float aux = 0.5;
    while (aux < z)
    {
        desenhaCubo(x, y, aux, 0.5, borda, madeira);
        aux += 0.5;
    }
    desenhaCubo(x + cos(mover_folhas) / 2 / 4, y, aux + 0.5, 0.5, borda, folha);

    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 6, y, aux, 0.5, borda, folha);
    desenhaCubo(x + 1 + cos(mover_folhas) / 2 / 8, y, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 1 + cos(mover_folhas) / 2 / 10, y, aux - 1, 0.5, borda, folha);
    desenhaCubo(x - 0.5, y, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 8, y + 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 10, y + 0.5, aux - 1, 0.5, borda, folha);

    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 6, y, aux, 0.5, borda, folha);
    desenhaCubo(x - 1 + cos(mover_folhas) / 2 / 8, y, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 1 + cos(mover_folhas) / 2 / 10, y, aux - 1, 0.5, borda, folha);
    desenhaCubo(x + 0.5, y, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 8, y - 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 10, y - 0.5, aux - 1, 0.5, borda, folha);

    desenhaCubo(x + cos(mover_folhas) / 2 / 6, y - 0.5, aux, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 8, y - 1, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 10, y - 1, aux - 1, 0.5, borda, folha);
    desenhaCubo(x, y + 0.5, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 8, y - 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 10, y - 0.5, aux - 1, 0.5, borda, folha);

    desenhaCubo(x + cos(mover_folhas) / 2 / 6, y + 0.5, aux, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 8, y + 1, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 10, y + 1, aux - 1, 0.5, borda, folha);
    desenhaCubo(x, y - 0.5, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 8, y + 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 10, y + 0.5, aux - 1, 0.5, borda, folha);
}

void terra(float porcentagem, int coqueiros, int arbustos)
{
    int numCubos = ceil(porcentagem * area() / 100 / 2);
    int numArbusto = arbustos;
    GLfloat cor[3] = {141.0f / 255, 90.0f / 255, 0.0f};
    GLfloat borda[3] = {0, 0, 0};
    int coqueirosCont = 0;
    int arbustosCont = 0;

    srand((comprimento * largura * altura));

    bool **areaOcupada = new bool *[(int)comprimento * 2];
    for (int i = 0; i < comprimento * 2; i++)
    {
        areaOcupada[i] = new bool[(int)largura * 2];
        for (int j = 0; j < largura * 2; j++)
        {
            areaOcupada[i][j] = false;
        }
    }

    for (float i = 0; i < numCubos && haCelulasLivres(areaOcupada, comprimento, largura); i += 0.5)
    {
        int aleatorioX, aleatorioY;
        do
        {
            aleatorioX = rand() % (int)comprimento;
            aleatorioY = rand() % (int)largura;
        } while (areaOcupada[aleatorioX][aleatorioY]);

        areaOcupada[aleatorioX][aleatorioY] = true;
        float centroX = aleatorioX;
        float centroY = aleatorioY;

        float alturaAtual = sin(centroX) * cos(centroY) + 1.5;

        desenhaCubo(centroX, centroY, alturaAtual, 0.5, borda, cor);
        for (float aux = 0.5; aux < alturaAtual; aux += 0.5)
        {
            desenhaCubo(centroX, centroY, aux, 0.5, borda, cor);
            desenhaCubo(centroX + 0.5, centroY + 0.5, aux, 0.5, borda, cor);
            desenhaCubo(centroX, centroY + 0.5, aux, 0.5, borda, cor);
            desenhaCubo(centroX + 0.5, centroY, aux, 0.5, borda, cor);
        }
        desenhaCubo(centroX + 0.5, centroY + 0.5, alturaAtual, 0.5, borda, cor);
        desenhaCubo(centroX, centroY + 0.5, alturaAtual, 0.5, borda, cor);
        desenhaCubo(centroX + 0.5, centroY, alturaAtual, 0.5, borda, cor);

        int aux = rand() % 3;
        if (coqueirosCont < coqueiros)
        {
            switch (aux)
            {
            case 0:
                coqueiro(centroX + 0.5, centroY, alturaAtual + altura / 2);
                break;
            case 1:
                coqueiro(centroX + 0.5, centroY + 0.5, alturaAtual + altura / 2);

                break;
            case 2:
                coqueiro(centroX, centroY + 0.5, alturaAtual + altura / 2);

                break;
            default:
                coqueiro(centroX, centroY, alturaAtual + altura / 2);
                break;
            }
            coqueirosCont++;
        }
        if (arbustosCont < arbustos)
        {
            switch (aux)
            {
            case 0:
                arbusto(centroX, centroY + 0.5, alturaAtual + 0.5);
                break;
            case 1:
                arbusto(centroX, centroY, alturaAtual + 0.5);
                break;
            case 2:
                arbusto(centroX + 0.5, centroY, alturaAtual + 0.5);
                break;
            default:
                arbusto(centroX + 0.5, centroY + 0.5, alturaAtual + 0.5);
                break;
            }
            arbustosCont++;
        }
    }

    for (int i = 0; i < comprimento; i++)
    {
        delete[] areaOcupada[i];
    }
    delete[] areaOcupada;
}

void drawAxes(float size)
{
    // Eixo X (vermelho)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glEnd();

    // Eixo Y (azul)
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size, 0.0f);
    glEnd();

    // Eixo Z (verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, size);
    glEnd();
}

float cameraX = 15;
float cameraY = 15;
float cameraZ = 15;
float cameraAngleY = 0;
float cameraAngleX = 0;
float rotate = 0;
float rotateKey = 0;
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        cameraX += 1 * sin(cameraAngleY);
        cameraY += 1 * sin(cameraAngleX);
        cameraZ -= 1 * cos(cameraAngleY);
        break;
    case 's':
        cameraX -= 1 * sin(cameraAngleY);
        cameraY -= 1 * sin(cameraAngleX);
        cameraZ += 1 * cos(cameraAngleY);
        break;
    case 'a':
        // virar a câmera para a esquerda
        rotate -= 1;
        break;
    case 'd':
        // virar a câmera para a direita
        rotate += 1;
        break;
    }
}

void display()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double cameraTargetX = comprimento / 2 + sin(cameraAngleY) * cos(cameraAngleX);
    double cameraTargetY = largura / 2 + sin(cameraAngleX);
    double cameraTargetZ = altura / 2 - cos(cameraAngleY) * cos(cameraAngleX);
    gluLookAt(cameraX, cameraY, cameraZ, cameraTargetX, cameraTargetY + rotate, cameraTargetZ, 0, 0, 1);
    drawAxes(5.0f);

    glRotatef(6 * rotateKey, 0, 0, 1);
    base();
    agua();
    terra(50, 3, 100);
    glutSwapBuffers();
}

void idleFunc()
{
    // Atualiza o ângulo de rotação
    mover_agua += 0.01;
    mover_folhas += 0.01;
    // Redesenha a cena
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}