#include <GL\glut.h>	// GLUT, include glu.h and gl.h
#include <fstream>		    // File library
#include <iostream>
using namespace std;

GLfloat angleV, fAspect;
GLfloat angle = 0.0f, angle1 = 0.0f;
int selected = 0;
char title[] = "OpenGL-PUC PR: Setas / Isolando as opera��es de rota��o";

// Fun��o callback chamada para fazer o desenho
void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa a tela e o buffer de profundidade
	glPushMatrix();
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glTranslatef(-50.0f, 12.5f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);		// branco
		glutSolidCube(25.0f);				// cubo 1
		glTranslatef(25.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 1.0f);		// magenta
		glutSolidCube(25.0f);				// cubo 2

		// Salva a matriz e faz a transla��o e a rota��o do cubo
		// desta forma esta opera��o fica isolada para o cubo 3
		glPushMatrix();
			glTranslatef(25.0f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);	// amarelo
			glRotatef(45.0f + angle1, 1.0f, 0.0f, 0.0f);
			glutSolidCube(25.0f);			// cubo 3					
		// Restaura a matriz
		glPopMatrix();

		glTranslatef(50.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);		// verde
		glutSolidCube(25.0f);				// cubo 4
		glTranslatef(25.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);		// azul
		glutSolidCube(25.0f);				// cubo 5
	glPopMatrix();

	glutSwapBuffers();
}

// Inicializa par�metros de rendering
void initGL(void)
{
	angleV = 45;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor" 
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
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
void setVisParam(void)
{
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
void reshape(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	setVisParam();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angleV >= 10) angleV -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angleV <= 130) angleV += 5;
		}
	setVisParam();
	glutPostRedisplay();  // redraw
}
// Keyboard ...
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		angle1--;
		break;
	case GLUT_KEY_RIGHT:
		angle1++;
		break;
	case GLUT_KEY_UP:
		angle--;
		break;
	case GLUT_KEY_DOWN:
		angle++;
		break;
	}
	glutPostRedisplay();   // redraw
}

// Programa Principal
int main(int argc, char** argv) {
	cout << "Setas para esquerda e direita - rotaciona o cubo central" << endl; 
	cout << "Setas para cima e para baixo - rotaciona a cena" << endl;
	glutInit(&argc, argv);					// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE);		// Enable double buffered mode
	glutInitWindowSize(640, 480);			// Set the window's initial width & height
	glutInitWindowPosition(50, 50);			// Position the window's initial top-left corner
	glutCreateWindow(title);				// Create window with the given title
	glutDisplayFunc(render);				// Regster callback for render function
	glutSpecialFunc(processSpecialKeys);	// Register callback handler for arrow keys (keyborad)
	glutReshapeFunc(reshape);				// Register callback for window resize event
	glutMouseFunc(mouse);					// Register callback for mouse event
//	glutIdleFunc(render);					// no animation
	initGL();								// Initialization function
	glutMainLoop();							// event loop
	return 0;
}