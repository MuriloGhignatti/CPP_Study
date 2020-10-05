#include <GL/freeglut.h>    // GLUT, include glu.h and gl.h
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"

GLfloat angleV, fAspect;
GLfloat angle = 0.0f, angle1 = 0.0f;
char title[] = "OpenGL-PUC PR: Trabalho";

// Fun��o callback chamada para fazer o desenho
/*
void render(int choice)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle,1.0f, 0.0f, 0.0f);
    switch(choice){
        case 0:
            glColor3f(0.0f, 0.0f, 1.0f);
            glutSolidTeapot(50.0f);
            // Executa os comandos OpenGL
    }
    glPopMatrix();

    glutSwapBuffers();
}
 */

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidTeapot(50.0f);
    // Executa os comandos OpenGL
    glPopMatrix();
    glutSwapBuffers();
}

// Inicializa par�metros de rendering
void initGL(void) {
    angleV = 45;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    GLfloat luzAmbiente[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};       // "cor"
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};// "brilho"
    GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;
    // Especifica que a cor de fundo da janela ser� preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Habilita o modelo de coloriza��o de Gouraud
    glShadeModel(GL_SMOOTH);
    // Define a reflet�ncia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentra��o do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define os par�metros da luz de n�mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    // Habilita a defini��o da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de ilumina��o
    glEnable(GL_LIGHTING);
    // Habilita a luz de n�mero 0
    glEnable(GL_LIGHT0);
}

// Fun��o usada para especificar o volume de visualiza��o
void setVisParam(void) {
    // Especifica sistema de coordenadas de proje��o
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de proje��o
    glLoadIdentity();
    // Especifica a proje��o perspectiva
    gluPerspective(angleV, fAspect, 0.1, 500);
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posi��o do observador e do alvo
    gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void reshape(GLsizei w, GLsizei h) {
    // Para previnir uma divis�o por zero
    if (h == 0) h = 1;
    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
    // Calcula a corre��o de aspecto
    fAspect = (GLfloat) w / (GLfloat) h;
    setVisParam();
}

std::vector<int> matrix(std::string vectors){

    std::string chars = "[],";

    for(char c: chars)
        vectors.erase(std::remove(vectors.begin(), vectors.end(),c),vectors.end());

    std::vector<char> v(vectors.length());
    std::copy(vectors.begin(), vectors.end(),v.begin());
    std::vector<int> convertedToInt;

    for(const auto& c :vectors)
        convertedToInt.push_back(c - 48);

    // for(int i = 0; i < convertedToInt.size(),i++)

    return convertedToInt;
}

void print(std::vector<int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

void selector() {
    char path[100];
    std::string my_list;
    //std::vector<std::vector<int>> parameters;
    std::cout << "Insira o Caminho Para As Especificações dos Solidos: ";
    std::cin.getline(path, sizeof(path));
    std::cout << path;
    std::ifstream arquivo(path);
    std::string line;
    std::string vectors;
    if (arquivo.is_open()) {
        while (getline(arquivo, line)) {
            std::cout << line << std::endl;
            vectors.append(line);
        }
        arquivo.close();
    }

    std::vector<int> parameters = matrix(vectors);

    for(int i; i < 5;i++) std::cout << " ";

    print(parameters);
}

// Programa Principal
int main(int argc, char **argv) {
    selector();
    glutInit(&argc, argv);                // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);    // Enable double buffered mode
    glutInitWindowSize(640, 480);        // Set the window's initial width & height
    glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner
    glutCreateWindow(title);            // Create window with the given title
    glutDisplayFunc(render);            // Regster callback for render function
    glutReshapeFunc(reshape);            // Register callback for window resize event
    glutIdleFunc(render);                // Register callback handler for "doing nothing" event / animation
    initGL();                            // Initialization function
    glutMainLoop();                        // event loop
    return 0;
}