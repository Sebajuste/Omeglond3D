/*
// Shadow Split - fragment shader
*/

uniform sampler2D shadowMap0;
uniform sampler2D shadowMap1;
uniform sampler2D shadowMap2;

void main(void)
{
	vec4 color;

	if( gl_TexCoord[0].q > 1.0 )
	{
		color = texture2DProj(shadowMap0, gl_TexCoord[0] + vec4(0.0, 0.0, 0.0, 0.3);
		//color *= texture2DProj(shadowMap1, gl_TexCoord[1]) + vec4(0.0, 0.0, 0.0, 0.3);
		//color *= texture2DProj(shadowMap2, gl_TexCoord[2]) + vec4(0.0, 0.0, 0.0, 0.3);
	}

	gl_FragColor = color;
}
