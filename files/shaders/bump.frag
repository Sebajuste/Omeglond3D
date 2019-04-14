/*
//  Bump mapping - fragment shader
*/


uniform sampler2D colorMap;
uniform sampler2D normalMap;

varying vec3 lightVec;

void main(void)
{
	vec4 base = texture2D(colorMap, gl_TexCoord[0].st);
	vec4 bump = (texture2D(normalMap, gl_TexCoord[0].st) - 0.5) * 2.0;

	float kc = gl_LightSource[0].constantAttenuation;
	float kl = gl_LightSource[0].linearAttenuation;
	float kq = gl_LightSource[0].quadraticAttenuation;

	float distSqr = dot(lightVec, lightVec);
	vec3 lVec = lightVec * inversesqrt(distSqr);

	vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

	float diffuse = max(dot(lVec, bump.xyz), 0.0);
	vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * diffuse;


	float att = 1.0 / (kc + kl*distSqr + kq*distSqr*distSqr);

	gl_FragColor = base * ((vAmbient * att) + (vDiffuse * att));
}
