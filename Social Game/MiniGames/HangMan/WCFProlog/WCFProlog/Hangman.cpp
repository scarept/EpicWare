#include "Hangman.h"
#include "HangmanLogic.h"
#include "WCF.h"

Estado estado;
Modelo modelo;
char word[80];
char category[80];
char guessList[80] = "";

CHangman::CHangman()
{
}


CHangman::~CHangman()
{
}


void Init(void){

	struct tm *current_time;
	time_t timer = time(0);

	//delay para o timer
	estado.delay = 1000;

	modelo.tamLado = 1;
	modelo.numLados = 4;
	modelo.raio = 0.1;
	modelo.tipoPoligono = GL_POLYGON;


	// Lê hora do Sistema
	current_time = localtime(&timer);
	modelo.hora.hor = current_time->tm_hour;
	modelo.hora.min = current_time->tm_min;
	modelo.hora.seg = current_time->tm_sec;

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

}

void Reshape(int width, int height)
{
	GLint size;

	if (width < height)
		size = width;
	else
		size = height;

	// glViewport(botom, left, width, height)
	// define parte da janela a ser utilizada pelo OpenGL

	glViewport(0, 0, (GLint)size, (GLint)size);


	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(left,right,bottom,top); 
	// projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1
	gluOrtho2D(-1, 1, -1, 1);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawGallowsPole(void){
	glPushMatrix();
	glColor3f(1, 1, 1);

	glTranslatef(-0.75, -0.75, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.3, -0.05);
	glVertex2f(0.0, -0.05);
	glEnd();

	//glRotatef((M_PI/2)*(-1), 0, 0, 1);
	glTranslatef(0.2, 0.0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glVertex2f(-0.1, 1.0);
	glVertex2f(-0.1, 0.0);
	glEnd();


	glTranslatef(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(0.5, -0.1);
	glVertex2f(0.0, -0.1);
	glEnd();

	glTranslatef(0.395, -0.1, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.1, 0.0);
	glVertex2f(0.1, -0.2);
	glEnd();
	glPopMatrix();
}


/*Draw stickman*/
void drawStickmanHead(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.15, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i){
		glVertex2f(cos((i*M_PI) / 180)*modelo.raio, sin((i*M_PI) / 180)*modelo.raio);
	}
	glEnd();
	glPopMatrix();
}

void drawStickmanBody(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.25, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -0.25);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftArm(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.325, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.1, -0.1);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightArm(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.325, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.1, -0.1);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftLeg(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.1, -0.1);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightLeg(void){
	glPushMatrix();
	glTranslatef(-0.05, -0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.1, -0.1);
	glEnd();
	glPopMatrix();
}
/*End Stickman*/


void drawText(char *txt){
	glPushMatrix();
	glColor3f(1, 1, 1);
	glRasterPos2f(0.2, -0.5);
	for (int i = 0; txt[i] != '\0'; ++i){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, txt[i]);
	}
	glPopMatrix();
}

void drawGuessedLetters(char *guesses){
	//strcat(guesses, "A B C D E F");
	glPushMatrix();
	glRasterPos2f(-0.75, 0.75);
	for (int i = 0; guesses[i] != '\0'; ++i){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, guesses[i]);
	}
	glPopMatrix();
}

void drawWordCategory(char *category){
	char result[80];
	strcpy(result, "CATEGORY: ");
	strcat(result, category);
	
	glPushMatrix();
	glRasterPos2f(0.2, 0.2);
	for (int i = 0; result[i] != '\0'; ++i){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, result[i]);
	}
	glPopMatrix();
}


// Callback de desenho
void Draw(void){
	drawGallowsPole();
	drawStickmanHead();
	drawStickmanBody();
	drawStickmanLeftArm();
	drawStickmanRightArm();
	drawStickmanLeftLeg();
	drawStickmanRightLeg();

	drawText(word);
	drawGuessedLetters(guessList);
	drawWordCategory("SHITS & STUFFS");

	glFlush();
	if (estado.doubleBuffer)
		glutSwapBuffers();
}

/*******************************
***   callbacks timer/idle   ***
*******************************/

// Callback Idle

void Idle(void)
{

	// accoes a tomar quando o glut está idle 

	// redesenhar o ecra 
	// glutPostRedisplay();
}

// Callback de temporizador

void Timer(int value)
{
	glutTimerFunc(estado.delay, Timer, 0);
	// ... accoes do temporizador ... 


	// redesenhar o ecra 
	glutPostRedisplay();
}


void imprime_ajuda(void)
{
	printf("\n\nDesenho de um quadrado\n");
	printf("h,H - Ajuda \n");
	printf("p,P - Poligono desenhado com GL_POLYGON\n");
	printf("t,T - Poligono desenhado com GL_TRIANGLE_FAN\n");
	printf("l,L - Poligono desenhado com GL_LINE_LOOP\n");
	printf("+   - Aumentar tamanho numero de Lados\n");
	printf("-   - Diminuir tamanho numero de Lados\n");
	printf("R   - Aumentar tamanho raio\n");
	printf("r   - Diminuir tamanho raio\n");
	printf("ESC - Sair\n");
}

/*******************************
***  callbacks de teclado    ***
*******************************/

// Callback para interaccao via teclado (carregar na tecla)

void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;
	case 'a':
	case 'A':
		//Cenas A
		break;
	case 'b':
	case 'B':
		//Cenas B
		break;
	case 'c':
	case 'C':
		//Cenas C
		break;
	case 'd':
	case 'D':
		//Cenas D
		break;
	case 'e':
	case 'E':
		//Cenas E
		break;
	case 'f':
	case 'F':
		//Cenas F
		break;
	case 'g':
	case 'G':
		//Cenas G
		break;
	case 'h':
	case 'H':
		//Cenas H
		break;
	case 'i':
	case 'I':
		//Cenas I
		break;
	case 'j':
	case 'J':
		//Cenas J
		break;
	case 'k':
	case 'K':
		//Cenas K
		break;
	case 'l':
	case 'L':
		//Cenas L
		break;
	case 'm':
	case 'M':
		//Cenas M
		break;
	case 'n':
	case 'N':
		//Cenas N
		break;
	case 'o':
	case 'O':
		//Cenas O
		break;
	case 'p':
	case 'P':
		//Cenas P
		break;
	case 'q':
	case 'Q':
		//Cenas Q
		break;
	case 'r':
	case 'R':
		//Cenas R
		break;
	case 's':
	case 'S':
		//Cenas S
		break;
	case 't':
	case 'T':
		//Cenas T
		break;
	case 'u':
	case 'U':
		//Cenas U
		break;
	case 'v':
	case 'V':
		//Cenas V
		break;
	case 'w':
	case 'W':
		//Cenas W
		break;
	case 'x':
	case 'X':
		//Cenas X
		break;
	case 'y':
	case 'Y':
		//Cenas Y
		break;
	case 'z':
	case 'Z':
		//Cenas Z
		break;
	}

	if (DEBUG)
		printf("Carregou na tecla %c\n", key);

}


void CHangman::startGame(int argc, char **argv)
{

	HangmanLogic s;

	/*---------------------*/

	//Open connection
	WCF* webService = new WCF();;

	std:vector<Word> words;

	words = webService->getEveryWord();

	for each (Word w in words){

		wprintf(L"%s\n", w.language);
		wprintf(L"%s\n", w.topic);
		wprintf(L"%s\n", w.text);

		printf("\n");
	}

	s.assertData(words);

	//Close connection and free heap
	webService->~WCF();

	/*---------------------*/

	//PlTermv av(3);
	//av[0] = "figurante";

	//PlQuery q("word", av);
	//while (q.next_solution())
	//	cout << (char *)av[1] << endl;
	
	s.chooseWord("Filmes", "Portugues");

	estado.doubleBuffer = GL_TRUE;

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 600);
	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Hangman") == GL_FALSE)
		exit(1);

	Init();

	imprime_ajuda();

	// Registar callbacks do GLUT

	// callbacks de janelas/desenho
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);

	// Callbacks de teclado
	glutKeyboardFunc(Key);
	//glutKeyboardUpFunc(KeyUp);
	//glutSpecialFunc(SpecialKey);
	//glutSpecialFunc(SpecialKeyUp);

	// callbacks timer/idle
	//glutTimerFunc(estado.delay, Timer, 0);
	//glutIdleFunc(Idle);


	// COMECAR...
	glutMainLoop();
}