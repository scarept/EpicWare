#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <GLUT/GL/glut.h>
#include <vector>
#include <SOIL\SOIL.h>

GLuint load2D(char * nomeTextura);

GLuint load3D(char * nomeTextura);

GLuint loadOpaqueTexture(char * nomeTextura);

GLuint loadTransparentTexture(char * nomeTextura);