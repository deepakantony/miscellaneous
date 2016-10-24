import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;
//import edu.princeton.cs.algs4.QuickFindUF;
import java.lang.IllegalArgumentException;
import java.lang.IndexOutOfBoundsException;

public class Percolation {
	private WeightedQuickUnionUF uf;
	private WeightedQuickUnionUF uf_no_vb; // no virtual bottom
	//private QuickFindUF uf;
	private int n;
	private boolean grid[];

	public Percolation(int n)               // create n-by-n grid, with all sites blocked
	{
		if( n <= 0 )
			throw new IllegalArgumentException();
		this.uf = new WeightedQuickUnionUF(n*n + 2);
		this.uf_no_vb = new WeightedQuickUnionUF(n*n+1);
		//this.uf = new QuickFindUF(n*n+2);
		this.n = n;
		this.grid = new boolean[n*n];
		
		for(int i = 0; i < n*n; ++i )
			this.grid[i] = false;

		// Connect virtual top/bottom
		//		for( int i = 0; i < n; ++i )
		//uf.union(getID(0,i), 
	}

	private void verify(int i, int j )
	{
		if( i < 1 || i > n || j < 1 || j > n )
			throw new IndexOutOfBoundsException();
	}

	private int getID(int i, int j )
	{
		return (i-1)*n+(j-1);
	}

	private void open(int i, int j, WeightedQuickUnionUF ufref)
	{
		if( i > 1 && isOpen(i-1,j) ) ufref.union(getID(i,j), getID(i-1, j));
		if( i < n && isOpen(i+1, j) ) ufref.union(getID(i,j), getID(i+1, j));
		if( j > 1 && isOpen(i,j-1) ) ufref.union(getID(i,j), getID(i, j-1));
		if( j < n && isOpen(i, j+1) ) ufref.union(getID(i,j), getID(i, j+1));
		this.grid[getID(i,j)] = true;
	}

	public void open(int i, int j)          // open site (row i, column j) if it is not open already
	{
		verify(i,j);
		open(i,j, uf);
		open(i,j, uf_no_vb);

			// Connect to the 2 open outside points.
		if( i == 1 ) {
			uf.union(getID(i,j), n*n);
			uf_no_vb.union(getID(i,j), n*n);
		}
		if( i == n )
			uf.union(getID(i,j), n*n+1);
	}

	public boolean isOpen(int i, int j)     // is site (row i, column j) open?
	{
		verify(i,j);
		return grid[getID(i,j)];
	}

	public boolean isFull(int i, int j)     // is site (row i, column j) full?
	{
		verify(i,j);
		return uf_no_vb.connected(getID(i,j), n*n);
	}

	public boolean percolates()             // does the system percolate?
	{
		return uf.connected(n*n, n*n+1);
	}

	public static void main(String[] args)  // test client (optional)
	{
	}
}

