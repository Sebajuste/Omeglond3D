/*
*/

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_Vertex;
	gl_Position = ftransform();		
}

