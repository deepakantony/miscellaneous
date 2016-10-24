import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
	private int sz;
	private Node first;
	private Node last;

	private class Node {
		public Item item;
		public Node next;
		public Node prev;
	}

	public Deque() {                           // construct an empty deque
		sz = 0;
		first = last = null;
		assert check();
	}

	public boolean isEmpty() {                // is the deque empty?
		return ( first == null );
	}

	public int size() {                        // return the number of items on the deque
		return sz;
	}

	public void addFirst(Item item) {          // add the item to the front
		if( item == null ) throw new NullPointerException("Cannot add a null item");
		Node old_first = first;
		first = new Node();
		first.item = item;
		first.next = old_first;
		first.prev = null;
		if( old_first != null )
			old_first.prev = first;
		if( last == null )
			last = first;
		++sz;
		assert check();
	}

	public void addLast(Item item) {           // add the item to the end
		if( item == null ) throw new NullPointerException("Cannot add a null item");
		Node old_last = last;
		last = new Node();
		last.item = item;
		last.next = null;
		last.prev = old_last;
		if( old_last != null )
			old_last.next = last;
		if( first == null )
			first = last;
		++sz;
		assert check();
	}

	public Item removeFirst() {                // remove and return the item from the front
		if (isEmpty()) throw new NoSuchElementException("Queue underflow");
		Item item = first.item;
		first = first.next;
		if( first == null )
			last = null;
		else
			first.prev = null;
		--sz;
		assert check();
		return item;
	}

	public Item removeLast() {                 // remove and return the item from the end
		if (isEmpty()) throw new NoSuchElementException("Queue underflow");
		Item item = last.item;
		last = last.prev;
		if( last == null )
			first = null;
		else
			last.next = null;
		--sz;
		assert check();
		return item;
	}

	public Iterator<Item> iterator() {         // return an iterator over items in order from front to end
		return new ForwardIterator();
	}

	private class ForwardIterator implements Iterator<Item> {
		Node cur_node = first;
		public boolean hasNext() { return (cur_node != null); }
		public void remove() { throw new UnsupportedOperationException(); }
		public Item next() {
			if (!hasNext()) throw new NoSuchElementException();
			Item cur_item = cur_node.item;
			cur_node = cur_node.next;
			return cur_item;
		}
	}

	private boolean check() {
		boolean valid = true;
		if( sz == 0 )
			valid = ( first == null && last == null );
		if( first == null )
			valid = ( sz == 0 && last == null );
		if( last == null )
			valid = ( sz == 0 && first == null );
		if( sz == 1 )
			valid = ( first != null && last == first && first.next == null && first.prev == null );
		if( last == first && last != null )
			valid = ( sz == 1 );
		if( first != null )
			valid = ( first.prev == null );
		if( last != null )
			valid = ( last.next == null );

		// can add more checks here

		return true;
	}

	private static <T> String GetString( Deque<T> dq ) {
		String str = new String();
		str += "[ ";
		for(T val : dq) {
			str += (val.toString() + ", ");
		}
		str += " ]" + " Size: " + dq.size();
		return str;
	}

	public static void main(String[] args) {   // unit testing
		Deque<Integer> q = new Deque<Integer>();

		for( int i = 0; i < 10; ++i )
			if( i%2 == 0 )
				q.addFirst(i);
			else
				q.addLast(i);

		System.out.println(GetString(q));

		Integer a = q.removeFirst();
		Integer b = q.removeLast();
		System.out.println("Removed: " + a + " & " + b );
		System.out.println(GetString(q));

		a = q.removeFirst();
		b = q.removeLast();
		System.out.println("Removed: " + a + " & " + b );
		System.out.println(GetString(q));
		
		a = q.removeFirst();
		b = q.removeLast();
		System.out.println("Removed: " + a + " & " + b );
		System.out.println(GetString(q));

		a = q.removeFirst();
		b = q.removeLast();
		System.out.println("Removed: " + a + " & " + b );
		System.out.println(GetString(q));

		a = q.removeFirst();
		b = q.removeLast();
		System.out.println("Removed: " + a + " & " + b );
		System.out.println(GetString(q));

		q.addFirst(0);
		q.addLast(1);
		q.addFirst(2);
		q.addLast(3);
		System.out.println(GetString(q));
	}
}

