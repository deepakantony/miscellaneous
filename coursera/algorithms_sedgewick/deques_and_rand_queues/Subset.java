import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Subset {
	public static void main(String[] args) {
		if( args.length <= 0 ) throw new IllegalArgumentException("Please specify k in the command line argument");
		int k = Integer.parseInt(args[0]);

		RandomizedQueue<String> rq = new RandomizedQueue<String>();

		int j = 0;
		if( k != 0 ) {
			while(!StdIn.isEmpty()) {
				String s = StdIn.readString();
				if( s.length() > 0 ) {
					if( j < k )
						rq.enqueue(s);
					else {
						String old = rq.dequeue();
						int r = StdRandom.uniform(j+1);
						if( r < k ) rq.enqueue(s);
						else rq.enqueue(old);										
					}
					++j;
				}
			}
		}


		int i = 0;
		for( String s : rq ) {
			if( i >= k ) break;
			System.out.println(s);
			++i;
		}
	}
}