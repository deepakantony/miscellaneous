import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
	private int sz;
	private Item [] items_arr;

	public RandomizedQueue() {                // construct an empty randomized queue
		items_arr = (Item[]) new Object[2];
		sz = 0;
	}
	
	private void resize(int newsize) {
		if( newsize > sz ) {
			Item [] temp = ( Item[] ) new Object[newsize];
			for( int i = 0; i < sz; ++i )
				temp[i] = items_arr[i];
			items_arr = temp;
		}
	}

	public boolean isEmpty() {                // is the queue empty?
		return (sz == 0);
	}

	public int size() {                       // return the number of items on the queue
		return sz;
	}

	public void enqueue(Item item) {          // add the item
		if( item == null ) throw new NullPointerException("Cannot add a null item");
		if( items_arr.length == sz )
			resize(sz*2);
		items_arr[sz++] = item;
	}

	public Item dequeue() {                   // remove and return a random item
		if (isEmpty()) throw new NoSuchElementException("Queue underflow");
		int random_index = StdRandom.uniform(sz);
		Item tmp = items_arr[random_index];
		items_arr[random_index] = items_arr[sz-1];
		items_arr[sz-1] = tmp;
		sz--;
		if( sz < ( items_arr.length/4) )
			resize(items_arr.length/4);
		return tmp;
	}

	public Item sample() {                    // return (but do not remove) a random item
		if (isEmpty()) throw new NoSuchElementException("Queue underflow");
		return items_arr[ StdRandom.uniform(sz) ];
	}

	public Iterator<Item> iterator() {        // return an independent iterator over items in random order
		return new RandomIterator();
	}

	private class RandomIterator implements Iterator<Item> {
		Item [] copy_items_arr;
		int cur_index;
		
		RandomIterator() {
			copy_items_arr = (Item[]) new Object[sz];
			for( int i = 0; i < sz; ++i )
				copy_items_arr[i] = items_arr[i];
			StdRandom.shuffle(copy_items_arr);
			cur_index = 0;
		}

		public boolean hasNext() { return cur_index < sz; }
		public void remove() { throw new UnsupportedOperationException(); }
		public Item next() {
			if (!hasNext()) throw new NoSuchElementException();
			return copy_items_arr[cur_index++];
		}
	}

	private static <T> String GetString( RandomizedQueue<T> rq ) {
		String str = new String();
		str += "[ ";
		for(T val : rq) {
			str += (val.toString() + ", ");
		}
		str += " ]" + " Size: " + rq.size();
		return str;
	}

	public static void main(String[] args) {  // unit testing
		RandomizedQueue<Integer> rq = new RandomizedQueue<Integer>();

		for( int i = 0; i < 10; ++i )
			rq.enqueue(i);
		
		System.out.println(GetString(rq));

		Integer rand_a = rq.dequeue();
		Integer rand_b = rq.dequeue();
		System.out.println("Removed: " + rand_a + " & " + rand_b);
		System.out.println(GetString(rq));

		rand_a = rq.dequeue();
		rand_b = rq.dequeue();
		System.out.println("Removed: " + rand_a + " & " + rand_b);
		System.out.println(GetString(rq));

		rand_a = rq.dequeue();
		rand_b = rq.dequeue();
		System.out.println("Removed: " + rand_a + " & " + rand_b);
		System.out.println(GetString(rq));

		rand_a = rq.dequeue();
		rand_b = rq.dequeue();
		System.out.println("Removed: " + rand_a + " & " + rand_b);
		System.out.println(GetString(rq));

		rand_a = rq.dequeue();
		rand_b = rq.dequeue();
		System.out.println("Removed: " + rand_a + " & " + rand_b);
		System.out.println(GetString(rq));

		rq.enqueue(0);
		rq.enqueue(1);
		rq.enqueue(2);
		rq.enqueue(3);
		System.out.println(GetString(rq));
	}
}