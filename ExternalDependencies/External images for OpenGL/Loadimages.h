#include <iostream> 
#include <fstream> 
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <SOIL\src\SOIL.h>
#include <freeGLUT\include\GL\freeglut.h>
#include <vector>

GLuint load2D(char * nomeTextura);

GLuint load3D(char * nomeTextura);

GLuint loadOpaqueTexture(char * nomeTextura);

GLuint loadTransparentTexture(char * nomeTextura);