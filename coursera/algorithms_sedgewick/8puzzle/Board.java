
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

public class Board {
	private char[][] _blocks;
	private int _dim;
	private int _dimSq;
	private int _manhattan;
	private int _hamming;
	private int _zi,_zj;

    public Board(int[][] blocks) {          // construct a board from an n-by-n array of blocks
		                                    // (where blocks[i][j] = block in row i, column j)

		if (blocks == null)
			throw new java.lang.NullPointerException();

		_dim = blocks.length;
		_dimSq = _dim * _dim;
		
		if (_dim < 2)
			throw new java.lang.IllegalArgumentException();

		_blocks = new char[_dim][];
		for (int i = 0; i < _dim; ++i) {
			if (blocks[i] == null)
				throw new java.lang.NullPointerException();
			if (blocks[i].length != _dim)
				throw new java.lang.IllegalArgumentException();
			_blocks[i] = new char[_dim];
			for (int j = 0; j < _dim; ++j) {
				_blocks[i][j] = (char)blocks[i][j];
				if (_blocks[i][j] == 0) {
					_zi = i; _zj = j;
				}
			}
		}

		_manhattan = Manhattan();
		_hamming = Hamming();
		//StdOut.println( "CONSTRUCTOR -- Manhattan:" + _manhattan + " Hamming:" + _hamming);
	}

	public int dimension() {                // board dimension n
		return _dim;
	}

	private int Hamming() {                  // number of blocks out of place
		int outOfPlace = 0;

		for (int i = 0; i < _dim; ++i)
			for (int j = 0; j < _dim; ++j) {
				int valid_num = (i*_dim + j + 1)%_dimSq;
				if (_blocks[i][j] != valid_num && _blocks[i][j] != 0)
					++outOfPlace;
			}

		return outOfPlace;
	}

	public int hamming() { return _hamming; }

	private int absolute(int val) {
		return (val<0) ? -val : val;
	}

	private int Manhattan() {                // sum of Manhattan distances between blocks and goal
		int totalManhattanDist = 0;

		for (int i = 0; i < _dim; ++i)
			for (int j = 0; j < _dim; ++j) 
				if (_blocks[i][j] != 0) {
					int value = _blocks[i][j] > 0 ? _blocks[i][j] : _dimSq;
					int row = (value-1)/_dim;
					int col = (value-1)%_dim;
					totalManhattanDist += (absolute(row-i)+absolute(col-j));
				}
		return totalManhattanDist;
	}
	
	public int manhattan() { return _manhattan; }

	public boolean isGoal() {               // is this board the goal board?
		return hamming() == 0;
	}

	public Board twin() {                   // a board that is obtained by exchanging any pair of blocks
		int i1,j1,i2,j2;
		if (_blocks[0][0] > 0) {
			i1 = 0; j1 = 0;
			if (_blocks[0][1] > 0) {
				i2 = 0; j2 = 1;
			}
			else { i2 = 1; j2 = 0; }
		}
		else { i1 = 0; j1 = 1; i2 = 1; j2 = 0; }

		return GetBoardBySwappingBlocks(i1,j1,i2,j2);
	}

	public boolean equals(Object y) {       // does this board equal y?
		if (y == this) return true;
		if (y == null) return false;
		if (y.getClass() != this.getClass()) return false;
		Board other = (Board)y;
		if (_dim != other._dim) return false;
		for (int i = 0; i < _dim; ++i)
			for (int j = 0; j < _dim; ++j)
				if (_blocks[i][j] != other._blocks[i][j])
					return false;
		return true;
	}

	private class List<Item> implements Iterable<Item> {
		private class Node { public Item item; public Node next; }
		private Node start, last;
		public List() { start = last = null; }
		public void Add(Item newitem) { 
			Node newnode = new Node();
			newnode.item = newitem;
			newnode.next = null;
			if ( start == null ) { start = last = newnode; }
			else { last.next = newnode; last = newnode; }
		}
		public Iterator<Item> iterator() {
			return new ForwardIterator();
		}

		private class ForwardIterator implements Iterator<Item> {
			private Node cur = start;
			public boolean hasNext() { return cur != null; }
			public void remove() { throw new UnsupportedOperationException(); }
			public Item next() {
				if (!hasNext()) throw new NoSuchElementException();
				Item curItem = cur.item;
				cur = cur.next;
				return curItem;
			}
		}
	}

	private Board GetBoardBySwappingBlocks( int i1, int j1, int i2, int j2 ) {
		int newblocks[][] = new int[_dim][_dim];
		for (int i = 0; i < _dim; ++i)
			for (int j = 0; j <_dim; ++j)
				newblocks[i][j] = (int)_blocks[i][j];

		int tmp = newblocks[i1][j1];
		newblocks[i1][j1] = newblocks[i2][j2];
		newblocks[i2][j2] = tmp;
		Board mySwapped = new Board(newblocks);
		return mySwapped;
	}

	public Iterable<Board> neighbors() {     // all neighboring boards
		List<Board> neighborsList = new List<Board>();

		for (int i = 0; i < _dim; ++i)
			for (int j = 0; j < _dim; ++j)
				if (_blocks[i][j] == 0) {
					if (i>0) neighborsList.Add(GetBoardBySwappingBlocks(i,j,i-1,j));
					if (j>0) neighborsList.Add(GetBoardBySwappingBlocks(i,j,i,j-1));
					if (i<(_dim-1)) neighborsList.Add(GetBoardBySwappingBlocks(i,j,i+1,j));
					if (j<(_dim-1)) neighborsList.Add(GetBoardBySwappingBlocks(i,j,i,j+1));
					break;
				}

		return neighborsList;
	}
		
	public String toString() {              // string representation of this board (in the output format specified below)
		StringBuilder s = new StringBuilder();
		s.append(_dim + "\n");
		for (int i = 0; i < _dim; i++) {
			for (int j = 0; j < _dim; j++) {
				s.append(String.format("%2d ", (int)_blocks[i][j]));
			}
			s.append("\n");
		}

		//s.append("Manhattan: " + _manhattan + " Hamming: " + _hamming + " IsGoal: " + isGoal());

		return s.toString();
	}



	public static void main(String[] args) { // unit tests (not graded)
		int blocksGoal[][] = { {2,1,3}, {4,5,6}, {7,8,0} };
		Board boardGoal = new Board( blocksGoal );

		StdOut.println( "Manhattan:" + boardGoal.manhattan() );
		StdOut.println( "Hamming:" + boardGoal.hamming() );
		StdOut.println( "IsGoal:" + boardGoal.isGoal() );
		StdOut.println( "Dim:" + boardGoal.dimension() );

		StdOut.println( "BOARD:" );
		StdOut.println( boardGoal );
		StdOut.println( "TWIN:" );
		Board twin = boardGoal.twin();
		StdOut.println( twin );

		StdOut.println( "NEIGHBORS:" );
		Iterable<Board> neighbors = boardGoal.neighbors();
		for (Board neighbor : neighbors)
			StdOut.println( neighbor );
	}
}

