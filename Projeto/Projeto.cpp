﻿//===============================================
//Eduardo Figueiredo n-2020213717 
//===============================================

#include "RgbImage.h"
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
GLfloat     xC = 40.0, yC = 40.0, zC = 40.0;


//===========================================================Variaveis e constantes

//============================================================= Observador
GLfloat  rVisao = -20, aVisao = -0.5 * PI, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 2.0, rVisao * sin(aVisao) };
//GLfloat  obsP[] = { -20 , 10.0, 0 };
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
GLint rotrodas = 10;

//============================================================== Texturas
GLUquadricObj* esfera = gluNewQuadric();
GLuint   texture[5];
RgbImage imag;

GLfloat Matriz[4][4];


//=========================================== Objecto
GLint     material = 10;

//---------------------------------------------------- AMBIENTE - fixa
GLint   Dia = 0;     //:::   'D'  
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 0.0 };   // 

//---------------------------------------------------- Luz pontual no TETO (eixo Y)
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLint   luzR = 1;		 	 //:::   'R'  
GLint   luzG = 1;			 //:::   'G'  
GLint   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 0.0, 5.0, 0.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };
GLint ligateto = 1;

//GL_LIGHT1
GLfloat l1Pos[] = { 0, 10, 0, 1 };
GLfloat l1Amb[] = { 0, 0., 0, 0 };
GLfloat l1Dif[] = { 1., 1., 0., 1. };
GLfloat l1Spec[] = { 0., 1., 0., 1. };
GLfloat upDownAngle = 0.;
GLuint n = 30, m = 30;
GLdouble phase = 0., phaseSpeed = 0.5, w = 1.;
bool showGrid = false;

//==================================================================== A variar no programa
bool 		Focos[] = { 1,1 };		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 70.0;		//.. angulo inicial do foco
GLfloat		anguloINC = 3.0;		//.. incremento
GLfloat		anguloMIN = 3.0;		//.. minimo
GLfloat		anguloMAX = 70.0;		//.. maximo

GLfloat Pos1[] = { 0.0f, 5.5f,  5.0f, 1.0f };   // Foco 1 
GLfloat Pos2[] = { 0.0f, 5.5f,  -5.0f, 1.0f };   // Foco 2 

//============================================================== Malha
GLint	  dim = 64;   //numero divisoes da grelha
GLint	  malha = 1;   //Visivel ou inv malha 

//==================================================================== VERTEX ARAY
//------------------------------------------- coordenadas + normais + cores
GLfloat tam = 1;

void initTexturas()
{

	//----------------------------------------- Esfera - skybox envolvente
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("sky.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  asfalto
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("semfreio.bmp");//semfreio.bmp
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//-----------------------------------------  madeira
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("brown-wooden-flooring.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  lateral carro 
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("pintura_azul_chama.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//-----------------------------------------  cima/baixo carro 
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("blue-concrete-textured-wall.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());


}

//…………………………………………………………………………………………………………………………………………… LUZES
void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void defineLuzes()
{
	GLfloat Foco_direccao[] = { 0, -1, 0, 0 };	//��� -Z
	GLfloat Foco1_cor[] = { 1, 0,  0, 1 };	//��� Cor da luz 1
	GLfloat Foco2_cor[] = { 0, 1,  0, 1 };	//��� Cor da luz 2
	GLfloat Foco_Expon = 2.0;		// Foco, SPOT_Exponent

	//�����������������������������������������������Foco Esquerda
	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

	//�����������������������������������������������Foco Direita
	glLightfv(GL_LIGHT2, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, Foco_Expon);

}

void initialize(void)
{
	glClearColor(BLACK);		//������������������������������Apagar
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores
	initTexturas();
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade

	glEnable(GL_NORMALIZE);

	////…………………………………………………………………………………………………………………………… ILUMINACAO / MAteriais
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	initLights();

	defineLuzes();
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

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (ligateto)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void drawChao() {
	glEnable(GL_TEXTURE_2D);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=-4
	glPushMatrix();
	float corAmb[] = { 1,1,1,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corAmb);

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glNormal3f(0, 1, 0);          //normal 

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3i(-xC, -4, xC); //A
	glTexCoord2f(1.0f, 1.0f);
	glVertex3i(xC, -4, xC);  //B
	glTexCoord2f(0.0f, 1.0f);
	glVertex3i(xC, -4, -xC); //C
	glTexCoord2f(0.0f, 0.0f);
	glVertex3i(-xC, -4, -xC); //D
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void drawEsfera()
{
	//------------------------- Esfera
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	//glTranslatef(2, 4, 2);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 60.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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
	glNormal3f(-1, 0, 0);
	glVertex3f(-tam, -tam, tam);//0
	glVertex3f(-tam, tam, tam);//1
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//cima
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(tam, tam, tam);//5
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(-tam, tam, tam);//1
	glEnd();
	//direita
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(tam, tam, tam);//5
	glVertex3f(tam, -tam, tam);//4
	glEnd();
	//baixo
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-tam, -tam, -tam);//3
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(-tam, -tam, tam);//0
	glEnd();
	//tras
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(-tam, tam, -tam);//2
	glVertex3f(tam, tam, -tam);//6
	glVertex3f(tam, -tam, -tam);//7
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//frente
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(tam, -tam, tam);//4
	glVertex3f(tam, tam, tam);//5
	glVertex3f(-tam, tam, tam);//1
	glVertex3f(-tam, -tam, tam);//0
	glEnd();

}

void drawcubotexturas(int tex) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[tex]);

	//esquerda
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-tam, -tam, tam);//0
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-tam, tam, tam);//1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-tam, tam, -tam);//2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//cima
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tam, tam, tam);//5
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tam, tam, -tam);//6
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-tam, tam, -tam);//2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-tam, tam, tam);//1
	glEnd();
	//direita
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tam, -tam, -tam);//7
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tam, tam, -tam);//6
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tam, tam, tam);//5
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(tam, -tam, tam);//4
	glEnd();
	//baixo
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-tam, -tam, -tam);//3
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tam, -tam, -tam);//7
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tam, -tam, tam);//4
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-tam, -tam, tam);//0
	glEnd();
	//tras
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-tam, tam, -tam);//2
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(tam, tam, -tam);//6
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(tam, -tam, -tam);//7
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-tam, -tam, -tam);//3
	glEnd();
	//frente
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(tam, -tam, tam);//4
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(tam, tam, tam);//5
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-tam, tam, tam);//1
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-tam, -tam, tam);//0
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void drawjante() {
	glPushMatrix();

	glPushMatrix();
	glRotatef(rotrodas, 0, 0, 1);
	glScalef(1, 0.1, 0.1);
	drawcubo();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotrodas + 45, 0, 0, 1);
	glScalef(1, 0.1, 0.1);
	drawcubo();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotrodas + 90, 0, 0, 1);
	glScalef(1, 0.1, 0.1);
	drawcubo();
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotrodas + 135, 0, 0, 1);
	glScalef(1, 0.1, 0.1);
	drawcubo();
	glPopMatrix();

	glPopMatrix();
}

void drawcar() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(theta, 0, 1, 0);

	//base da pickup
	glColor3f(0.0745, 0.3176, 0.8471);
	glPushMatrix();
	glScalef(8, 2, 4);
	drawcubotexturas(3);
	glPopMatrix();

	if (light) {
		//luzes
		//frente direita
		glPushMatrix();
		float corluzfrente[] = { 1, 1, 0,1 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, corluzfrente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, corluzfrente);
		glMaterialfv(GL_FRONT, GL_SPECULAR, corluzfrente);
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

		float corluztras[] = { 1, 0, 0,1 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, corluztras);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, corluztras);
		glMaterialfv(GL_FRONT, GL_SPECULAR, corluztras);

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
	glPushMatrix();
	float corHAb[] = { 0.0745, 0.3176, 0.8471,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corHAb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corHAb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corHAb);
	glTranslatef(-0.5, 4, 0);

	glScalef(1.5, 2, 4);

	drawcubotexturas(4);
	glPopMatrix();

	//cabine vidro DIR
	float corVIDROfUM[] = { 0, 0, 0,0.6 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corVIDROfUM);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corVIDROfUM);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corVIDROfUM);
	//glColor4f(0, 0, 0, 0.6);
	glPushMatrix();
	glTranslatef(3, ywindow, 3.98);
	glRotatef(90, 0, 1, 0);
	glScalef(0.01, 1.9999, 2);

	drawcabine();
	glPopMatrix();
	//cabine vidro ESQ
	//glColor4f(0, 0, 0, 0.6);
	glPushMatrix();
	glTranslatef(3, ywindow, -3.98);
	glRotatef(90, 0, 1, 0);
	glScalef(0.01, 1.9999, 2);

	drawcabine();
	glPopMatrix();
	float corcolhab[] = { 0, 0, 0,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corcolhab);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corcolhab);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corcolhab);

	//col vidro dianteiro
	//glColor4f(0, 0, 0, 1);
	glPushMatrix();
	glTranslatef(3, 3.8, 3.799);
	glRotatef(45, 0, 0, 1);
	glScalef(0.2, 2.9, 0.2);

	drawcubo();
	glPopMatrix();

	//col vidro dir
	//glColor4f(0, 0, 0, 1);
	glPushMatrix();
	glTranslatef(3, 3.8, -3.799);
	glRotatef(45, 0, 0, 1);
	glScalef(0.2, 2.9, 0.2);

	drawcubo();
	glPopMatrix();

	//vidro dianteiro
	float corVIDROFRT[] = { 0.6, 0.8, 0.9,0.5 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corVIDROFRT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corVIDROFRT);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corVIDROFRT);
	glColor4f(0.6, 0.8, 0.9, 0.5);
	glPushMatrix();
	glTranslatef(3, 4, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.01, 2.84, 3.99);

	drawcubo();
	glPopMatrix();



	//mala lateral dir 
	float corMala[] = { 0.3, 0.15, 0,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corMala);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corMala);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corMala);
	//glColor3f(0.6, 0.3, 0);
	glPushMatrix();
	glTranslatef(-5, 3, 3.95);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 1, 3);
	drawcubotexturas(2);
	glPopMatrix();

	//mala lateral esq 
	//glColor3f(0.6, 0.3, 0);
	glPushMatrix();
	glTranslatef(-5, 3, -3.95);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 1, 3);
	drawcubotexturas(2);
	glPopMatrix();


	//mala lateral parte tras
	//glColor3f(0.6, 0.3, 0);
	glPushMatrix();
	glTranslatef(-8, 1.95, 0);

	glRotatef(angtap, 0, 0, 1);
	glTranslatef(0.05, 1, 0);
	glScalef(0.1, 1, 4);
	drawcubotexturas(2);
	glPopMatrix();

	//rodas dir frente
	//glColor3f(0.07, 0.07, 0.07);
	glPushMatrix();
	float corWeel[] = { 0.07, 0.07, 0.07,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, corWeel);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corWeel);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corWeel);
	glTranslatef(5.5, -2, 4.7);
	glRotatef(rotrodas, 0, 0, 1);
	drawjante();
	glutSolidTorus(0.7, 1.5, 15, 15);
	glPopMatrix();

	//rodas esq frente
	//glColor3f(0.07, 0.07, 0.07);
	glPushMatrix();
	glTranslatef(5.5, -2, -4.7);
	glRotatef(rotrodas, 0, 0, 1);
	drawjante();
	glutSolidTorus(0.7, 1.5, 15, 15);
	glPopMatrix();

	//rodas esq tras
	//glColor3f(0.07, 0.07, 0.07);
	glPushMatrix();
	glTranslatef(-5.5, -2, -4.7);
	glRotatef(rotrodas, 0, 0, 1);
	drawjante();
	glutSolidTorus(0.7, 1.5, 15, 15);//glutWireTorus(0.5, 1.5, 15, 15);
	glPopMatrix();

	//rodas dir tras
	//glColor3f(0.07, 0.07, 0.07);
	glPushMatrix();
	glTranslatef(-5.5, -2, 4.7);
	glRotatef(rotrodas, 0, 0, 1);
	drawjante();
	glutSolidTorus(0.7, 1.5, 15, 15);
	glPopMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);
	glDisable(GL_BLEND);
	glPopMatrix();


	glDisable(GL_LIGHTING);
	glPushMatrix();
	//�������������������������������Verde
	if (Focos[0]) {
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}
	//�������������������������������Vermelha
	if (Focos[1]) {
		glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(Pos2[0], Pos2[1], Pos2[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
}

void drawmalha() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//----------------------------------------------- Luzes
	defineLuzes();

	//----------------------------------------------- Quadro Material - branco
	float corAmb[] = { 0.7,0.7,0.7,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corAmb);

	//----------------------------------------------- Textura - caracol
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	//----------------------------------------------- Dsenha malha poligonos
	glPushMatrix();
	glTranslatef(0, -4.0, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(50, 50, 50);

	glTranslatef(-1, -1, 0);

	glNormal3f(0, 0, 1);          //normal 

	float			med_dim = (float)dim / 2;
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();
	glPopMatrix();

}

void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}


//====================================================== 
void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_LIGHTING);
	//<><><><><><><><><><><><><> Viewport 1 - MAPA   ???
	glViewport(0, 0, 0.30 * wScreen, 0.30 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos[0], pos[1] + 5, pos[2], pos[0], pos[1], pos[2], 0, 0, 1);

	//����������������������������������������������������������Objectos
	drawcar();
	if (malha) {
		drawmalha();
	}
	else {
		drawChao();
	}
	updateLuz();
	iluminacao();
	drawEixos();
	
	
	//=======================================================


	//================================================================= Viewport 2
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//======================================================
	//  <><><><><><><>         OBSERVADOR NAO EST� FIXO ????
	gluLookAt(obsP[0], obsP[1]+10, obsP[2], 0, 0, 0, 0, 1, 0);

	//======================================================


	//����������������������������������������������������������Objectos
	drawcar();
	if (malha) {
		drawmalha();
	}
	else {
		drawChao();
	}
	updateLuz();
	iluminacao();
	drawEixos();
	

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
	case 'L':	case 'l':
		Dia = !Dia;
		if (Dia) {
			luzGlobalCorAmb[0] = 1.0;
			luzGlobalCorAmb[1] = 1.0;
			luzGlobalCorAmb[2] = 1.0;
		}
		else {
			luzGlobalCorAmb[0] = 0.0;
			luzGlobalCorAmb[1] = 0.0;
			luzGlobalCorAmb[2] = 0.0;
		}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

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
		if (rotrodas < 360) {
			rotrodas += 10;
		}
		else {
			rotrodas = 0;
		}
		printf("coordenadas : %f,%f,%f\n", Matriz[3][0], Matriz[3][1], Matriz[3][2]);
		glutPostRedisplay();
		break;
		//------------------------------ rotacao	
	case 'W': case 'w':
		pos[0] = pos[0] + vel * cos(theta * PI / 180.);
		pos[2] = pos[2] - vel * sin(theta * PI / 180.);
		if (rotrodas > 0) {
			rotrodas -= 10;
		}
		else {
			rotrodas = 350;
		}
		printf("coordenadas : %f,%f,%f\n", Matriz[3][0], Matriz[3][1], Matriz[3][2]);
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
		//--------------------------- Iluminacaoda sala
	case 'P': case 'p':
		ligateto = !ligateto;
		iluminacao();
		glutPostRedisplay();
		break;

	case 'i': case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':case 'R':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':case 'G':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':case 'B':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'C':case 'c':
		malha = !malha;
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		dim = 2 * dim;
		if (dim > 256) dim = 256;
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		dim = 0.5 * dim;
		if (dim < 1) dim = 1;
		glutPostRedisplay();
		break;
	case '1':
		Focos[0] = !Focos[0];
		if (Focos[0] == 0)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;
	case '2':
		Focos[1] = !Focos[1];
		if (Focos[1] == 0)
			glDisable(GL_LIGHT2);
		else
			glEnable(GL_LIGHT2);
		glutPostRedisplay();
		break;
	case '9':
		aberturaFoco = aberturaFoco + anguloINC;
		if (aberturaFoco > anguloMAX)
			aberturaFoco = anguloMAX;
		glutPostRedisplay();
		break;
	case '0':
		aberturaFoco = aberturaFoco - anguloINC;
		if (aberturaFoco < anguloMIN)
			aberturaFoco = anguloMIN;
		glutPostRedisplay();
		break;
		//	//--------------------------- MAterial
		//case 'H': case 'h':
		//	material = (material + 1) % 18;
		//	initMaterials(material);
		//	glutPostRedisplay();
		//	break;

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

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 1);
}

//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("efigueiredo@student.dei.uc.pt  ------  |Observador:'SETAS'|  |carro- �r�, 'w/s' 'a/d'| |vidros 'm/k'| |mala 'n/j'| ");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, Timer, 1);
	glutMainLoop();

	return 0;
}

