import java.util.Comparator;
import java.util.Arrays;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;


public class FastCollinearPoints {

	private LineSegment [] segments;
	private int num_segments;
	private Point [] points;

	private static int DoubleCompare(double a, double b) {
		if (a < b-1e-9) return -1;
		else if (a > b+1e-9) return 1;
		return 0;
	}

	private static int SeqSearchIndex(Point []points, int lo, int hi, Point key, Comparator<Point> c ) {
		for (int i = lo; i <= hi; ++i)
			if (c.compare(points[i], key)==0)
				return i;
		return -1;
	}

	private static int BinSearchIndex(Point []points, int lo, int hi, Point key, Comparator<Point> c ) {
		while (lo <= hi) {
			int mid = lo + (hi-lo)/2;
			if (c.compare(points[mid], key)==0)
				return mid;
			if (c.compare(points[mid], key)>0)
				hi = mid-1;
			else lo = mid+1;
		}
		return -1;
	}	

	private void ResizeSegments() {
		if (segments.length <= num_segments) {
			int new_size = (num_segments==0) ? 1 : num_segments*2;
			segments = Arrays.copyOf(segments, new_size);
		}
	}

	public FastCollinearPoints(Point[] in_points) {   // finds all line segments containing 4 points
		if (in_points == null)
			throw new java.lang.NullPointerException();
		
		this.points = new Point[in_points.length];
		for (int i = 0; i < in_points.length; ++i)
			if ( in_points[i] == null)
				throw new java.lang.NullPointerException();
			else
				this.points[i] = in_points[i];

		Arrays.sort(this.points);

		for (int i = 1; i < this.points.length; ++i)
			if (points[i].compareTo(points[i-1]) == 0)
				throw new java.lang.IllegalArgumentException("Repeated point!");

		segments = new LineSegment[1];
		num_segments = 0;
	
		int i = 0;
		for (i = 0; i < points.length - 3; ++i) {
			Point p = points[i];
			
			Arrays.sort(points, i+1, points.length, p.slopeOrder());

			if (i > 0) Arrays.sort(points, 0, i, p.slopeOrder());

			int dist_collinear = 0;
			Point max = p;

			for (int j = i+1; j < points.length; ++j) {
				Point q = points[j];

				if (DoubleCompare( p.slopeTo(q), p.slopeTo(max) ) == 0)
					++dist_collinear;
				else if (dist_collinear >= 3) {
					//int keyIndex = SeqSearchIndex(points, 0, i-1, max, p.slopeOrder());
					int keyIndex = BinSearchIndex(points, 0, i-1, max, p.slopeOrder());

					if (keyIndex == -1) {
						ResizeSegments();
						segments[num_segments++] = new LineSegment(p,max);
					}
					dist_collinear = 1;
				}
				else
					dist_collinear = 1;
				//StdOut.println(dist_collinear + " " + p + " -> " + q + " " + p.slopeTo(q) + " " + p.slopeTo(max));
				max = q;
			}

			if (dist_collinear >= 3) {
				//int keyIndex = SeqSearchIndex(points, 0, i-1, max, p.slopeOrder());
				int keyIndex = BinSearchIndex(points, 0, i-1, max, p.slopeOrder());
				if (keyIndex == -1) {
					ResizeSegments();
					segments[num_segments++] = new LineSegment(p, max);				
				}
			}

			Arrays.sort(points, i+1, points.length);
		}
	}

	public           int numberOfSegments() {       // the number of line segments
		return num_segments;
	}

	public LineSegment[] segments() {               // the line segments
		return Arrays.copyOf(segments, num_segments);
	}

	public static void main(String[] args) {
		// read the n points from a file
		In in = new In(args[0]);
		int n = in.readInt();
		Point[] points = new Point[n];
		for (int i = 0; i < n; i++) {
			int x = in.readInt();
			int y = in.readInt();
			points[i] = new Point(x, y);
		}

		// draw the points
		StdDraw.enableDoubleBuffering();
		StdDraw.setXscale(0, 32768);
		StdDraw.setYscale(0, 32768);
		for (Point p : points) {
			p.draw();
		}
		StdDraw.show();

		// print and draw the line segments
		FastCollinearPoints collinear = new FastCollinearPoints(points);
		for (LineSegment segment : collinear.segments()) {
			StdOut.println(segment);
			segment.draw();
		}
		StdDraw.show();
	}
}

