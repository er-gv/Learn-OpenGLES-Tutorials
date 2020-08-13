precision mediump float;       	// Set the default precision to medium. We don't need as high of a 
								// precision in the fragment shader.

uniform mat4 u_MVPMatrix;		// A constant representing the combined model/view/projection matrix.
uniform mat4 u_MVMatrix;		// A constant representing the combined model/view matrix.

uniform vec3 u_LightPos;
uniform sampler2D u_Texture;    // The input texture.
uniform vec2 u_JuliaSeed;
uniform vec3 u_Color;

varying vec3 v_Position;
varying vec3 v_Normal;
varying vec2 v_TexCoordinate;


float juliaTester(float threashold, int max_itr, vec2 seed){

	//first let's see if this pixel is a part of the Julia set. if not it will be black.

	vec2 c;
    c.x = 1.3333 * (v_TexCoordinate.x - 0.5)*1.4-0.5;
    c.y = (v_TexCoordinate.y - 0.5)*1.4;////
    vec2 z=vec2(v_TexCoordinate.x-0.5, v_TexCoordinate.y-0.5);
    int i;
    float normelizedDist = 0.05;//
    //float threashold = 1.9*1.9;//
    //z = c;
    for(i=0; i<max_itr; i++) {
        float x = (z.x * z.x - z.y * z.y)+c.x;
        float y = (z.y * z.x + z.x * z.y)+c.y;
        normelizedDist = x * x + y * y;
		if(normelizedDist > threashold){
        	break;
        }//
        z.x = x;
        z.y = y;
    }
    if(i==max_itr) return 1.0;
    return float(i)/float(max_itr);

}
// The entry point for our fragment shader.
void main()                    		
{


    // Transform the normal's orientation into eye space.

    // Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);                  
	
	// Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);              	

	// Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
	// pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(normalize(v_Normal), lightVector), 0.0);

	// Add attenuation. 
    diffuse = diffuse * (1.0 / (1.0 + (0.10 * distance)));
    
    // Add ambient lighting
    diffuse = diffuse + 0.5;
    //gl_FragColor = vec4(u_Color, 1.0f)*diffuse* texture2D(u_Texture, v_TexCoordinate);
    float mask = juliaTester(4.0, 60, u_JuliaSeed);
    if(mask<1.0){

		gl_FragColor = vec4(mask*u_Color, 1.0f) * (diffuse+1.0);//
	}
	else{
		// Multiply the color by the diffuse illumination level and texture value to get final output color.
    	gl_FragColor = vec4(u_Color, 1.0f) * diffuse * texture2D(u_Texture, v_TexCoordinate);
    }
  }                                                                     	

