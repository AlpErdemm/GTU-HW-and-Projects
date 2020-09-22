import java.util.Iterator;
import java.util.NoSuchElementException;

public class GTUVector<T> extends GTUContainer<T> implements Iterable<T> {
    public GTUVector(int capacity) {
        arr = (T[]) new Comparable[capacity];
    }

    public GTUVector() {
        arr = getInitialArray();
    }

    private T[] getInitialArray() {
        return (T[]) new Comparable[INIT_CAPACITY];
    }

    public boolean contains(Object t1) {
        for (int i = 0; i < size; i++) {
            if (t1.equals(arr[i]))
                return true;
        }
        return false;
    }

    public void insert(T element) {
        // Capacity is full. Double the capacity.
        if (size == arr.length) {
            doubleCap();
        }
        arr[size++] = element;
    }

    void clear() {
        arr = getInitialArray();
        size = 0;
    }

    void erase(T element) {
        int ind = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i].equals(element)) {
                ind = i;
                break;
            }
        }

        // shift elements
        for (int i = ind + 1; i < size; i++) {
            arr[i-1] = arr[i];
        }

        // free the last element
        size--;
        arr[size] = null;
    }

    private void doubleCap(){
        T[] oldArray = arr;
        arr = (T[]) new Comparable[arr.length*2];
        System.arraycopy(oldArray, 0, arr, 0, size);
    }

    int size() {
        if (arr != null) {
            return size;
        }
        else {
            return 0;
        }
    }

    int max_size() {
        if (arr != null) {
            return arr.length;
        }
        else {
            return 0;
        }
    }

    boolean empty() {
        return size == 0;
    }

    class GTUIterator implements Iterator<T> {
        int position = 0;

        public boolean hasNext() {
            return position != size;
        }

        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            return arr[position++];
        }
    }

    public Iterator<T> iterator() {
        return new GTUIterator();
    }
}
