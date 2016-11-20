import java.util.Comparator;
import java.util.Arrays;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;

public class KdTree {
	private class Node {
		public Node left;
		public Node right;
		public Point2D p;
		public int size;
	}

	private Node _root;

	public         KdTree()                     {          // construct an empty set of points 
		_root = null;
	}
		
	public           boolean isEmpty()            {          // is the set empty? 
		return _root == null;
	}

	public               int size()               {          // number of points in the set 
		return isEmpty() ? 0 : _root.size;
	}

	private Node add(Node root, Node newnode, boolean xComp)
	{
		if (root == null) return newnode;
		// no need to check if we're adding duplicates! We're already taking care of that in insert().
		//if (newnode.p.x() == root.p.x() && newnode.p.y() == root.p.y()) return root;
		if (xComp ) {
			if (newnode.p.x() >= root.p.x()) root.right = add(root.right, newnode, !xComp);
			else root.left = add(root.left,newnode,!xComp);
		}
		else {
			if (newnode.p.y() >= root.p.y()) root.right = add(root.right, newnode, !xComp);
			else root.left = add(root.left,newnode,!xComp);
		}
		root.size += 1;
		return root;
	}

	public              void insert(Point2D p)    {          // add the point to the set (if it is not already in the set)
		if (p == null) throw new java.lang.NullPointerException();
		if (contains(p)) return;
		Node newnode = new Node();
		newnode.left = newnode.right = null;
		newnode.p = p;
		newnode.size = 1;

		_root = add(_root, newnode, true);
	}

	public           boolean contains(Point2D p)  {          // does the set contain point p? 
		if (p == null) throw new java.lang.NullPointerException();

		Node cur = _root;
		boolean xcmp = true;
		while (cur != null) {
			if (cur.p.x() == p.x() && cur.p.y() == p.y())
				return true;
			else if (xcmp) {
				if (p.x() >= cur.p.x()) cur = cur.right;
				else cur = cur.left;
			}
			else {
				if (p.y() >= cur.p.y()) cur = cur.right;
				else cur = cur.left;
			}
			xcmp = !xcmp;
		}

		return false;
	}

	private void draw(Node root, RectHV rect, boolean xcmp)
	{
		if (root == null) return;

		// draw point
		StdDraw.setPenColor(StdDraw.BLACK);
		StdDraw.setPenRadius(0.01);
		root.p.draw();

		// draw line
		if (xcmp) {
			StdDraw.setPenColor(StdDraw.RED);
			StdDraw.setPenRadius();
			StdDraw.line(root.p.x(),rect.ymin(),root.p.x(),rect.ymax());
		}
		else {
			StdDraw.setPenColor(StdDraw.BLUE);
			StdDraw.setPenRadius();
			StdDraw.line(rect.xmin(),root.p.y(),rect.xmax(),root.p.y());
		}

		RectHV rectLeft = new RectHV(rect.xmin(), rect.ymin(),root.p.x(),rect.ymax());
		RectHV rectRight = new RectHV(root.p.x(),rect.ymin(),rect.xmax(),rect.ymax());
		if (!xcmp) {
			rectLeft = new RectHV(rect.xmin(),rect.ymin(),rect.xmax(),root.p.y());
			rectRight = new RectHV(rect.xmin(),root.p.y(),rect.xmax(),rect.ymax());
		}

		draw(root.left, rectLeft, !xcmp);
		draw(root.right, rectRight, !xcmp);
	}

	public              void draw()               {          // draw all points to standard draw 
		draw(_root, new RectHV(0,0,1,1), true);
	}

	private void dfsRange(Node root, RectHV rect, SET<Point2D> rangeSet, boolean xcmp)
	{
		if (root == null) return;
		if (xcmp) {
			if (rect.xmax() >= root.p.x())
				dfsRange(root.right, rect, rangeSet, !xcmp);
			if (rect.xmin() < root.p.x())
				dfsRange(root.left, rect, rangeSet, !xcmp);
		}
		else {
			if (rect.ymax() >= root.p.y())
				dfsRange(root.right, rect, rangeSet, !xcmp);
			if (rect.ymin() < root.p.y())
				dfsRange(root.left, rect, rangeSet, !xcmp);
		}
		if (rect.contains(root.p)) rangeSet.add(root.p);
	}

	public Iterable<Point2D> range(RectHV rect)   {          // all points that are inside the rectangle 
		if (rect == null) throw new java.lang.NullPointerException();

		SET<Point2D> rangeSet = new SET<Point2D>();
		dfsRange(_root, rect, rangeSet, true);
		return rangeSet;
	}

	private Point2D dfsNearest(Node root, Point2D p, boolean xcmp, Point2D minP, RectHV rect)
	{
		if (root == null) return null;
		if (minP == null) minP = root.p;

		double distRoot = p.distanceSquaredTo(root.p);
		double distRootx = (p.x()-root.p.x())*(p.x()-root.p.x());
		double distRooty = (p.y()-root.p.y())*(p.y()-root.p.y());

		RectHV rectLeft = new RectHV(rect.xmin(), rect.ymin(),root.p.x(),rect.ymax());
		RectHV rectRight = new RectHV(root.p.x(),rect.ymin(),rect.xmax(),rect.ymax());
		if (!xcmp) {
			rectLeft = new RectHV(rect.xmin(),rect.ymin(),rect.xmax(),root.p.y());
			rectRight = new RectHV(rect.xmin(),root.p.y(),rect.xmax(),rect.ymax());
		}

		double minSofarSq = minP.distanceSquaredTo(p);

		if (minSofarSq > distRoot) {
			minSofarSq = distRoot;
			minP = root.p;
		}

		Point2D nearestCand1 = null;
		Point2D nearestCand2 = null;
		double distNearestCand1 = Double.MAX_VALUE;
		double distNearestCand2 = Double.MAX_VALUE;
		if (xcmp) {
			if (p.x() >= root.p.x())
				nearestCand1 = dfsNearest(root.right, p, !xcmp, minP, rectRight);
			else nearestCand1 = dfsNearest(root.left, p, !xcmp, minP, rectLeft);

  			if (nearestCand1 != null)
				distNearestCand1 = nearestCand1.distanceSquaredTo(p);
			if (minSofarSq > distNearestCand1) {
				minSofarSq = distNearestCand1;
				minP = nearestCand1;
			}

			if (minSofarSq > distRootx) {
				if (p.x() >= root.p.x())
					nearestCand2 = dfsNearest(root.left, p, !xcmp, minP, rectLeft);
				else nearestCand2 = dfsNearest(root.right, p, !xcmp, minP, rectRight);

				if (nearestCand2 != null)
					distNearestCand2 = nearestCand2.distanceSquaredTo(p);
				if (minSofarSq > distNearestCand2) {
					minSofarSq = distNearestCand2;
					minP = nearestCand2;
				}
			}
		}
		else {
			if (p.y() >= root.p.y())
				nearestCand1 = dfsNearest(root.right, p, !xcmp, minP, rectRight);
			else nearestCand1 = dfsNearest(root.left, p, !xcmp, minP, rectLeft);

  			if (nearestCand1 != null)
				distNearestCand1 = nearestCand1.distanceSquaredTo(p);
			if (minSofarSq > distNearestCand1) {
				minSofarSq = distNearestCand1;
				minP = nearestCand1;
			}

			if (minSofarSq > distRooty) {
				if (p.y() >= root.p.y())
					nearestCand2 = dfsNearest(root.left, p, !xcmp, minP, rectLeft);
				else nearestCand2 = dfsNearest(root.right, p, !xcmp, minP, rectRight);

				if (nearestCand2 != null)
					distNearestCand2 = nearestCand2.distanceSquaredTo(p);
				if (minSofarSq > distNearestCand2) {
					minSofarSq = distNearestCand2;
					minP = nearestCand2;
				}
			}
		}
		
		return minP;
	}

	public           Point2D nearest(Point2D p)   {          // a nearest neighbor in the set to point p; null if the set is empty 
		if (p == null) throw new java.lang.NullPointerException();
		return dfsNearest(_root, p, true, null, new RectHV(0,0,1,1));
	}

	public static void main(String[] args)                  // unit testing of the methods (optional) 
	{
        String filename = args[0];
        In in = new In(filename);

        StdDraw.enableDoubleBuffering();

        // initialize the data structures with N points from standard input
        KdTree kdtree = new KdTree();
        while (!in.isEmpty()) {
            double x = in.readDouble();
            double y = in.readDouble();
            Point2D p = new Point2D(x, y);
            kdtree.insert(p);
        }		
        // draw the points
        StdDraw.clear();
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.setPenRadius(0.01);
        kdtree.draw();
        StdDraw.show();

	}
}


