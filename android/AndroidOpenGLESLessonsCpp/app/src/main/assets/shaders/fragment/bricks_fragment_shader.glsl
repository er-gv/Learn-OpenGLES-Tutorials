
precision mediump float;

varying float LightIntensity;
varying vec2 MCposition;

uniform vec3 BrickColor;
uniform vec3 MortarColor;

uniform vec2 BrickSize;
uniform vec2 BrickPct;

void main(){

	vec3 color;
	vec2 position, useBrick;
	position = MCposition / BrickSize;
	if(fract(position.y * 0.5) > 0.5)
		position.x += 0.5;
		
	position = fract(position);
	useBrick = step(position, BrickPct);
	
	color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);
	color *= LightIntensity;
	gl_FragColor = vec4(color, 1.0);
}