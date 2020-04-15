package Polyhedrons;

import android.opengl.Matrix;

import com.learnopengles.android.Polyhedrons.ShaderClass;
import com.learnopengles.android.Polyhedrons.Vector3D;

import badlogic.gdx.backends.android.AndroidGL20;

public abstract class AbstractPolyhedron {

	protected static final int BYTES_PER_FLOAT = 4;
	protected static final int BYTES_PER_SHORT = 2;
	protected Vector3D[] vertices;
	protected Vector3D[] vertexNormals;
	protected int[] vbo;
	protected int[] ibo;
	protected Vector3D mPosition;
	
	
	public AbstractPolyhedron() {
		mPosition = new Vector3D(0.0f, 0.0f, 0.0f);
	}	
	
	public void init(){
		buildVertices();
		buildNormals();
		buildBuffers();
	}
	abstract public void render(AndroidGL20 glEs20, ShaderClass shader);
	
	abstract protected void buildVertices();
	abstract protected void buildNormals();
	abstract protected void buildBuffers();
	abstract public void sendDataToGPU();
	
	protected class Polygon{
		
		private int[] indices;
		private Vector3D normal;
		public Polygon(int[] vertices){
			this.indices = vertices;
			this.normal = new Vector3D();
		}
		
		public Vector3D getVertex(int index){
			return vertices[indices[index]];
		}
		
		public Vector3D getNormal(){
			return this.normal;
		}
		
		public void setNormal(Vector3D normal){
			this.normal = normal;
		}
	}
	
	public void setPosition(float x, float y, float z){
		this.mPosition.x = x;
		this.mPosition.y = y;
		this.mPosition.z = z;
	}
	
	public void translate(float dx, float dy, float dz){
		this.mPosition.x += dx;
		this.mPosition.y += dy;
		this.mPosition.z += dz;
	}
	
	public void scale(float sx, float sy, float sz){
		this.mPosition.x *= sx;
		this.mPosition.y *= sy;
		this.mPosition.z *= sz;
	}
	
	public void rotate(float angleInDegrees, float rx, float ry, float rz){
		float mat[] = new float[16];
		Matrix.setIdentityM(mat, 0);
		Matrix.rotateM(mat, 0, angleInDegrees, rx, ry, rz);
		float rotated[] = new float[4];
		Matrix.multiplyMV(rotated, 0, mat, 0, new float[]{(float)(this.mPosition.x), (float)(this.mPosition.y), (float)(this.mPosition.z), 1}, 0);
		this.mPosition.x = rotated[0];
		this.mPosition.y = rotated[1];
		this.mPosition.z = rotated[2];
	}
	
}
