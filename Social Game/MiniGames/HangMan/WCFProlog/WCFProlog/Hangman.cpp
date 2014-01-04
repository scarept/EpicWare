#include "Hangman.h"
#include "HangmanLogic.h"
#include "WCF.h"

/*Global variables*/
Estado estado;
Modelo modelo;
HangmanLogic s;
vector<string> categories;
string language = "Portugues";

CHangman::CHangman(){}


CHangman::~CHangman(){}


void Init(void){

	struct tm *current_time;
	time_t timer = time(0);

	//delay para o timer
	estado.delay = 1000;

	categories = s.getTopicsByLanguage(language);

	if (WIDTH > HEIGHT)
		modelo.raio = 0.05*HEIGHT;	//Set stickman's head size
	else
		modelo.raio = 0.05*WIDTH;
	modelo.onGame = false; //Open in category menu
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

	// define parte da janela a ser utilizada pelo OpenGL
	glViewport(0, 0, (GLint)size, (GLint)size);


	// Matriz Projeccao
	// Matriz onde se define como o mundo e apresentado na janela
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// gluOrtho2D(left,right,bottom,top); 
	// projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1
	glutReshapeWindow(WIDTH, HEIGHT);
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	// Matriz Modelview
	// Matriz onde são realizadas as tranformacoes dos modelos desenhados
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*Draw stickman*/
void drawGallowsPole(void){
	glPushMatrix();
	glColor3f(1, 1, 1);

	glTranslatef(0.0375*WIDTH, 0.875*HEIGHT, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.1625*WIDTH, 0.0);
	glVertex2f(0.1625*WIDTH, 0.03125*HEIGHT);
	glVertex2f(0.0, 0.03125*HEIGHT);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(0.0625*WIDTH, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -0.375*HEIGHT);
	glVertex2f(0.0375*WIDTH, -0.375*HEIGHT);
	glVertex2f(0.0375*WIDTH, 0.0);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(0.0375*WIDTH, -0.375*HEIGHT, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.225*WIDTH, 0.0);
	glVertex2f(0.225*WIDTH, 0.03125*HEIGHT);
	glVertex2f(0.0, 0.03125*HEIGHT);
	glEnd();

	//glColor3f(1, 0, 0);
	glTranslatef(0.2225*WIDTH, 0.0325*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, 0.0);
	glVertex2f(0, 0.0625*HEIGHT);
	glEnd();
	glPopMatrix();
}

void drawStickmanHead(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.64375*HEIGHT, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i){
		glVertex2f(cos((i*M_PI) / 180)*modelo.raio, sin((i*M_PI) / 180)*modelo.raio);
	}
	glEnd();
	glPopMatrix();
}

void drawStickmanBody(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.69375*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.125*HEIGHT);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftArm(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.71875*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.0375*WIDTH, 0.0375*HEIGHT);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightArm(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.71875*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0375*WIDTH, 0.0375*HEIGHT);
	glEnd();
	glPopMatrix();
}

void drawStickmanLeftLeg(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.81875*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.0375*WIDTH, 0.0375*HEIGHT);
	glEnd();
	glPopMatrix();
}

void drawStickmanRightLeg(void){
	glPushMatrix();
	glTranslatef(0.36*WIDTH, 0.81875*HEIGHT, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0375*WIDTH, 0.0375*HEIGHT);
	glEnd();
	glPopMatrix();
}
/*End Stickman*/

/*Text */
void drawText(char *txt, int x, int y, float size){
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(size, size, 0);
	for (int i = 0; i< strlen(txt); i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, txt[i]);
	glPopMatrix();
}

void drawWordCategory(char *category){
	glPushMatrix();
	glTranslatef(WIDTH / 2 - strlen(category) * 80 / 2, HEIGHT / 5, 0);
	glRotatef(180 , 1.0, 0.0, 0.0);
	for (int i = 0; i< strlen(category); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, category[i]);
	glPopMatrix();
}
/*End text*/

/*Draw Buttons*/
void drawKeyboard(GLenum mode){
	GLuint letter[26];
	int xStart = WIDTH / 2, yStart = (2.0 / 3.0)*HEIGHT;
	char* prefix = "bt_";
	char* suffix = ".png";
	char let[2] = { 'A', 0 };
	char result[10];
	for (int i = 1; i <= 26; i++){
		if (strchr(modelo.guesses, (let[0] - 'A' + 'a')) == NULL){
			strcpy(result, prefix);
			strcat(result, let);
			strcat(result, suffix);
			glPushMatrix();
			if (mode == GL_SELECT)
				glLoadName(1000 + i);
			letter[i - 1] = carrega_texturas(result);

			glBindTexture(GL_TEXTURE_2D, letter[i - 1]);

			glBegin(GL_POLYGON);
			glTexCoord2f(0, 1);
			glVertex2f(xStart, yStart - (7.0 / 160.0)*HEIGHT);
			glTexCoord2f(1, 1);
			glVertex2f(xStart + (7.0 / 160.0)*WIDTH, yStart - (7.0 / 160.0)*HEIGHT);
			glTexCoord2f(1, 0);
			glVertex2f(xStart + (7.0 / 160.0)*WIDTH, yStart);
			glTexCoord2f(0, 0);
			glVertex2f(xStart, yStart);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, NULL);
			glPopMatrix();
		}
		let[0]++;
		if (i % 10 != 0){
			xStart += 0.05*WIDTH;
		}
		else if (i == 20){
			xStart = WIDTH / 2 + 0.1*WIDTH;
			yStart += 0.05*HEIGHT;
		}
		else{
			xStart = WIDTH / 2;
			yStart += 0.05*HEIGHT;
		}
	}
}

void drawCategoryButtons(GLenum mode){
	int identifierCounter = 0;
	int xStart = WIDTH / 2.0 - WIDTH / 4.0, xEnd = WIDTH / 2.0 + WIDTH / 4.0, yStart = HEIGHT/2.0 -	categories.size()/2.0 * 0.00625*HEIGHT, yEnd = yStart + 0.0625*HEIGHT;
	for each (string category in categories){
		glPushMatrix();
		if (mode == GL_SELECT)
			glLoadName(1100 + identifierCounter);
		glColor3d(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2f(xStart, yStart);
		glVertex2f(xEnd, yStart);
		glVertex2f(xEnd, yEnd);
		glVertex2f(xStart, yEnd);
		glEnd();	
		glPopMatrix();	

		glPushMatrix();
		glColor3d(0, 0, 0);
		drawText(&category[0], (xStart + xEnd) / 2 - strlen(&category[0]) / 2 * 20, yStart + ((yEnd - yStart) / 2.0) + 0.25*(yEnd - yStart), 0.2);
		glPopMatrix();
		
		identifierCounter++;
		yStart += 0.0625*HEIGHT + 0.00625*HEIGHT;
		yEnd = yStart + 0.0625*HEIGHT;
	}
}

void drawCategoriesMenu(GLenum mode){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawCategoryButtons(mode);
}
/*End Buttons*/

/*Game screen*/
void drawFinalScreen(char *message){
	glPushMatrix();
	glTranslatef(WIDTH /20.0, HEIGHT / 2.0 - 2 * HEIGHT / 100.0, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(0.8, 0.8, 1);
	for (int i = 0; i < strlen(message); i++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, message[i]);
	glPopMatrix();

}

void drawGameScreen(GLenum mode){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (s.isGameWon(modelo.word, modelo.guesses)){
		drawFinalScreen("YOU WIN!");
	}
	else if (modelo.numErrors >= 6){
		drawFinalScreen("YOU LOSE!");
	}
	else{
		glColor3f(1, 1, 1);
		drawText(modelo.category, WIDTH / 2 - strlen(modelo.category) * 80 / 2, HEIGHT / 5, (9.0 / (1.5*strlen(modelo.category))) < 1.0 ? (9.0 / (1.5*strlen(modelo.category))) : 1.0);
		drawText(modelo.partialWord, WIDTH / 20.0, HEIGHT / 3 + HEIGHT / 20, (9.0 / (1.5*strlen(modelo.partialWord))) < 1.0 ? (9.0 / (1.5*strlen(modelo.partialWord))) : 1.0);
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
	//glutSwapBuffers();
}

void clickEvent(GLint hits, GLuint *buffer){
	GLuint names, *ptr = buffer;
	char str[2];	/*char array little helper*/
	str[1] = 0;		/*put \0 in the end*/
	for (int i = 0; i < hits; i++){
		names = *ptr;	/*this is pure magic, just don't ask!*/
		ptr += 3;
		for (unsigned int j = 0; j < names; j++){
			/*If user clicked any letter on board*/
			if (*ptr > 1000 && *ptr < 1027){
				/*Add guess to guess list*/
				str[0] = (*ptr - 1001 + 'a');
				strcat(modelo.guesses, str);
				
				try{
					vector<int> indexes = s.validateGuess(&str[0], modelo.word);
					if (!indexes.empty()){
						while (!indexes.empty()){
							modelo.partialWord[indexes.back()] = str[0] - 'a' + 'A';
							indexes.pop_back();
						}
					}
					else{
						modelo.numErrors++;
					}
					drawGameScreen(GL_SELECT);
					glutSwapBuffers();
				}
				catch (PlException &plex){
				
					cout << (char*)plex;
				}

				
			}
			else if(*ptr >=1100 && *ptr < 1100+categories.size()) {
				cout << *ptr << endl;
				strcpy(modelo.category, &(categories[*ptr - 1100])[0]);
				modelo.onGame = true;
				try{
					//cout << s.chooseWord(modelo.category, language) << endl;
					strcpy(modelo.word, &(s.chooseWord(modelo.category, language))[0]);
					for (int i = 0; modelo.word[i] != '\0'; i++)
						modelo.partialWord[i] = '_';
					drawGameScreen(GL_SELECT);
					glutSwapBuffers();
				}
				catch (PlException &ex){
					cerr << (char *)ex << endl;
				}
			}
			else{
				cout << *ptr << endl;
			}
			ptr++;
		}
	}
}

void pickRects(int button, int state, int x, int y){
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
	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 1, 1, viewport);
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	if (modelo.onGame){
		drawGameScreen(GL_SELECT);
	}
	else{
		drawCategoriesMenu(GL_SELECT);
	}

	glPopMatrix();
	glFlush();
	hits = glRenderMode(GL_RENDER);
	clickEvent(hits, selectBuf);

}

// Callback de desenho
void Draw(void){
	
	if (!modelo.onGame){
		drawCategoriesMenu(GL_SELECT);
		glutSwapBuffers();
	}
	else{
		drawGameScreen(GL_SELECT);
		glutSwapBuffers();
	}

	glFlush();
}

void Timer(int value)
{
	glutTimerFunc(estado.delay, Timer, 0);
	// ... accoes do temporizador ... 


	// redesenhar o ecra 
	glutPostRedisplay();
}

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


void CHangman::startGame(int argc, char **argv){

	//Open connection
	WCF* webService = new WCF();;

	vector<Word> words;

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
	/*string tmp = s.chooseWord("Filmes", language);
	strcpy(modelo.word, &tmp[0] );
	for (int i = 0; modelo.word[i] != '\0'; i++)
		modelo.partialWord[i] = '_';*/

	/*cout << modelo.word << endl;
	cout << modelo.partialWord << endl;*/
	estado.doubleBuffer = GL_TRUE;
	
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
	if (glutCreateWindow("Hangman") == GL_FALSE)
		exit(1);

	Init();

	//imprime_ajuda();

	// Registar callbacks do GLUT

	// callbacks de janelas/desenho
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);

	glutMouseFunc(pickRects);
	
	// Callbacks de teclado
	glutKeyboardFunc(Key);

	// COMECAR...
	glutMainLoop();
}