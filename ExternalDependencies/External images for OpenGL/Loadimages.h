#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GLUT/GL/glut.h>
#include <vector>
#include <SOIL\SOIL.h>

GLuint carrega_texturas(char * nomeTextura);

GLuint loadOpaqueTexture(char * nomeTextura);

GLuint loadTransparentTexture(char * nomeTextura);