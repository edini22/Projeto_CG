#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI		 3.14159

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0

//------------------------------------------------------------ Sistema Coordenadas 
GLint		wScreen = 800, hScreen = 600;		//.. janela - pixeis
GLfloat		SIZE = 10.0;	//.. Mundo  SIZE=coordenadas x=y=z

//===========================================================Variaveis e constantes

//============================================================= Observador
GLfloat  rVisao = 20, aVisao = -0.5 * PI, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 2.0, rVisao * sin(aVisao) };
float	 anguloZ = 35;


//============================================================= Animacao
float	  centrox = 0;
float	  rotacao = 0;
GLfloat theta = 0.;
GLfloat vel = 1.;
GLfloat pos[] = { 0., 0., 0. };
GLfloat ywindow = 4;
GLfloat angtap = 0;
GLint light = 1;
//==================================================================== VERTEX ARAY
//------------------------------------------- coordenadas + normais + cores
GLfloat tam = 1;


void initialize(void)
{
	glClearColor(GRAY);		//������������������������������Apagar
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores

	glEnable(GL_CULL_FACE);		//������������������������������Faces visiveis
	glCullFace(GL_BACK);		//������������������������������Mostrar so as da frente

}


void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * SIZE, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * SIZE, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * SIZE);
	glEnd();

}

void drawcabine() {
	//face frente
	glBegin(GL_TRIANGLES);
	glVertex3f(-tam, -tam, tam);//0
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(tam, tam, -tam);//6
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-tam, -tam, tam);//0
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(-tam, tam, -tam);//2
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-tam, -tam, tam);//0
	glVertex3f(-tam, -tam, -tam);//3
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(tam, -tam, -tam);//7
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();

}

void drawcubo() {
	//esquerda
	glBegin(GL_QUADS);
	glVertex3f(-tam, -tam, tam);//0
	glVertex3f(-tam, tam, tam);//1
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//cima
	glBegin(GL_QUADS);
	glVertex3f(tam, tam, tam);//5
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(-tam, tam, tam);//1
	glEnd();
	//direita
	glBegin(GL_QUADS);
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(tam, tam, tam);//5
	glVertex3f(tam, -tam, tam);//4
	glEnd();
	//baixo
	glBegin(GL_QUADS);
	glVertex3f(-tam, -tam, -tam);//3
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(-tam, -tam, tam);//0
	glEnd();
	//tras
	glBegin(GL_QUADS);
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//frente
	glBegin(GL_QUADS);
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(tam, tam, tam);//5
	glVertex3f(-tam, tam, tam);//1
	glVertex3f(-tam, -tam, tam);//0
	glEnd();

}

void drawcar() {
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(theta, 0, 1, 0);
		
		//base da pickup
		glColor3f(1, 1, 1);
		glPushMatrix();
			glScalef(8, 2, 4);
			drawcubo();
		glPopMatrix();

		if(light){
			//luzes
			//frente direita
			glColor3f(1, 1, 0);
			glPushMatrix();
			glTranslatef(8, 0.9, 2.999);
			glScalef(0.5, 1, 1);
			drawcubo();
			glPopMatrix();

			//frente esquerda
			glPushMatrix();
			glTranslatef(8, 0.9, -2.999);
			glScalef(0.5, 1, 1);
			drawcubo();
			glPopMatrix();

			//tras direita
			glColor3f(1, 0, 0);
			glPushMatrix();
			glTranslatef(-7.5555, 0.9, 2.999);
			glScalef(0.5, 1, 1);
			drawcubo();
			glPopMatrix();

			//tras direita
			glColor3f(1, 0, 0);
			glPushMatrix();
			glTranslatef(-7.5555, 0.9, -2.999);
			glScalef(0.5, 1, 1);
			drawcubo();
			glPopMatrix();
		}



		//habitaculo
		glColor3f(0, 1, 0);
		glPushMatrix();
			glTranslatef(-0.5, 4, 0);

			glScalef(1.5,2,4);

			drawcubo();
		glPopMatrix();

		//cabine vidro DIR
		glColor4f(0, 0, 0, 0.5);
		glPushMatrix();
			glTranslatef(3, ywindow, 3.98); 
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 1.9999, 2);

			drawcabine();
		glPopMatrix();
		//cabine vidro ESQ
		glColor4f(0, 0, 0, 0.5);
		glPushMatrix();
			glTranslatef(3, ywindow, -3.98);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 1.9999, 2);

		drawcabine();
		glPopMatrix();

		//col vidro dianteiro
		glColor4f(0, 0, 0, 1);
		glPushMatrix();
			glTranslatef(3, 3.8, 3.799);
			glRotatef(45, 0, 0, 1);
			glScalef(0.2, 2.9, 0.2);

			drawcubo();
		glPopMatrix();

		//col vidro dir
		glColor4f(0, 0, 0, 1);
		glPushMatrix();
			glTranslatef(3, 3.8, -3.799);
			glRotatef(45, 0, 0, 1);
			glScalef(0.2, 2.9, 0.2);

			drawcubo();
		glPopMatrix();
		
		//vidro dianteiro
		glColor4f(0.6, 0.8, 0.9, 0.5);
		glPushMatrix();
		glTranslatef(3, 4,0);
			glRotatef(45, 0, 0, 1);
			glScalef(0.01, 2.84, 4);

			drawcubo();
		glPopMatrix();



		//mala lateral dir 
		glColor3f(0.6, 0.3, 0);
		glPushMatrix();
			glTranslatef(-5, 3, 3.95);
			glRotatef(90, 0, 1, 0);
			glScalef(0.1, 1, 3);

			drawcubo();
		glPopMatrix();

		//mala lateral esq 
		glColor3f(0.6, 0.3, 0);
		glPushMatrix();
		glTranslatef(-5, 3, -3.95);
		glRotatef(90, 0, 1, 0);
		glScalef(0.1, 1, 3);

		drawcubo();
		glPopMatrix();


		//mala lateral parte tras
		glColor3f(0.6, 0.3, 0);
		glPushMatrix();
			glTranslatef(-8,1.95 , 0);

			glRotatef(angtap,0,0,1);//TODO: COLOCAR VARIAVEL PARA ABRIR A MALA!!
			glTranslatef(0.05,1,0);
			glScalef(0.1, 1, 4);
			drawcubo();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
}

//====================================================== 
void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Viewport 2
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//======================================================
	//  <><><><><><><>         OBSERVADOR NAO EST� FIXO ????
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//======================================================


	//����������������������������������������������������������Objectos
	drawEixos();

	drawcar();

	/*drawScene();*/


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {

		/*case 'R': case 'r':
			sempreRodar = !sempreRodar;
			glutPostRedisplay();
			break;*/

			//------------------------------ translacao
	case 'A': case 'a':
		theta += 3.;
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		theta -= 3.;
		glutPostRedisplay();
		break;
	case 'S': case 's':
		pos[0] = pos[0] - vel * cos(theta * PI / 180.);
		pos[2] = pos[2] + vel * sin(theta * PI / 180.);
		glutPostRedisplay();
		break;
		//------------------------------ rotacao	
	case 'W': case 'w':
		pos[0] = pos[0] + vel * cos(theta * PI / 180.);
		pos[2] = pos[2] - vel * sin(theta * PI / 180.);
		glutPostRedisplay();
		break;
	case 'M':case 'm':
		if (ywindow > 0) {
			ywindow -= 0.5;
			glutPostRedisplay();
		}
		break;
	case 'K':case 'k':
		if (ywindow < 4) {
			ywindow += 0.5;
			glutPostRedisplay();
		}
		break;
	case 'J':case 'j':
		if (angtap > 0) {
			angtap -= 10;
			glutPostRedisplay();
		}
		break;
	case 'N':case 'n':
		if (angtap < 170) {
			angtap += 10;
			glutPostRedisplay();
		}
		break;
	case 'L':case 'l':
		if (light) {
			light = 0;
		}
		else {
			light = 1;
		}
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

}



void teclasNotAscii(int key, int x, int y) {

	//=========================================================
	//  <><><><><><>  Movimento do observador  ???
	//=========================================================
	if (key == GLUT_KEY_UP) {
		obsP[1] += 0.1;
	}	// Movimento para cima
	if (key == GLUT_KEY_DOWN) {
		obsP[1] -= 0.1;
	}  // Movimento para baixo
	if (key == GLUT_KEY_LEFT) {
		aVisao += 0.1;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	}  // Movimento para a esquerda
	if (key == GLUT_KEY_RIGHT) {
		aVisao -= 0.1;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	} // Movimento para a direira

	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("efigueiredo@student.dei.uc.pt  ------  |Observador:'SETAS'|  |carro- �r�, 'w/s' 'a/d'  ");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}

