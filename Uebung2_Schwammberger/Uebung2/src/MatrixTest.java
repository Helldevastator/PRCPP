import static org.junit.Assert.*;

import org.junit.Test;


public class MatrixTest {

	protected void setUp() throws Exception {
		//System.loadLibrary("MatrixMultiplyDebug");
		System.loadLibrary("MatrixMultiplyRelease");
	}
	
	@Test
	public void testMatrixIntInt() {
		Matrix m2 = new Matrix(5,2);
		Matrix m3 = new Matrix(32,32);
		Matrix m4 = new Matrix(32,32);
		
		assertEquals(5, m2.getWidth());
		assertEquals(2,m2.getHeight());
		assertFalse(m3.equals(m4)); //has a small chance to fail, it tests for random number generation.
	}

	@Test
	public void testMatrixIntIntDouble() {
		Matrix m1 = new Matrix(3,3,0.010d);
		Matrix m2 = new Matrix(3,3,0.010d);
		
		assertTrue(m1.equals(m2));
	}

	@Test
	public void testGetSetValueAt() {
		Matrix m1 = new Matrix(5,2,0.01d);
		
		m1.setValueAt(0, 0, 1d);
		m1.setValueAt(1, 0, 1d);
		m1.setValueAt(2, 0, 1d);
		m1.setValueAt(3, 1, 1d);
		m1.setValueAt(4, 1, 1d);
		
		assertEquals(1d,m1.getValueAt(0, 0));
		assertEquals(1d,m1.getValueAt(1, 0));
		assertEquals(1d,m1.getValueAt(2, 0));
		assertEquals(1d,m1.getValueAt(3, 1));
		assertEquals(1d,m1.getValueAt(4, 1));
		
		assertEquals(0.01d,m1.getValueAt(0, 1));
		assertEquals(0.01d,m1.getValueAt(1, 1));
		assertEquals(0.01d,m1.getValueAt(2, 1));
		assertEquals(0.01d,m1.getValueAt(3, 0));
		assertEquals(0.01d,m1.getValueAt(4, 0));
	}

	@Test
	public void testMultiplyNative() {
		Matrix m1 = new Matrix(5,2,2d);
		Matrix m2 = new Matrix(3,5,2d);
		Matrix m3 = new Matrix(3,2,20d);
		
		Matrix res = m1.multiplyNative(m2);
		
		assertTrue(res.equals(m3));
	}

	@Test
	public void testMultiply() {
		Matrix m1 = new Matrix(5,2,2d);
		Matrix m2 = new Matrix(3,5,2d);
		Matrix m3 = new Matrix(3,2,20d);
		
		Matrix res = m1.multiply(m2);
		
		assertTrue(res.equals(m3));
	}

	@Test
	public void testPower() {
		Matrix m1 = new Matrix(2,2,5d);
		Matrix m2 = new Matrix(2,2,50d);
		Matrix mk = m1.power(2);
		
		//assertTrue(m2.equals(mk));
	}

	@Test
	public void testPowerNative() {
		fail("Not yet implemented");
	}

	@Test
	public void testEqualsMatrix() {
		Matrix m1 = new Matrix(3,3,0.010d);
		Matrix m2 = new Matrix(3,3,0.010d);
		Matrix m3 = new Matrix(5,1,0.010d);
		Matrix m4 = new Matrix(3,3,0.011d);
		
		assertTrue(m1.equals(m2));
		assertFalse(m1.equals(m3));
		assertFalse(m1.equals(m4));
	}

}
