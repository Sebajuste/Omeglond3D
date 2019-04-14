/*
//  Parallax mapping - vertex shader
*/

varying vec3 eyeVec;
varying vec3 lightVec;

attribute vec3 vTangent;
attribute vec3 vBinormal;

void main(void)
{
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_Position = ftransform();

	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * vTangent);
	vec3 b = cross(n, t);

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	vec3 tmpVec = gl_LightSource[0].position.xyz - vVertex;
	lightVec.x = dot(tmpVec, t);
	lightVec.y = dot(tmpVec, b);
	lightVec.z = dot(tmpVec, n);

	tmpVec = -vVertex;
	eyeVec.x = dot(tmpVec, t);
	eyeVec.y = dot(tmpVec, b);
	eyeVec.z = dot(tmpVec, n);
}
