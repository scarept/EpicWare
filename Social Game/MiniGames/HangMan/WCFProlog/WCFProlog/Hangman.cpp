#include "Hangman.h"
#include "HangmanLogic.h"
#include "WCF.h"

/*Global variables*/
Estado estado;
Modelo modelo;

char word[80];
char category[80];
char guessList[80] = "";

CHangman::CHangman(){}


CHangman::~CHangman(){}


void Init(void){

	struct tm *current_time;
	time_t timer = time(0);

	//delay para o timer
	estado.delay = 1000;

	modelo.raio = 40;	//Set stickman's head size
	modelo.menuPoint = true; //Open in category menu
	modelo.numErrors = 0; //Draw only gallowsPole
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
	gluOrtho2D(0, 800, 800, 0);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*Draw stickman*/
void drawGallowsPole(void){
	glPushMatrix();
	glColor3f(1, 1, 1);

	glTranslatef(30, 700, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(130, 0.0);
	glVertex2f(130, 25);
	glVertex2f(0.0, 25);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(50, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -300);
	glVertex2f(30, -300);
	glVertex2f(30, 0.0);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(30, -300, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(180, 0.0);
	glVertex2f(180, 25);
	glVertex2f(0.0, 25);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(178, 26, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0.0);
	glVertex2f(0, 50);
	glEnd();
	glPopMatrix();
}

void drawStickmanHead(void){
	glPushMatrix();
	glTranslatef(288, 515, 0.0);
	//glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i){
		glVertex2f(cos((i*M_PI) / 180)*modelo.raio, sin((i*M_PI) / 180)*modelo.raio);
	}
	glEnd();
	glPopMatrix();
}

void drawStickmanBody(void){
	glPushMatrix();
	glTranslatef(288, 555, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 100);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftArm(void){
	glPushMatrix();
	glTranslatef(288, 575, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-30, 30);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightArm(void){
	glPushMatrix();
	glTranslatef(288, 575, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(30, 30);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftLeg(void){
	glPushMatrix();
	glTranslatef(288, 655, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-30, 30);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightLeg(void){
	glPushMatrix();
	glTranslatef(288, 655, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(30, 30);
	glEnd();
	glPopMatrix();
}
/*End Stickman*/

/*Draw Buttons*/
void drawKeyboard(GLenum mode){
	GLuint letter[26];
	int xStart = 400, yStart = 600;
	char* prefix = "bt_";
	char* suffix = ".png";
	char let[2] = { 'A', 0 };
	char result[10];
	for (int i = 1; i <= 26; i++){
		strcpy(result, prefix);
		strcat(result, let);
		strcat(result, suffix);
		glPushMatrix();
		if (mode == GL_SELECT)
			glLoadName(1000 + i);
		letter[i-1] = carrega_texturas(result);

		glBindTexture(GL_TEXTURE_2D, letter[i-1]);

		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1);
		glVertex2f(xStart, yStart - 35);
		glTexCoord2f(1, 1);
		glVertex2f(xStart + 35, yStart - 35);
		glTexCoord2f(1, 0);
		glVertex2f(xStart + 35, yStart);
		glTexCoord2f(0, 0);
		glVertex2f(xStart, yStart);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glPopMatrix();
		
		let[0]++;
		if (i == 0 || i % 10 !=0){
			xStart += 40;
		}
		else if (i == 20){
			xStart = 480;
			yStart += 40;
		}
		else{
			xStart = 400;
			yStart += 40;
		}
	}
}

/*
void drawLanguageMenu(GLenum mode){
	GLuint imagePT = carrega_texturas("bt_PT.png");
	GLuint imageEN = carrega_texturas("bt_EN.png");
	GLuint imageFR = carrega_texturas("bt_FR.png");
	GLuint imageDE = carrega_texturas("bt_DE.png");

	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(1);
	glBindTexture(GL_TEXTURE_2D, imagePT);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(25, 30);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(75, 30);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(75, 37);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(25, 37);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(2);
	glBindTexture(GL_TEXTURE_2D, imageEN);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(25, 40);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(75, 40);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(75, 47);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(25, 47);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(3);
	glBindTexture(GL_TEXTURE_2D, imageFR);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(25, 50);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(75, 50);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(75, 57);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(25, 57);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (mode == GL_SELECT)
		glLoadName(4);
	glBindTexture(GL_TEXTURE_2D, imageDE);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(25, 80);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(75, 80);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(75, 87);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(25, 87);
	glEnd();
	glPopMatrix();
}
*/

void drawCategoriesMenu(GLuint value){
	/*Do magic here*/
}

/*End Buttons*/

/*Game screen*/
void drawGameScreen(GLenum mode){
	drawGallowsPole();
	if (modelo.numErrors > 0)
		drawStickmanHead();
	if (modelo.numErrors > 1)
		drawStickmanBody();
	if (modelo.numErrors > 2)
		drawStickmanLeftArm();
	if (modelo.numErrors > 3)
		drawStickmanRightArm();
	if (modelo.numErrors > 4)
		drawStickmanLeftLeg();
	if (modelo.numErrors > 5)
		drawStickmanRightLeg();
	drawKeyboard(mode);
}


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

void clickEvent(GLint hits, GLuint *buffer){
	//cout << "Pressed" << endl;
	GLuint names, *ptr = buffer;
	//cout << hits << endl;
	for (int i = 0; i < hits; i++){
		cout << "Inside!" << endl;
		names = *ptr;
		ptr += 3;
		
		for (int j = 0; j < names; j++){
			if (*ptr > 1000 && *ptr < 1027){
				//drawCategoriesMenu(*ptr);
				cout << (char)(*ptr - 1001 + 65) << endl;
				if (modelo.numErrors < 7)
					modelo.numErrors++;
				else
					modelo.numErrors = 0;
				glFlush();
			}
			else{
				cout << "Coisas" << endl;
				exit(0);
				
			}
			ptr++;
		}
	}
}

void pickRects(int button, int state, int x, int y)
{

	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer((GLsizei)BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName((GLuint)~0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	/* create 5x5 pixel picking region near cursor location */
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5, 5, viewport);
	gluOrtho2D(0, 800, 800, 0);
	drawGameScreen(GL_SELECT);

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEvent(hits, selectBuf);

}

// Callback de desenho
void Draw(void){
	
	if (!modelo.menuPoint){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawCategoriesMenu(GL_SELECT);
		glutSwapBuffers();
	}
	else{
		glClear(GL_COLOR_BUFFER_BIT);
		drawGameScreen(GL_SELECT);
		glutSwapBuffers();
	}
	//drawText(word);
	//drawGuessedLetters(guessList);
	//drawWordCategory("SHITS & STUFFS");

	glFlush();
	
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
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Hangman") == GL_FALSE)
		exit(1);

	Init();

	imprime_ajuda();

	// Registar callbacks do GLUT

	// callbacks de janelas/desenho
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);

	glutMouseFunc(pickRects);
	//glutMotionFunc(MouseMotion);
	//glutPassiveMotionFunc(MousePassiveMotion);

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