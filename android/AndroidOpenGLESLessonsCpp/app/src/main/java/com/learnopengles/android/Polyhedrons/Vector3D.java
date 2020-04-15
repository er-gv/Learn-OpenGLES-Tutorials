package com.learnopengles.android.Polyhedrons;

public class Vector3D {

	public float x,y,z;
	
	public Vector3D(){
		this.x = 0.0f;
		this.y = 0.0f;
		this.z = 0.0f;
	}
	
	public Vector3D(float x, float y, float z){
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public Vector3D(Vector3D v){
		this.x = v.x;
		this.y = v.y;
		this.z = v.z;
	}
	
	public void scale(float sc){
		this.x *= sc;
		this.y *= sc;
		this.z *= sc;
	}
	
	public static Vector3D subtract(Vector3D v1, Vector3D v2){
		return new Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	public static Vector3D sum(Vector3D v1, Vector3D v2){
		return new Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}
	
	public static Vector3D crossProduct(Vector3D v1, Vector3D v2){
		return new Vector3D(v1.y*v2.z - v1.z*v2.y, v2.x*v1.z - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	}
	
	public static float dotProduct(Vector3D v1, Vector3D v2){
		return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
	}
	
	public static Vector3D avarage(Vector3D[] vecs){
		Vector3D result = new Vector3D();
		for(int i=0; i<vecs.length; i++){
			result.x += vecs[1].x;
			result.y += vecs[1].y;
			result.z += vecs[1].z;
		}
		result.scale(vecs.length);
		return result;
	}
	
	public float length(){
		return (float)(Math.sqrt(x*x + y*y + z*z));
	}
	
	public void normalize(){
		float length = this.length();
		if(length != 0.0){
			x/=length;
			y/=length;
			z/=length;
		}
	}
	
}
