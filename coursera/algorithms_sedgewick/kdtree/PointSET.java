import java.util.Comparator;
import java.util.Arrays;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;

public class PointSET {
	private SET<Point2D> _set;

	public         PointSET()                     {          // construct an empty set of points 
		_set = new SET<Point2D>();
	}
		
	public           boolean isEmpty()            {          // is the set empty? 
		return _set.isEmpty();
	}

	public               int size()               {          // number of points in the set 
		return _set.size();
	}

	public              void insert(Point2D p)    {          // add the point to the set (if it is not already in the set)
		if (p == null) throw new java.lang.NullPointerException();
		_set.add(p);
	}

	public           boolean contains(Point2D p)  {          // does the set contain point p? 
		if (p == null) throw new java.lang.NullPointerException();
		return _set.contains(p);
	}

	public              void draw()               {          // draw all points to standard draw 
		for (Point2D p : _set)
			p.draw();
	}

	public Iterable<Point2D> range(RectHV rect)   {          // all points that are inside the rectangle 
		if (rect == null) throw new java.lang.NullPointerException();

		SET<Point2D> rangeSet = new SET<Point2D>();

		for (Point2D p : _set)
			if (rect.contains(p))
				rangeSet.add(p);

		return rangeSet;
	}

	public           Point2D nearest(Point2D p)   {          // a nearest neighbor in the set to point p; null if the set is empty 
		if (p == null) throw new java.lang.NullPointerException();

		double minDist = Double.MAX_VALUE;
		Point2D minP = null;
		for (Point2D curP : _set) {
			double distSq = p.distanceSquaredTo(curP);
			if (distSq < minDist) {
				minDist = distSq;
				minP = curP;
			}
		}

		return minP;
	}

	public static void main(String[] args)                  // unit testing of the methods (optional) 
	{
		
	}
}


