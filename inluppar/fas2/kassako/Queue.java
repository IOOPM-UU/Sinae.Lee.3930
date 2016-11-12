

public class Queue<T>
{
    private Node first;
    private Node last;
    private int length;

    private class Node
    {
        private T element;
        private Node next;

        public Node (T element, Node next)
        {
            this.element = element;
            this.next = next;
        }
    }

    public int length() {return length;}

    // empty queue. constructor
    public Queue()
    {
        first = last = null;
        length = 0;
    }
    
    // is this queue empty?
    public boolean isEmpty()
    {
        if (first == null)
            {
                return true;
            }

        else
            {
                return false;
            }
    }

    //public Customer getElement() {return element;}
    
    public void enqueue(T element)
    {
        Node newNode = new Node(element, null);

        if (isEmpty() == true) {first = newNode;}
        
        else {last.next = newNode;}

        last = newNode;
        
        length++;

        System.out.println("adding: " + element);
    }

    
    // ta bort (och returnera) kunden som står först i kön
    public T dequeue()
    {
        if (isEmpty() == true)
            {
                throw new EmptyQueueException();
            }
        
        T element = first.element;

        if (last == first)
            {
                last = null;
            }

        first = first.next;
        length--;

        System.out.println("dequeue: " + element);

        return element;
    }

    public T first()
    {
        if (isEmpty() == true)
            {
                throw new EmptyQueueException();
            }

        T element = first.element;

        System.out.println("first:" + element);
        return element;
    }

    @SuppressWarnings("unchecked") 
    public static void main(String [] args)
    {
        Customer c1 = new Customer (2, 5);
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9);
        Customer c4 = new Customer (0, 10);

        Queue q = new Queue();

        q.enqueue(c1);
        q.enqueue(c2);

        q.first();
        
        q.enqueue(c3);
        q.enqueue(c4);

        q.first();
        
        q.dequeue();

        q.first();
        
        q.dequeue();
        q.dequeue();

        q.first();

        q.dequeue();
        
        int size = q.length();
        System.out.println("length: " + size);
    }
}
    
   
