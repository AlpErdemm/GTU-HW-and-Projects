import java.util.Iterator;

abstract class GTUContainer<T>{
    T arr[];
    int size = 0;
    final int INIT_CAPACITY = 10;

    abstract boolean empty();
    abstract int size();
    abstract int max_size();
    abstract void insert(T element);

    abstract void erase(T element);

    abstract void clear();

    abstract Iterator<T> iterator();
    abstract boolean contains(Object t1);
}