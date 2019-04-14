/*
// Shadow Split - vertex shader
*/

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_Vertex;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_Vertex;
	gl_TexCoord[2] = gl_TextureMatrix[2] * gl_Vertex;

	gl_Position = ftransform();
}

