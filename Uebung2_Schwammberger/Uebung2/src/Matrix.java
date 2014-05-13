

import java.util.Random;

public class Matrix implements Cloneable {
	int width;
	int height;
	double[] matrix;
	
	public Matrix(int width, int height)
	{
		this.width = width;
		this.height = height;
		this.matrix = new double[width*height];
		
		Random rand = new Random();
		
		for(int i = 0; i < this.width;i++) {
			for(int j = 0; j < this.height;j++) {
				this.setValueAt(i, j, rand.nextDouble());
			}
		}
	}
	
	public Matrix(int width,int height, double initVal)
	{
		this.width = width;
		this.height = height;
		this.matrix = new double[width*height];
		
		for(int i = 0; i < this.width;i++) {
			for(int j = 0; j < this.height;j++) {
				this.setValueAt(i, j, initVal);
			}
		}
	}
	
	public int getWidth() {
		return this.width;
	}
	
	public int getHeight() {
		return this.height;
	}
	
	public double getValueAt(int x, int y) {
		return this.matrix[this.width * y + x];
	}
	
	public void setValueAt(int x, int y, double val) {
		this.matrix[this.width * y + x] = val;
	}
	
	public Matrix multiply(Matrix m) {
		if(this.width != m.height)
			return null;
		
		Matrix ret = new Matrix(m.width, this.height,0d);
		this.multiplyJ(m, ret);
		
		return ret;
	}
	
	public Matrix multiplyNative(Matrix m) {
		if(this.width != m.height)
			return null;
		
		Matrix res = new Matrix(m.width,this.height,0d);
		this.multiplyC(this.matrix, m.matrix, res.matrix, this.height, m.width, this.width);
		
		return res;
	}
	
	private native void multiplyC(double[] a, double[] b, double[] r, int i, int j, int k);
	
	private void multiplyJ(Matrix m, Matrix ret) {
		for (int i = 0; i < this.height;i++) {
			for(int j = 0; j < m.width;j++) {
				double val = 0d;
				
				for(int k = 0; k < this.width;k++) {
					val += this.getValueAt(k, i) * m.getValueAt(j, k);
				}
				
				ret.setValueAt(j, i, val);
			}
		}
	}
	
	public Matrix power(int k) {
		Matrix b = (Matrix)this.clone();
		Matrix r = (Matrix)this.clone();
		--k;
		
		for(int i = 0; i < k;++i) {
			this.multiplyJ(b, r);
			Matrix tmp = r;
			r = b;
			b = tmp;
		}
		
		return b;
	}
	
	
	private native void powerC(double[] a, int dimension, int pow);
	
	public Matrix powerNative(int k)
	{
		Matrix res = (Matrix)this.clone();
		
		this.powerC(res.matrix, this.width, k);
		return res;
	}
	
	public boolean equals(Matrix m) {
		if(this.width != m.getWidth() || this.height != m.getHeight())
			return false;
		
		if(m == this)
			return true;
		
		boolean answer = true;
		int i, j; i = j = 0;
		while(i < this.width && answer) {
			while(j < this.height && answer) {
				answer = this.getValueAt(i, j) == m.getValueAt(i, j);
				j++;
			}
			i++;
		}
		
		return answer;
	}
	
	public Object clone(){
		Matrix ret = new Matrix(this.width,this.height,0d);
		
		for(int i = 0;i < this.width;++i) {
			for(int j = 0;j < this.height;++j) {
				ret.setValueAt(i, j, this.getValueAt(i, j));
			}
		}
		
		return ret;
	}
}
