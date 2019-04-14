/*
//  Shadow mapping - fragment shader
*/

uniform sampler2D shadowMap;

void main()
{
	vec4 color;

	if( gl_TexCoord[0].q > 1.0 )
	{
		color = texture2DProj(shadowMap, gl_TexCoord[0]) + vec4(0.0, 0.0, 0.0, 0.3);
	}

	gl_FragColor = color;
}
