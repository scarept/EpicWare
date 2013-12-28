#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>     
#include <GL\glut.h>
#include <iostream>
#include "Grafo.h"
#include "LoadImages.h"

using namespace std;

#define BUFSIZE 512
//funções
void myReshape(int w, int h);
void escreveTexto();

//convers�es
#define radToDeg(x)   (180*(x)/M_PI)
#define dtr(x)   (M_PI*(x)/180)

#define graus(X) (double)((X)*180/M_PI)
#define rad(X)   (double)((X)*M_PI/180)

// luzes e materiais

const GLfloat mat_ambient[][4] = { { 0.33, 0.22, 0.03, 1.0 },	// brass
{ 0.0, 0.0, 0.0 },			// red plastic
{ 0.0215, 0.1745, 0.0215 },	// emerald
{ 0.02, 0.02, 0.02 },		// slate
{ 0.0, 0.0, 0.1745 },		// azul
{ 0.02, 0.02, 0.02 },		// preto
{ 0.1745, 0.1745, 0.1745 } };// cinza

const GLfloat mat_diffuse[][4] = { { 0.78, 0.57, 0.11, 1.0 },		// brass
{ 0.5, 0.0, 0.0 },				// red plastic
{ 0.07568, 0.61424, 0.07568 },	// emerald
{ 0.78, 0.78, 0.78 },			// slate
{ 0.0, 0.0, 0.61424 },			// azul
{ 0.08, 0.08, 0.08 },			// preto
{ 0.61424, 0.61424, 0.61424 } };	// cinza

const GLfloat mat_specular[][4] = { { 0.99, 0.91, 0.81, 1.0 },			// brass
{ 0.7, 0.6, 0.6 },					// red plastic
{ 0.633, 0.727811, 0.633 },		// emerald
{ 0.14, 0.14, 0.14 },				// slate
{ 0.0, 0.0, 0.727811 },			// azul
{ 0.03, 0.03, 0.03 },				// preto
{ 0.727811, 0.727811, 0.727811 } };	// cinza

const GLfloat mat_shininess[] = { 27.8,	// brass
32.0,	// red plastic
76.8,	// emerald
18.78,	// slate
30.0,	// azul
75.0,	// preto
60.0 };	// cinza

enum tipo_material { brass, red_plastic, emerald, slate, azul, preto, cinza }; //materiais para cobrir os objectos

#ifdef __cplusplus
inline tipo_material operator++(tipo_material &rs, int) {
	return rs = (tipo_material)(rs + 1);
}
#endif

typedef	GLdouble Vertice[3];
typedef	GLdouble Vector[4];



typedef struct Camera{
	GLfloat fov;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice center;

}Camera;

typedef struct Estado{
	Camera		camera;
	int			xMouse, yMouse;
	GLboolean	light;
	GLboolean	apresentaNormais;
	GLint		lightViewer;
	GLint		eixoTranslaccao;
	GLdouble	eixo[3];
	GLint		estadoJogo; // 0 - login; 1- Jogo 3D; 2- menu
}Estado;

typedef struct Login{
	GLuint loginBoxImg;
	GLuint imagemFundo;
	string username;
	string password;
	bool usernameSelected;
	bool passwordSelected;

}Login;

typedef struct Modelo {
#ifdef __cplusplus
	tipo_material cor_cubo;
#else
	enum tipo_material cor_cubo;
#endif

	GLfloat g_pos_luz1[4];
	GLfloat g_pos_luz2[4];

	GLfloat escala;
	GLUquadric *quad;
}Modelo;

Estado estado;
Modelo modelo;
Login login;

void initEstado(){
	estado.camera.dir_lat = M_PI / 4;
	estado.camera.dir_long = -M_PI / 4;
	estado.camera.fov = 60;
	estado.camera.dist = 100;
	estado.eixo[0] = 0;
	estado.eixo[1] = 0;
	estado.eixo[2] = 0;
	estado.camera.center[0] = 0;
	estado.camera.center[1] = 0;
	estado.camera.center[2] = 0;
	estado.light = GL_FALSE;
	estado.apresentaNormais = GL_FALSE;
	estado.lightViewer = 1;
}

void initModelo(){
	modelo.escala = 0.2;

	modelo.cor_cubo = brass;
	modelo.g_pos_luz1[0] = -5.0;
	modelo.g_pos_luz1[1] = 5.0;
	modelo.g_pos_luz1[2] = 5.0;
	modelo.g_pos_luz1[3] = 0.0;
	modelo.g_pos_luz2[0] = 5.0;
	modelo.g_pos_luz2[1] = -15.0;
	modelo.g_pos_luz2[2] = 5.0;
	modelo.g_pos_luz2[3] = 0.0;
}

void desenhaBtnLogin(GLenum mode){
	/* funções botões */
	/*zona de username */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(1);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(39, 39);
	glVertex2f(68, 39);
	glVertex2f(68, 47);
	glVertex2f(39, 47);
	glEnd();
	glPopMatrix();

	/*zona de password */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(2);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(39, 50);
	glVertex2f(68, 50);
	glVertex2f(68, 57);
	glVertex2f(39, 57);
	glEnd();
	glPopMatrix();

	/* botao login */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(3);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(33, 63);
	glVertex2f(67, 63);
	glVertex2f(67, 71);
	glVertex2f(33, 71);
	glEnd();
	glPopMatrix();

	/* modo offline */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(4);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(33, 72);
	glVertex2f(67, 72);
	glVertex2f(67, 78);
	glVertex2f(33, 78);
	glEnd();
	glPopMatrix();

	/* fim criacção de butões */

}

void desenhaLogin(GLenum mode){

	desenhaBtnLogin(mode);

	/* carregar fundo */
	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(10);
		glEnable(GL_TEXTURE_2D); //obrigatorio para ler imagens no soil
		//GLuint ax = carrega_texturas("menu.png");
	
		glBindTexture(GL_TEXTURE_2D, login.imagemFundo);
		/* render texturas */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 0.5); //transparencias 
		glBegin(GL_POLYGON);
		//glColor3f(0, 1, 1);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(0, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(100, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(100, 100);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(0, 100);
		glEnd();
	glPopMatrix();


	/* caixa de login */
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, login.loginBoxImg);
		/* render imagens */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBegin(GL_POLYGON);
		//glColor3f(0, 1, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(30, 10);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(70, 10);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(70, 90);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(30, 90);
		glEnd();
	glPopMatrix();


	glDisable(GL_TEXTURE_2D); // desetivar para não interferir com o grafo 3D
	//escreveTexto();
	escreveTexto();

}

void escreveTexto(){
	/* escrever texto */
	glRasterPos2f(39, 45);
	int tamanho = login.username.length();
	for(int i = 0; i < tamanho;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, login.username[i]);
	}

	glRasterPos2f(39, 55);
	int tamanhoPass = login.password.length();
	char * asterisco = "*";
	for (int i = 0; i < tamanhoPass; i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *asterisco);
	}
}

void loginInit(){
	login.imagemFundo = carrega_texturas("background.png");
	login.loginBoxImg = carrega_texturas("login.png");
	/*
	glPushMatrix();
	menu.imagemFundo = carrega_texturas("menu.png");
	//GLint in = carrega_texturas("menu.png");
	glPopMatrix();
	*/
}

void gameInit()
{
	glPushMatrix();
	GLuint ax = carrega_texturas("menu.png");
	glPopMatrix();

	GLfloat LuzAmbiente[] = { 0.5, 0.5, 0.5, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	glEnable(GL_NORMALIZE);

	glDepthFunc(GL_LESS);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	initModelo();
	initEstado();
	modelo.quad = gluNewQuadric();
	gluQuadricDrawStyle(modelo.quad, GLU_FILL);
	gluQuadricNormals(modelo.quad, GLU_OUTSIDE);

	leGrafo();
}

void imprime_ajuda(void)
{
	printf("\n\nDesenho de um labirinto a partir de um grafo\n");
	printf("h,H - Ajuda \n");
	printf("i,I - Reset dos Valores \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("k,K - Alerna luz de camera com luz global \n");
	printf("s,S - PolygonMode Fill \n");
	printf("w,W - PolygonMode Wireframe \n");
	printf("p,P - PolygonMode Point \n");
	printf("c,C - Liga/Desliga Cull Face \n");
	printf("n,N - Liga/Desliga apresenta��o das normais \n");
	printf("******* grafos ******* \n");
	printf("F1  - Grava grafo do ficheiro \n");
	printf("F2  - L� grafo para ficheiro \n");
	printf("F6  - Cria novo grafo\n");
	printf("******* Camera ******* \n");
	printf("Bot�o esquerdo - Arrastar os eixos (centro da camera)\n");
	printf("Bot�o direito  - Rodar camera\n");
	printf("Bot�o direito com CTRL - Zoom-in/out\n");
	printf("PAGE_UP, PAGE_DOWN - Altera dist�ncia da camara \n");
	printf("ESC - Sair\n");
}


void material(enum tipo_material mat)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[mat]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess[mat]);
}

const GLfloat red_light[] = { 1.0, 0.0, 0.0, 1.0 };
const GLfloat green_light[] = { 0.0, 1.0, 0.0, 1.0 };
const GLfloat blue_light[] = { 0.0, 0.0, 1.0, 1.0 };
const GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };


void putLights(GLfloat* diffuse)
{
	const GLfloat white_amb[] = { 0.2, 0.2, 0.2, 1.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT0, GL_POSITION, modelo.g_pos_luz1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT1, GL_AMBIENT, white_amb);
	glLightfv(GL_LIGHT1, GL_POSITION, modelo.g_pos_luz2);

	/* desenhar luz */
	//material(red_plastic);
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz1[0], modelo.g_pos_luz1[1], modelo.g_pos_luz1[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();
	//glPushMatrix();
	//	glTranslatef(modelo.g_pos_luz2[0], modelo.g_pos_luz2[1], modelo.g_pos_luz2[2]);
	//	glDisable(GL_LIGHTING);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glutSolidCube(0.1);
	//	glEnable(GL_LIGHTING);
	//glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void desenhaSolo(){
#define STEP 10
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	for (int i = -300; i<300; i += STEP)
	for (int j = -300; j<300; j += STEP){
		glVertex2f(i, j);
		glVertex2f(i + STEP, j);
		glVertex2f(i + STEP, j + STEP);
		glVertex2f(i, j + STEP);
	}
	glEnd();

}

void CrossProduct(GLdouble v1[], GLdouble v2[], GLdouble cross[])
{
	cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
	cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
	cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

GLdouble VectorNormalize(GLdouble v[])
{
	int		i;
	GLdouble	length;

	if (fabs(v[1] - 0.000215956) < 0.0001)
		i = 1;

	length = 0;
	for (i = 0; i< 3; i++)
		length += v[i] * v[i];
	length = sqrt(length);
	if (length == 0)
		return 0;

	for (i = 0; i< 3; i++)
		v[i] /= length;

	return length;
}

void desenhaNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat){

	switch (mat){
	case red_plastic:
		glColor3f(1, 0, 0);
		break;
	case azul:
		glColor3f(0, 0, 1);
		break;
	case emerald:
		glColor3f(0, 1, 0);
		break;
	default:
		glColor3f(1, 1, 0);
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.4, 0.4, 0.4);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3dv(normal);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);

}

void desenhaParede(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf){
	/*
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	v1[0] = xf - xi;
	v1[1] = yf - yi;
	v1[2] = 0;
	v2[0] = 0;
	v2[1] = 0;
	v2[2] = 1;
	CrossProduct(v1, v2, cross);
	//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
	length = VectorNormalize(cross);
	//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

	material(emerald);
	glBegin(GL_QUADS);
	glNormal3dv(cross);
	glVertex3f(xi, yi, zi);
	glVertex3f(xf, yf, zf + 0);
	glVertex3f(xf, yf, zf + 1);
	glVertex3f(xi, yi, zi + 1);
	glEnd();

	if (estado.apresentaNormais) {
	desenhaNormal(xi, yi, zi, cross, emerald);
	desenhaNormal(xf, yf, zf, cross, emerald);
	desenhaNormal(xf, yf, zf + 1, cross, emerald);
	desenhaNormal(xi, yi, zi + 1, cross, emerald);
	}
	*/
}


void desenhaChao(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf, int orient){
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	v1[0] = xf - xi;
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = yf - yi;

	switch (orient) {
	case NORTE_SUL:
		v1[2] = 0;
		v2[2] = zf - zi;
		CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

		material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zi);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zf);
		glEnd();
		if (estado.apresentaNormais) {
			desenhaNormal(xi, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yf, zf, cross, red_plastic);
			desenhaNormal(xi, yi, zf, cross, red_plastic);
		}
		break;
	case ESTE_OESTE:
		v1[2] = zf - zi;
		v2[2] = 0;
		CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);
		material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zf);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zi);
		glEnd();
		if (estado.apresentaNormais) {
			desenhaNormal(xi, yi, zi, cross, red_plastic);
			desenhaNormal(xf, yi, zf, cross, red_plastic);
			desenhaNormal(xf, yf, zf, cross, red_plastic);
			desenhaNormal(xi, yi, zi, cross, red_plastic);
		}
		break;
	default:
		cross[0] = 0;
		cross[1] = 0;
		cross[2] = 1;
		material(azul);
		/*
		glBegin(GL_LINE_LOOP);//start drawing a line loop
		glVertex3f(-1.0f, 0.0f, 0.0f);//left of window
		glVertex3f(0.0f, -1.0f, 0.0f);//bottom of window
		glVertex3f(1.0f, 0.0f, 0.0f);//right of window
		glVertex3f(0.0f, 1.0f, 0.0f);//top of window
		glEnd();//end drawing of line loop
		*/

		/*
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 300; i++){
		double angle = 2 * M_PI * i / 300;
		double x = cos(angle);
		double y = sin(angle);
		glVertex3f(xi+x+1 , yi+y+1,zi);
		}
		glEnd();
		*/

		//glBegin(GL_QUADS);
		//glNormal3f(0,0,1);
		//glVertex3f(xi,yi,zi);
		//glVertex3f(xf,yi,zf);
		//glVertex3f(xf,yf,zf);
		//glVertex3f(xi,yf,zi);
		//glEnd();
		/*
		if(estado.apresentaNormais) {
		desenhaNormal(xi,yi,zi,cross,azul);
		desenhaNormal(xf,yi,zf,cross,azul);
		desenhaNormal(xf,yf,zf,cross,azul);
		desenhaNormal(xi,yi,zi,cross,azul);
		}
		*/
		break;
	}
}




void desenhaLigacao(Arco arco){
	No *noi, *nof;// dois n�s que vao ser ligados
	GLUquadricObj *obj = gluNewQuadric();
	GLdouble distanciaLig;
	GLdouble angOrientacao;
	GLdouble catetoOposto;
	GLdouble tamanhoCA;
	GLdouble angInclinacao;


	noi = &nos[arco.noi];
	nof = &nos[arco.nof];

	//material(cinza);
	material(red_plastic);

	glPushMatrix();
	//mover para o n� inicial para coem�ar a desenhar
	glTranslatef(noi->x, noi->y, noi->z);
	//Desnivel
	catetoOposto = nof->z - noi->z;
	//base do triangulo
	tamanhoCA = sqrt(pow((nof->x - noi->x), 2) + pow((nof->y - noi->y), 2));
	//distancia entre os 2 n�s
	distanciaLig = sqrt(pow((nof->x - noi->x), 2) + pow((nof->y - noi->y), 2) + pow((nof->z - noi->z), 2));
	angInclinacao = radToDeg(atan2(catetoOposto, tamanhoCA));
	//Angulo de rotacao dos zz
	angOrientacao = radToDeg(atan2(nof->y - noi->y, nof->x - noi->x));
	glRotated(angOrientacao, 0, 0, 1);
	//Angulo de rotacao dos yy
	glRotated(angInclinacao - 90, 0, -1, 0);
	//a largura da liga��o pode variar, mas apenas est� presente a for�a de liga��o definida pelo utilizador actual.
	gluCylinder(obj, arco.forcaLig / 5, arco.forcaLig / 5, distanciaLig, 30, 30);//30 numero de vertices
	glPopMatrix();



}

void desenhaEsferaNo(float largura){

	material(preto);
	glPushMatrix();
	//glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(largura / 2, 20, 20);
	glPopMatrix();

}

void drawGraph(){
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glScalef(5, 5, 5);
	material(red_plastic);
	/* desnha bolas que representam os n�s */
	for (int i = 0; i<numNos; i++){
		glPushMatrix();
		//material(preto);
		//move para as coordenadas onde tem que desenhar
		glTranslatef(nos[i].x, nos[i].y, nos[i].z);// +0.25);
		//desenhar esfera
		desenhaEsferaNo(nos[i].largura);

		glPopMatrix();
	}
	/* desnha os cilindors que represent�o as liga��es a cada n� */
	//material(emerald);
	for (int i = 0; i < numArcos; i++){
		desenhaLigacao(arcos[i]);
		//rampa pequena que sai do arco (talvez n�o necessario)
		//desenhaElemLigacao(arcos[i]);
	}
	glPopMatrix();
}

void desenhaElemLigacao(Arco arco){



}

void desenhaEixo(){
	gluCylinder(modelo.quad, 0.5, 0.5, 20, 16, 15);
	glPushMatrix();
	glTranslatef(0, 0, 20);
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(modelo.quad, 0.5, 2, 16, 6);
	glPopMatrix();
	gluCylinder(modelo.quad, 2, 0, 5, 16, 15);
	glPopMatrix();
}

#define EIXO_X		1
#define EIXO_Y		2
#define EIXO_Z		3

void desenhaPlanoDrag(int eixo){
	glPushMatrix();
	glTranslated(estado.eixo[0], estado.eixo[1], estado.eixo[2]);
	switch (eixo) {
	case EIXO_Y:
		if (abs(estado.camera.dir_lat)<M_PI / 4)
			glRotatef(-90, 0, 0, 1);
		else
			glRotatef(90, 1, 0, 0);
		material(red_plastic);
		break;
	case EIXO_X:
		if (abs(estado.camera.dir_lat)>M_PI / 6)
			glRotatef(90, 1, 0, 0);
		material(azul);
		break;
	case EIXO_Z:
		if (abs(cos(estado.camera.dir_long))>0.5)
			glRotatef(90, 0, 0, 1);

		material(emerald);
		break;
	}
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, 0, -100);
	glVertex3f(100, 0, -100);
	glVertex3f(100, 0, 100);
	glVertex3f(-100, 0, 100);
	glEnd();
	glPopMatrix();

}

void desenhaEixos(){

	glPushMatrix();
	glTranslated(estado.eixo[0], estado.eixo[1], estado.eixo[2]);
	material(emerald);
	glPushName(EIXO_Z);
	desenhaEixo();
	glPopName();
	glPushName(EIXO_Y);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	material(red_plastic);
	desenhaEixo();
	glPopMatrix();
	glPopName();
	glPushName(EIXO_X);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	material(azul);
	desenhaEixo();
	glPopMatrix();
	glPopName();
	glPopMatrix();

}

void setCamera(){
	Vertice eye;
	eye[0] = estado.camera.center[0] + estado.camera.dist*cos(estado.camera.dir_long)*cos(estado.camera.dir_lat);
	eye[1] = estado.camera.center[1] + estado.camera.dist*sin(estado.camera.dir_long)*cos(estado.camera.dir_lat);
	eye[2] = estado.camera.center[2] + estado.camera.dist*sin(estado.camera.dir_lat);

	if (estado.light){
		gluLookAt(eye[0], eye[1], eye[2], estado.camera.center[0], estado.camera.center[1], estado.camera.center[2], 0, 0, 1);
		putLights((GLfloat*)white_light);
	}
	else{
		putLights((GLfloat*)white_light);
		gluLookAt(eye[0], eye[1], eye[2], estado.camera.center[0], estado.camera.center[1], estado.camera.center[2], 0, 0, 1);
	}
}

void display(void)
{

	if (estado.estadoJogo == 0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		desenhaLogin(GL_SELECT);
		glutSwapBuffers();
		glFlush();

	}
	else if (estado.estadoJogo == 1){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		setCamera();

		material(slate);
		desenhaSolo();


		desenhaEixos();

		// desnha o grafo 3D
		drawGraph();

		if (estado.eixoTranslaccao) {
			// desenha plano de translac��o
			cout << "Translate... " << estado.eixoTranslaccao << endl;
			desenhaPlanoDrag(estado.eixoTranslaccao);

		}

		glFlush();
		glutSwapBuffers();
		
	}

}



void keyboard(unsigned char key, int x, int y)
{
	if (estado.estadoJogo==0){
		/*apanha o texto para username e password*/
		switch (key)
		{
		case 8:
			if (login.usernameSelected == true) {
				//se já estiver algo escrito
				if (login.username != "") {
					login.username = login.username.substr(0, login.username.size() - 1);
					//glutPostRedisplay();
					break;
				}
			}
			else if (login.passwordSelected == true){
				//se já estiver algo escrito
				if (login.password != "") {
					login.password = login.password.substr(0, login.password.size() - 1);
					//glutPostRedisplay();
					break;
				}
			}
		

		default:
			if (login.usernameSelected == true) {
				login.username += key;
				//cout << key << endl;
			}
			else if (login.passwordSelected==true && key!='\b'){ //obriga que a tecla pressionada seja diferente do backspace (impedir lixo no final de apagar tudo)
				login.password += key;
			}

		}
		

		/* chama  a função que escreve bno ecra */
		//cout << login.username << endl;
		//cout << login.password<< endl;
		escreveTexto();

		glutPostRedisplay();

	}
	else if (estado.estadoJogo == 1){
		switch (key)
		{
		case 27:
			exit(0);
			break;
		case 'h':
		case 'H':
			//imprime_ajuda();
			estado.estadoJogo = 1;
			gameInit();
			/* força a abertura do reshape pois vai mudar de 2D (menu) para 3D grafo */
			myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutPostRedisplay();

			cout << "modo jogo!" << endl;
			break;
		case 'l':
		case 'L':
			loginInit();
			estado.estadoJogo = 0;
			myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutPostRedisplay();

			/*
			if (estado.lightViewer)
			estado.lightViewer = 0;
			else
			estado.lightViewer = 1;
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, estado.lightViewer);
			glutPostRedisplay();
			*/
			break;
		case 'k':
		case 'K':
			estado.light = !estado.light;
			glutPostRedisplay();
			break;
		case 'w':
		case 'W':
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glutPostRedisplay();
			break;
		case 'p':
		case 'P':
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glutPostRedisplay();
			break;
		case 's':
		case 'S':
			glEnable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glutPostRedisplay();
			break;
		case 'c':
		case 'C':
			if (glIsEnabled(GL_CULL_FACE))
				glDisable(GL_CULL_FACE);
			else
				glEnable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		case 'n':
		case 'N':
			estado.apresentaNormais = !estado.apresentaNormais;
			glutPostRedisplay();
			break;
		case 'i':
		case 'I':
			initEstado();
			initModelo();
			glutPostRedisplay();
			break;
		}
	}
}

void Special(int key, int x, int y){

	switch (key){
	case GLUT_KEY_F1:
		gravaGrafo();
		break;
	case GLUT_KEY_F2:
		leGrafo();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F6:
		numNos = numArcos = 0;
		addNo(criaNo(0, 10, 0));  // 0
		addNo(criaNo(0, 5, 0));  // 1
		addNo(criaNo(-5, 5, 0));  // 2
		addNo(criaNo(5, 5, 0));  // 3
		addNo(criaNo(-5, 0, 0));  // 4
		addNo(criaNo(5, 0, 0));  // 5
		addNo(criaNo(-5, -5, 0));  // 6
		addArco(criaArco(0, 1, 1, 1));  // 0 - 1
		addArco(criaArco(1, 2, 1, 1));  // 1 - 2
		addArco(criaArco(1, 3, 1, 1));  // 1 - 3
		addArco(criaArco(2, 4, 1, 1));  // 2 - 4
		addArco(criaArco(3, 5, 1, 1));  // 3 - 5
		addArco(criaArco(4, 5, 1, 1));  // 4 - 5
		addArco(criaArco(4, 6, 1, 1));  // 4 - 6
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		estado.camera.dist -= 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		estado.camera.dist += 1;
		glutPostRedisplay();
		break;
	}
}


void setProjection(int x, int y, GLboolean picking){
	glLoadIdentity();
	if (picking) { // se est� no modo picking, l� viewport e define zona de picking
		GLint vport[4];
		glGetIntegerv(GL_VIEWPORT, vport);
		gluPickMatrix(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 4, 4, vport); // Inverte o y do rato para corresponder � jana
	}

	gluPerspective(estado.camera.fov, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1, 500);

}

void myReshape(int w, int h){
	
	if (estado.estadoJogo == 0){
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);

		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		gluOrtho2D(0, 100, 100, 0);

		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
	}
	else if (estado.estadoJogo == 1){
	
		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		setProjection(0, 0, GL_FALSE);
		glMatrixMode(GL_MODELVIEW);
	}

}


void motionRotate(int x, int y){
#define DRAG_SCALE	0.01
	double lim = M_PI / 2 - 0.1;
	estado.camera.dir_long += (estado.xMouse - x)*DRAG_SCALE;
	estado.camera.dir_lat -= (estado.yMouse - y)*DRAG_SCALE*0.5;
	if (estado.camera.dir_lat>lim)
		estado.camera.dir_lat = lim;
	else
	if (estado.camera.dir_lat<-lim)
		estado.camera.dir_lat = -lim;
	estado.xMouse = x;
	estado.yMouse = y;
	glutPostRedisplay();
}

void motionZoom(int x, int y){
#define ZOOM_SCALE	0.5
	estado.camera.dist -= (estado.yMouse - y)*ZOOM_SCALE;
	if (estado.camera.dist<5)
		estado.camera.dist = 5;
	else
	if (estado.camera.dist>200)
		estado.camera.dist = 200;
	estado.yMouse = y;
	glutPostRedisplay();
}

void motionDrag(int x, int y){
	GLuint buffer[100];
	GLint vp[4];
	GLdouble proj[16], mv[16];
	int n;
	GLdouble newx, newy, newz;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projec��o
	glLoadIdentity();
	setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera();
	desenhaPlanoDrag(estado.eixoTranslaccao);

	n = glRenderMode(GL_RENDER);
	if (n > 0) {
		glGetIntegerv(GL_VIEWPORT, vp);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, (double)buffer[2] / UINT_MAX, mv, proj, vp, &newx, &newy, &newz);
		printf("Novo x:%lf, y:%lf, z:%lf\n\n", newx, newy, newz);
		switch (estado.eixoTranslaccao) {
		case EIXO_X:
			estado.eixo[0] = newx;
			//estado.eixo[1]=newy;
			break;
		case EIXO_Y:
			estado.eixo[1] = newy;
			//estado.eixo[2]=newz;
			break;
		case EIXO_Z:
			//estado.eixo[0]=newx;
			estado.eixo[2] = newz;
			break;
		}
		glutPostRedisplay();
	}


	glMatrixMode(GL_PROJECTION); //rep�e matriz projec��o
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int picking(int x, int y){
	int i, n, objid = 0;
	double zmin = 10.0;
	GLuint buffer[100], *ptr;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projec��o
	glLoadIdentity();
	setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera();
	desenhaEixos();

	n = glRenderMode(GL_RENDER);
	if (n > 0)
	{
		ptr = buffer;
		for (i = 0; i < n; i++)
		{
			if (zmin >(double) ptr[1] / UINT_MAX) {
				zmin = (double)ptr[1] / UINT_MAX;
				objid = ptr[3];
			}
			ptr += 3 + ptr[0]; // ptr[0] contem o n�mero de nomes (normalmente 1); 3 corresponde a numnomes, zmin e zmax
		}
	}


	glMatrixMode(GL_PROJECTION); //rep�e matriz projec��o
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	return objid;
}

void userLogin(){
	/*chama a web service*/

}

void clickEvent(GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint names, *ptr;
	//printf("hits = %d\n", hits);
	ptr = (GLuint *)buffer;
	for (i = 0; i < hits; i++) { /* for each hit */
		names = *ptr;
		/*
		printf(" number of names for hit = %d\n", names);
		ptr++;
		printf(" z1 is %g;", (float)*ptr / 0xffffffff);
		ptr++;
		printf(" z2 is %g\n", (float)*ptr / 0xffffffff);
		ptr++;
		printf(" the name is ");
		*/
		ptr = ptr + 3;
		for (j = 0; j < names; j++) { /* for each name */
			if (*ptr == 1){
				/*carregou na zona de username*/
				login.usernameSelected = true;
				login.passwordSelected = false;

			}
			else if (*ptr == 2){
				/*carregou na zona de password*/
				login.passwordSelected = true;
				login.usernameSelected = false;
				
			}
			else if (*ptr == 3){
				/*carregou no botão de login*/
				userLogin();

				/*caso o login seja valido, abreo jogo*/
				estado.estadoJogo = 1;
				gameInit();
				/* força a abertura do reshape pois vai mudar de 2D (menu) para 3D grafo */
				myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
				glutPostRedisplay();
			}
			else if (*ptr == 4){
				/*carregou no botão modo offline*/
				cout << "Modo offline - A implementar" << endl;
			}
			else if (*ptr == 0){
				/*carregou em sair*/
			
			}


			//printf("%d ", *ptr);
			ptr++;
		}
		//printf("\n");
	}
}



void mouse(int btn, int state, int x, int y){
	
	if (estado.estadoJogo==0){ // se estiver no menu de login
		GLuint selectBuf[BUFSIZE];
		GLint hits;
		GLint viewport[4];
		if (btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
			return;
		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer(BUFSIZE, selectBuf);
		(void)glRenderMode(GL_SELECT);
		glInitNames();
		glPushName((GLuint)~0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		/* create 5x5 pixel picking region near cursor location */
		gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 0.5, 0.5, viewport);
		gluOrtho2D(0, 100, 100, 0);
		desenhaLogin(GL_SELECT);

		glPopMatrix();
		glFlush();
		hits = glRenderMode(GL_RENDER);
		clickEvent(hits, selectBuf);
	}
	else if (estado.estadoJogo == 1){ // se estiver no jogo 3D tem outro tipo de picking
		switch (btn) {
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN){
				estado.xMouse = x;
				estado.yMouse = y;
				if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
					glutMotionFunc(motionZoom);
				else
					glutMotionFunc(motionRotate);
				cout << "Left down\n";
			}
			else{
				glutMotionFunc(NULL);
				cout << "Left up\n";
			}
			break;
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN){
				estado.eixoTranslaccao = picking(x, y);
				if (estado.eixoTranslaccao)
					glutMotionFunc(motionDrag);
				cout << "Right down - objecto:" << estado.eixoTranslaccao << endl;
			}
			else{
				if (estado.eixoTranslaccao != 0) {
					estado.camera.center[0] = estado.eixo[0];
					estado.camera.center[1] = estado.eixo[1];
					estado.camera.center[2] = estado.eixo[2];
					glutMotionFunc(NULL);
					estado.eixoTranslaccao = 0;
					glutPostRedisplay();
				}
				cout << "Right up\n";
			}
			break;
		}
	}
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700); //tamanho da janela
	glutCreateWindow("SocialGame - EpicWare"); //nome da janela

	/* fazer novo init*/
	estado.estadoJogo = 0;
	login.usernameSelected = true;

	//gameInit();

	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	/*  Funcionalidade do teclado  */
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(Special);
	/*  Funcionalidades do rato   */
	glutMouseFunc(mouse);

	imprime_ajuda();

	loginInit();
	
	



	glutMainLoop();
}
