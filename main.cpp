#include <glut.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
// gcc main.cpp -o main -lGL -lGLU -lglut -- para rodar

float X;
float Y;
float Z;
float ilha;
float lagos;
float terrestres_1;
float terrestres_2;
float plantas_1;
float plantas_2;
float last = 0;

struct Vertex
{
    GLfloat x, y, z;
    GLfloat nx, ny, nz;
};

std::vector<Vertex> vertices;
std::vector<GLuint> indices;

struct Bloco
{
    bool colisao;
    float altura;
};

Bloco **colisao;

struct ValoresArquivo
{
    std::string X;
    std::string Y;
    std::string Z;
    std::string ilha;
    std::string lagos;
    std::string terrestres_1;
    std::string terrestres_2;
    std::string plantas_1;
    std::string plantas_2;
};

void lerArquivo(std::string nome_arquivo, float &saida_X, float &saida_Y, float &saida_Z, float &saida_ilha, float &saida_lagos, float &saida_terrestes_1, float &saida_terrestes_2, float &saida_plantas_1, float &saida_plantas_2)
{
    ValoresArquivo valores;

    std::ifstream arquivo(nome_arquivo);
    std::string linha;
    std::string X, Y, Z, lixo, ilha, lagos, terrestres_1, terrestres_2, plantas_1, plantas_2;

    int cont = 0;
    while (getline(arquivo, linha))
    {
        std::stringstream ss(linha);
        std::cout << "Linha: " << linha << "\n";
        switch (cont)
        {
        case 0:
            ss >> lixo >> valores.X >> valores.Y >> valores.Z;
            std::cout << "Valores de X, Y, Z: " << valores.X << ", " << valores.Y << ", " << valores.Z << "\n";
            break;
        case 1:
            ss >> lixo >> valores.ilha;
            std::cout << "Valor de ilha: " << valores.ilha << "\n";
            break;

        case 2:
            ss >> lixo >> valores.lagos;
            std::cout << "Valor de lagos: " << valores.lagos << "\n";
            break;

        case 3:
            ss >> lixo >> valores.terrestres_1;
            std::cout << "Valor de terrestres_1: " << valores.terrestres_1 << "\n";
            break;

        case 4:
            ss >> lixo >> valores.terrestres_2;
            std::cout << "Valor de terrestres_2: " << valores.terrestres_2 << "\n";
            break;

        case 5:
            ss >> lixo >> valores.plantas_1;
            std::cout << "Valor de plantas_1: " << valores.plantas_1 << "\n";
            break;

        case 6:
            ss >> lixo >> valores.plantas_2;
            std::cout << "Valor de plantas_2: " << valores.plantas_2 << "\n";
            break;
        }
        cont++;
    }
    saida_X = std::stof(valores.X);
    saida_Y = std::stof(valores.Y);
    saida_Z = std::stof(valores.Z);
    saida_ilha = std::stof(valores.ilha);
    saida_lagos = std::stof(valores.lagos);
    saida_terrestes_1 = std::stof(valores.terrestres_1);
    saida_terrestes_2 = std::stof(valores.terrestres_2);
    saida_plantas_1 = std::stof(valores.plantas_1);
    saida_plantas_2 = std::stof(valores.plantas_2);

    arquivo.close();
}

void inicializaColisao(Bloco **&colisao, int X, int Y)
{
    colisao = new Bloco *[(int)X];

    for (int i = 0; i < X; i++)
    {
        colisao[i] = new Bloco[(int)Y];
        for (int j = 0; j < Y; j++)
        {
            colisao[i][j].colisao = false;
            colisao[i][j].altura = 0;
        }
    }
}
void imprimirMatrizColisao(Bloco **colisao, int X, int Y)
{
    for (int j = Y - 1; j >= 0; j--)
    {
        for (int i = 0; i < X; i++)
        {
            if (colisao[i][j].colisao)
                std::cout << "X";
            else
                std::cout << "O";
            std::cout << "[" << colisao[i][j].altura << "] ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n"
              << std::endl;
}

void inserirMatrizColisao(Bloco **colisao, int X, int Y)
{

    colisao[X][Y].altura = sin(X) * cos(Y) + 1.5;

    colisao[X][Y].colisao = true;
}

void desenhaCubo(float x, float y, float z, float lado, GLfloat borda[3], GLfloat cor[3])
{
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 0};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[] = {x + lado / 2, y + lado / 2, z + lado * 2, 1};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);

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

void loadOBJ(const char *filename)
{
    std::ifstream in(filename);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);
    }

    char buffer[1024];
    while (in.getline(buffer, sizeof(buffer)))
    {
        std::stringstream line(buffer);
        std::string cmd;
        line >> cmd;

        if (cmd == "v")
        {
            Vertex v;
            line >> v.x >> v.y >> v.z;
            v.nx = v.ny = v.nz = 0.0f;
            vertices.push_back(v);
        }
        else if (cmd == "vn")
        {
            int idx;
            line >> idx;
            line >> vertices[idx - 1].nx >> vertices[idx - 1].ny >> vertices[idx - 1].nz;
        }
        else if (cmd == "f")
        {
            GLuint idx;
            while (line >> idx)
            {
                indices.push_back(idx - 1);
                char c = line.peek();
                if (c == '/')
                {
                    line.ignore();
                    if (line.peek() != '/')
                    {
                        // read texture coordinate index
                        line >> idx;
                    }
                    line.ignore();
                    if (line.peek() != ' ')
                    {
                        // read vertex normal index
                        line >> idx;
                        vertices[indices.back()].nx = vertices[idx - 1].nx;
                        vertices[indices.back()].ny = vertices[idx - 1].ny;
                        vertices[indices.back()].nz = vertices[idx - 1].nz;
                    }
                }
            }
        }
    }

    in.close();
}

void human(std::vector<GLuint> indices, std::vector<Vertex> vertices, GLfloat entra_x, GLfloat entra_y, GLfloat entra_z)
{
    GLfloat cor[3] = {125.0f / 255, 91.0f / 255, 140.0f / 255};

    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 0};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat position[] = {entra_x, entra_y, entra_z * 2, 1};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, cor);

    glBegin(GL_QUADS);
    for (int i = 0; i < indices.size(); i++)
    {
        glColor3f(cor[0], cor[1], cor[2]);
        Vertex v = vertices[indices[i]];
        glVertex3f(v.x / 15 + entra_x, v.y / 15 + entra_y, v.z / 15 + entra_z);
    }
    glEnd();
}

void terrestre_1(Bloco **colisao)
{

    GLfloat cor[3] = {1, 0, 0};
    GLfloat borda[3] = {1, 1, 1};
    int atualX, atualY;
    int novoX, novoY;
    int i;
    srand(time(NULL));
    do
    {
        atualX = rand() % (int)X;
        atualY = rand() % (int)Y;
    } while (!colisao[atualX][atualY].colisao);

    human(indices, vertices, atualX, atualY + 0.25, colisao[atualX][atualY].altura + 0.25);
    colisao[atualX][atualY].colisao = false;
}

void terrestre_2(Bloco **colisao)
{

    GLfloat cor[3] = {0, 0, 1};
    GLfloat borda[3] = {1, 1, 1};
    int atualX, atualY;
    int novoX, novoY;
    int i;
    do
    {
        atualX = rand() % (int)X;
        atualY = rand() % (int)Y;
    } while (!colisao[atualX][atualY].colisao);

    desenhaCubo(atualX, atualY, colisao[atualX][atualY].altura + 0.5, 0.375, borda, cor);
    colisao[atualX][atualY].colisao = false;
}

void base(float X, float Y, float Z)
{
    GLfloat pos0[3] = {0.0, 0.0, 0.0}; // a {0,0,0}0
    GLfloat pos1[3] = {X, 0, 0.0};     // b {x,0,0}1
    GLfloat pos2[3] = {0.0, Y, 0.0};   // c {0,y,0}2
    GLfloat pos3[3] = {X, Y, 0.0};     // d {x,y,0}3
    GLfloat pos4[3] = {0.0, 0.0, Z};   // e {0,0,z}4
    GLfloat pos5[3] = {X, 0, Z};       // f {x,0,z}5
    GLfloat pos6[3] = {0.0, Y, Z};     // g {0,y,z}6
    GLfloat pos7[3] = {X, Y, Z};       // h {x,y,z}7
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(pos0);
    glVertex3fv(pos1);

    glVertex3fv(pos1);
    glVertex3fv(pos3);

    glVertex3fv(pos3);
    glVertex3fv(pos2);

    glVertex3fv(pos2);
    glVertex3fv(pos0);

    glVertex3fv(pos0);
    glVertex3fv(pos4);

    glVertex3fv(pos1);
    glVertex3fv(pos5);

    glVertex3fv(pos2);
    glVertex3fv(pos6);

    glVertex3fv(pos3);
    glVertex3fv(pos7);

    glVertex3fv(pos4);
    glVertex3fv(pos5);

    glVertex3fv(pos5);
    glVertex3fv(pos7);

    glVertex3fv(pos7);
    glVertex3fv(pos6);

    glVertex3fv(pos6);
    glVertex3fv(pos4);

    // Finaliza a definição das primitivas
    glEnd();
}

float area()
{
    return X * Y;
}

float mover_agua = 0;
void agua()
{
    for (float i = 0; i < X; i += 0.5)
    {
        for (float k = 0; k < Y; k += 0.5)
        {
            GLfloat cor[3] = {31.0f / 255, 12.0f / 255, 243.0f / 255};
            GLfloat borda[3] = {1, 1, 1};
            desenhaCubo(i, k, cos(i * mover_agua) / 10 * sin(k * mover_agua), 0.5, borda, cor);
        }
    }
}

bool haCelulasLivres(bool **areaOcupada, int Y, int X)
{
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
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
    GLfloat folha[3] = {58.0f / 255, 99.0f / 255, 50.0f / 255};

    desenhaCubo(x + 0.125, y + 0.125, z, 0.25, borda, folha);
}

float mover_folhas = 0;
void coqueiro(float x, float y, float z)
{

    GLfloat borda[3] = {1, 1, 1};
    GLfloat folha[3] = {58.0f / 255, 99.0f / 255, 50.0f / 255};
    GLfloat bordatronco[3] = {0, 0, 0};

    GLfloat madeira[3] = {115.0f / 255, 96.0f / 255, 81.0f / 255};

    float aux = 0.25;
    float aleatorio = rand() % (int)z / 2;
    while (aux < aleatorio + 5)
    {
        desenhaCubo(x + 0.125, y + 0.125, aux, 0.25, bordatronco, madeira);
        aux += 0.25;
    }
    desenhaCubo(x + cos(mover_folhas) / 2 / 4, y, aux + 0.25, 0.5, borda, folha);

    desenhaCubo(x + 0.25 + cos(mover_folhas) / 2 / 6, y, aux, 0.5, borda, folha);
    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 8, y, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 0.5 + cos(mover_folhas) / 2 / 10, y, aux - 1, 0.5, borda, folha);
    desenhaCubo(x - 0.25, y, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x + 0.25 + cos(mover_folhas) / 2 / 8, y + 0.25, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 0.25 + cos(mover_folhas) / 2 / 10, y + 0.25, aux - 1, 0.5, borda, folha);

    desenhaCubo(x - 0.25 + cos(mover_folhas) / 2 / 6, y, aux, 0.5, borda, folha);
    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 8, y, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 0.5 + cos(mover_folhas) / 2 / 10, y, aux - 1, 0.5, borda, folha);
    desenhaCubo(x + 0.25, y, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x - 0.25 + cos(mover_folhas) / 2 / 8, y - 0.25, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 0.25 + cos(mover_folhas) / 2 / 10, y - 0.25, aux - 1, 0.5, borda, folha);

    desenhaCubo(x + cos(mover_folhas) / 2 / 6, y - 0.25, aux, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 8, y - 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 10, y - 0.5, aux - 1, 0.5, borda, folha);
    desenhaCubo(x, y + 0.25, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x + 0.25 + cos(mover_folhas) / 2 / 8, y - 0.25, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + 0.25 + cos(mover_folhas) / 2 / 10, y - 0.25, aux - 1, 0.5, borda, folha);

    desenhaCubo(x + cos(mover_folhas) / 2 / 6, y + 0.25, aux, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 8, y + 0.5, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x + cos(mover_folhas) / 2 / 10, y + 0.5, aux - 1, 0.5, borda, folha);
    desenhaCubo(x, y - 0.25, aux - 1.5, 0.5, borda, folha);

    desenhaCubo(x - 0.25 + cos(mover_folhas) / 2 / 8, y + 0.25, aux - 0.5, 0.5, borda, folha);
    desenhaCubo(x - 0.25 + cos(mover_folhas) / 2 / 10, y + 0.25, aux - 1, 0.5, borda, folha);
}

bool stopRand = true;
float idle = 0;
void terra(float porcentagem, int coqueiros, int arbustos)
{
    int numCubos = ceil(porcentagem * area() / 100 / 2);
    int numArbusto = arbustos;
    GLfloat cor[3] = {56.0f / 255, 41.0f / 255, 26.0f / 255};
    GLfloat borda[3] = {0, 0, 0};
    int coqueirosCont = 0;
    int arbustosCont = 0;
    int colisCont = 0;

    if (stopRand)
    {

        srand(idle);
        last = idle;
    }
    else
    {
        srand(last);
    }

    bool **areaOcupada = new bool *[(int)X * 2];
    for (int i = 0; i < X * 2; i++)
    {
        areaOcupada[i] = new bool[(int)Y * 2];
        for (int j = 0; j < Y * 2; j++)
        {
            areaOcupada[i][j] = false;
        }
    }
    for (float i = 0; i < numCubos && haCelulasLivres(areaOcupada, X, Y); i += 0.5)
    {
        int aleatorioX, aleatorioY;
        do
        {
            aleatorioX = rand() % (int)X;
            aleatorioY = rand() % (int)Y;
        } while (areaOcupada[aleatorioX][aleatorioY]);

        areaOcupada[aleatorioX][aleatorioY] = true;

        inserirMatrizColisao(colisao, aleatorioX, aleatorioY);
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
                coqueiro(centroX + 0.5, centroY, alturaAtual + Z / 2);
                break;
            case 1:
                coqueiro(centroX + 0.5, centroY + 0.5, alturaAtual + Z / 2);

                break;
            case 2:
                coqueiro(centroX, centroY + 0.5, alturaAtual + Z / 2);

                break;
            default:
                coqueiro(centroX, centroY, alturaAtual + Z / 2);
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

    for (int i = 0; i < X; i++)
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
    case 'q':
        stopRand = !stopRand;
        break;
    }
}

void display()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Habilitar iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double cameraTargetX = X / 2 + sin(cameraAngleY) * cos(cameraAngleX);
    double cameraTargetY = Y / 2 + sin(cameraAngleX);
    double cameraTargetZ = Z / 2 - cos(cameraAngleY) * cos(cameraAngleX);
    gluLookAt(cameraX, cameraY, cameraZ, cameraTargetX, cameraTargetY, cameraTargetZ, 0, 0, 1);
    drawAxes(5.0f);

    glRotatef(0 + rotate, 0, 0, 1);
    base(X, Y, Z);
    agua();
    terra(ilha, plantas_1, plantas_2);
    for (int i = 0; i < terrestres_1; i++)
    {
        terrestre_1(colisao);
    }
    for (int i = 0; i < terrestres_2; i++)
    {
        terrestre_2(colisao);
    }

    glutSwapBuffers();
}

void idleFunc()
{
    // Atualiza o ângulo de rotação
    mover_agua += 0.01;
    mover_folhas += 0.01;
    idle += 0.01;
    // Redesenha a cena
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    loadOBJ("human.obj");
    lerArquivo("entrada.txt", X, Y, Z, ilha, lagos, terrestres_1, terrestres_2, plantas_1, plantas_2);
    inicializaColisao(colisao, X, Y);
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