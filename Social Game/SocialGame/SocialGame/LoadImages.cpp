#include "LoadImages.h"



GLuint carrega_texturas(char * nomeTextura){
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glEnable(GL_TEXTURE_2D); //em 3D necessario desativar

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	GLuint imagem = SOIL_load_OGL_texture
		(
		nomeTextura,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);


	/* check for an error during the load process */
	if (0 == imagem)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	return imagem;
}