precision mediump float;       	// Set the default precision to medium. We don't need as high of a 
								// precision in the fragment shader.
uniform vec3 u_LightPos;       	// The position of the light in eye space.
uniform sampler2D u_Texture;    // The input texture.
uniform vec2 c_seed;

varying vec3 v_Position;		// Interpolated position for this fragment.
varying vec4 v_Color;          	// This is the color from the vertex shader interpolated across the 
  								// triangle per fragment.
varying vec3 v_Normal;         	// Interpolated normal for this fragment.
varying vec2 v_TexCoordinate;   // Interpolated texture coordinate per fragment.
  
// The entry point for our fragment shader.
void main()                    		
{                              
	
	
    
	// Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);                  
	
	// Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);              	

	// Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
	// pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(v_Normal, lightVector), 0.0);               	  		  													  

	// Add attenuation. 
    diffuse = diffuse * (1.0 / (1.0 + (0.10 * distance)));
    
    // Add ambient lighting
    diffuse = diffuse + 0.3;  

	//first let's see if this pixel is a part of the Julia set. if not it will be black.
	vec2 z;
	int max_itr = 60;
	vec2 c;
    c.x = 1.3333 * (v_TexCoordinate.x - c_seed.x)*1.4 -c_seed.x;
    c.y = (v_TexCoordinate.y - c_seed.y)*1.4;////

    int i;
    float normelizedDist = 0.05;//
    float threashold = 1.9*1.9;//
    z = c;
    for(i=0; i<max_itr; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;
		normelizedDist = x * x + y * y;
		if(normelizedDist > threashold){
        	break;
        }//
        z.x = x;
        z.y = y;
    }
    gl_FragColor = v_Color * (diffuse) *normelizedDist;
	if(i== max_itr){
		gl_FragColor = v_Color * (diffuse+1.0) *normelizedDist;//
	}
	else{
		// Multiply the color by the diffuse illumination level and texture value to get final output color.
    	gl_FragColor = (v_Color * diffuse * texture2D(u_Texture, v_TexCoordinate));
    }                                 		
  }                                                                     	

