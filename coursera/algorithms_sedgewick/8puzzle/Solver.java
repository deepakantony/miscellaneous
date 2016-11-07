import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

public class Solver {
	private boolean _solvable;
	private StackList<Board> _solution;

	private class MoveNode implements Comparable<MoveNode> {
		public int priority;
		public int moveCount;
		public Board cur;
		public MoveNode prev;

		public int compareTo( MoveNode other ) {
			int dxPriority = priority - other.priority;
			if (dxPriority != 0)
				return dxPriority;
			int dxHamming = cur.hamming() - other.cur.hamming();
			if (dxHamming != 0)
				return dxHamming;
			int dxManhattan = cur.manhattan() - other.cur.manhattan();
			return dxManhattan;
		}
		public boolean isGoal() { return cur.isGoal(); }
		public int manhattan() { return cur.manhattan(); }
	}
	
	private StackList<Board> GetSolution(MoveNode goalNode) {
		StackList<Board> sol = null;

		if (goalNode.isGoal()) {
			sol = new StackList<Board>();
			sol.Add(goalNode.cur);
			MoveNode cur = goalNode;
			
			while (cur.prev != null) {
				cur = cur.prev;
				sol.Add(cur.cur);
			}
		}
		
		return sol;
	}

	private class StackList<Item> implements Iterable<Item> {
		private class Node { public Item item; public Node next; }
		private Node start;
		private int size;
		public StackList() { start = null; size = 0; }
		public void Add(Item newitem) { 
			Node newnode = new Node();
			newnode.item = newitem;
			newnode.next = start;
			start = newnode;
			++size;
		}
		public int Size() { return size; }
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


    public Solver(Board initial) {          // find a solution to the initial board (using the A* algorithm)
		MoveNode start = new MoveNode();
		start.priority = initial.manhattan();
		start.moveCount = 0;
		start.cur = initial;
		start.prev = null;
		MinPQ<MoveNode> pq = new MinPQ<MoveNode>();
		MoveNode cur = start;
		
		MoveNode startTwin = new MoveNode();
		Board twin = initial.twin();
		startTwin.priority = twin.manhattan();
		startTwin.moveCount = 0;
		startTwin.cur = twin;
		startTwin.prev = null;
		MinPQ<MoveNode> pqTwin = new MinPQ<MoveNode>();
		MoveNode curTwin = startTwin;
		
		while (!cur.isGoal() && !curTwin.isGoal()) {
			//StdOut.println( "CUR:\n" + cur.cur );
			// regular
			Iterable<Board> neighbors = cur.cur.neighbors();
			//StdOut.println( "NEIGHBORS:");
			for ( Board neighbor : neighbors ) 
				if ( cur.prev == null || !neighbor.equals(cur.prev.cur)) {
					MoveNode newnode = new MoveNode();
					newnode.moveCount = cur.moveCount + 1;
					newnode.priority = neighbor.manhattan() + newnode.moveCount;
					newnode.cur = neighbor;
					newnode.prev = cur;
					pq.insert(newnode);
					//StdOut.println(neighbor);
				}

			// twin
			//StdOut.println( "CURTWIN:\n" + curTwin.cur );
			Iterable<Board> neighborsTwin = curTwin.cur.neighbors();
			//StdOut.println( "NEIGHBORS TWIN:");
			for ( Board neighborTwin : neighborsTwin ) 
				if ( curTwin.prev == null || !neighborTwin.equals(curTwin.prev.cur)) {
					MoveNode newnodeTwin = new MoveNode();
					newnodeTwin.moveCount = curTwin.moveCount + 1;
					newnodeTwin.priority = neighborTwin.manhattan() + newnodeTwin.moveCount;
					newnodeTwin.cur = neighborTwin;
					newnodeTwin.prev = curTwin;
					pqTwin.insert(newnodeTwin);
					//StdOut.println(neighborTwin);
				}

			// pop PQ
			if (pq.isEmpty() || pqTwin.isEmpty()) break;
			cur = pq.delMin();
			curTwin = pqTwin.delMin();
		}

		if (cur.isGoal()) {
			_solution = GetSolution(cur);
			_solvable = true;
		}
		else {
			_solvable = false;
			_solution = null;
		}
	}

	public boolean isSolvable() {           // is the initial board solvable?
		return _solvable;
	}

	public int moves() {                    // min number of moves to solve initial board; -1 if unsolvable
		return (isSolvable()) ? _solution.Size()-1 : -1;			
	}

	public Iterable<Board> solution() {     // sequence of boards in a shortest solution; null if unsolvable
		return _solution;
	}

	public static void main(String[] args) {// solve a slider puzzle (given below)
		// create initial board from file
		In in = new In(args[0]);
		int n = in.readInt();
		int[][] blocks = new int[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				blocks[i][j] = in.readInt();
		Board initial = new Board(blocks);

		// solve the puzzle
		Solver solver = new Solver(initial);

		// print solution to standard output
		if (!solver.isSolvable())
			StdOut.println("No solution possible");
		else {
			StdOut.println("Minimum number of moves = " + solver.moves());
			for (Board board : solver.solution())
				StdOut.println(board);
		}
	}
}
