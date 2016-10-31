
import java.util.Arrays;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.In;

public class BruteCollinearPoints {
	private LineSegment [] segments;
	private int num_segments;
	private Point [] points;

	private static int DoubleCompare(double a, double b) {
		if( a < b-1e-9 ) return -1;
		else if( a > b+1e-9 ) return 1;
		return 0;
	}

	public BruteCollinearPoints(Point[] in_points) {   // finds all line segments containing 4 points
		if (in_points == null)
			throw new java.lang.NullPointerException();
		
		this.points = new Point[in_points.length];
		for (int i = 0; i < in_points.length; ++i)
			if (in_points[i] == null)
				throw new java.lang.NullPointerException();
			else
				this.points[i] = in_points[i];

		Arrays.sort(this.points);

		for (int i = 1; i < this.points.length; ++i)
			if (points[i].compareTo(points[i-1]) == 0)
				throw new java.lang.IllegalArgumentException("Repeated point!");

		segments = new LineSegment[1];
		num_segments = 0;
		
		for (int i = 0; i < points.length-3; ++i) {
			Point p = points[i];
			for (int j = i+1; j < points.length-2; ++j) {
				Point q = points[j];
				for (int k = j+1; k < points.length-1; ++k) {
					Point r = points[k];
					for (int l = k+1; l < points.length; ++l) {
						Point s = points[l];

						double slppq = p.slopeTo(q);
						double slppr = p.slopeTo(r);
						double slpps = p.slopeTo(s);
						if (DoubleCompare(slppq, slppr) == 0 && DoubleCompare(slppq, slpps) == 0) {
							if (segments.length == num_segments)
								segments = Arrays.copyOf(segments, num_segments*2);
							segments[ num_segments++ ] = new LineSegment(p, s);
						}
					}
				}
			}
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
		BruteCollinearPoints collinear = new BruteCollinearPoints(points);
		for (LineSegment segment : collinear.segments()) {
			StdOut.println(segment);
			segment.draw();
		}
		StdDraw.show();
	}

}

