

attribute vec4 MCvertex;
attribute vec3 MCnormal;

uniform mat4 u_MVMatrix;
uniform mat4 u_MVPMatrix;

uniform vec3 u_LightPosition;



varying float LightIntensity;
varying vec2 MCposition;

void main(){
	
	const float SpecularContribution = 0.3;
	const float DiffuseContribution = 1.0 - SpecularContribution;

	vec3 ecPosition = vec3(u_MVMatrix * MCvertex);
	vec3 tnorm = normalize(MCnormal);
	vec3 lightVec = normalize(u_LightPosition - ecPosition);
	vec3 reflectVec = reflect(-lightVec, tnorm);
	vec3 viewVec = normalize(-ecPosition);
	float diffuse = max(dot(lightVec, tnorm), 0.0);
	float spec = 0.0;
	
	if(diffuse > 0.0){
		spec = max(dot(reflectVec, viewVec), 0.0);
		spec = pow(spec, 16.0);
	}
	
	LightIntensity = DiffuseContribution * diffuse + SpecularContribution * spec;
	if(MCvertex.x != 0.0f)
		MCposition = MCvertex.yz;
	else if (MCvertex.y != 0.0f)
		MCposition = MCvertex.zx;
	else
		MCposition = MCvertex.yx;
	gl_Position = u_MVPMatrix * MCvertex;
}