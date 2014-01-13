#include "Loadimages.h"

GLuint load3D(char * nomeTextura){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//glEnable(GL_TEXTURE_2D); //em 3D necessario desativar

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint imagem = SOIL_load_OGL_texture
		(
		nomeTextura,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
		);


	/* check for an error during the load process */
	if (0 == imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	return imagem;
}


GLuint load2D(char * nomeTextura){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint imagem = SOIL_load_OGL_texture
		(
		nomeTextura,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
		);


	/* check for an error during the load process */
	if (0 == imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	return imagem;
}

GLuint loadOpaqueTexture(char * nomeTextura){

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint imagem = SOIL_load_OGL_texture
		(
		nomeTextura,
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
		);


	/* check for an error during the load process */
	if (0 == imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glDisable(GL_TEXTURE_2D);

	return imagem;
}

GLuint loadTransparentTexture(char * nomeTextura){

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint imagem = SOIL_load_OGL_texture
		(
		nomeTextura,
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB
		);


	/* check for an error during the load process */
	if (0 == imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	return imagem;
}