
public class main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//System.loadLibrary("MatrixMultiplyDebug");
		System.loadLibrary("MatrixMultiplyRelease");
		
		compareMultiply();
		comparePower();
	}
	
	public static void compareMultiply() {
		Matrix m2 = new Matrix(400,6000,2d);
		Matrix m1 = new Matrix(6000,300,2d);
		
		long jstart = System.currentTimeMillis();
		Matrix m3 = m1.multiply(m2);
		long jend = System.currentTimeMillis();
		
		long cstart = System.currentTimeMillis();
		Matrix m4 = m1.multiplyNative(m2);
		long cend = System.currentTimeMillis();
		
		System.out.println("Multiply, java: "+(jend-jstart)+ "ms C++: "+(cend-cstart)+"ms");
	}
	
	public static void comparePower() {
		Matrix m1 = new Matrix(200,200,2.0);
		
		long jstart = System.currentTimeMillis();
		Matrix m3 = m1.power(50);
		long jend = System.currentTimeMillis();
		
		long cstart = System.currentTimeMillis();
		Matrix m4 = m1.powerNative(50);
		long cend = System.currentTimeMillis();
		
		System.out.println("Power, java: "+ (jend-jstart) + "ms C++: "+(cend-cstart)+"ms");
	}
	/* Debug
	 * Multiply, java: 4794ms C++: 8958ms
	 * Power, java: 504ms C++: 2633ms
	 * 
	 * Release
	 * Multiply, java: 4771ms C++: 5040ms
	 * Power, java: 500ms C++: 363ms
	 */
	

}
