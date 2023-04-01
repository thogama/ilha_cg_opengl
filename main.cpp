#include <glut.h>

// gcc main.cpp -o main -lGL -lGLU -lglut -- para rodar

float basePontos[8][3] =
    {
        {0.0, 0.0, 0.0}, //a
        {8, 0, 0.0}, //b
        {0.0, 12, 0.0}, //c
        {8, 12, 0.0}, //d
        {0.0, 0.0, 10}, //e
        {8, 0, 10}, //f
        {0.0, 12, 10}, //g
        {8, 12, 10},  //h
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

double rotate_z = 0;

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotate_z += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_z -= 5;
    // else if (key == GLUT_KEY_UP)
    //     rotate_x += 1;
    // else if (key == GLUT_KEY_DOWN)
    //     rotate_x -= 1;
    glutPostRedisplay();
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
    gluLookAt(
        15, 15, 15,
        6, 6, 6,
        0, 0, 1);
    drawAxes(2.0f);

    glRotatef(rotate_z, 0, 0.0, 1);
    // drawAxes(10.0); // desenha os eixos
    base();
    glutSwapBuffers();
}

void idleFunc()
{
    // Atualiza o ângulo de rotação
    rotate_z += 0.1;

    // Redesenha a cena
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutIdleFunc(idleFunc);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}