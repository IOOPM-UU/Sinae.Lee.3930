/**
 * Queues order elements in a FIFO manner.
 * @author Sinae Lee
 * @author Marie Paulsson
 * @version 1.0
 * @since 2016-11-20
 */

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

    public Queue()
    {
        first = last = null;
        length = 0;
    }

/**
 * This method is used to get the length of queue.
 * 
 * @return int - a length of queue
 */
    public int length() {return this.length;}

   
/**
 * This method is used to get the boolean value if the queue is empty.
 * 
 * @return boolean true - if the queue is empty.
 */
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

/**
 * This method is used to insert an element into the queue.
 * @param element the element to add
 */
    
    public void enqueue(T element)
    {
        Node newNode = new Node(element, null);

        if (isEmpty() == true) {first = newNode;}
        
        else {last.next = newNode;}

        last = newNode;
        
        ++length;
    }

    
    /**
     * This method is used to remove and retrieve the head of the queue.
     * 
     * @return the head of the queue
     * @exception EmptyQueueException if the queue is empty
     */
    public T dequeue() throws EmptyQueueException
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
        --length;

        return element;
    }

    /**
     * This method is used to retrieve the head of the queue 
     * or throw an exception if the queue is empty.
     * 
     * @return the head of the queue
     * @exception EmptyQueueException if the queue is empty
     */

    public T first() throws EmptyQueueException 
    {

        if (!isEmpty())
            {
                T element = first.element;
                return element;
            }
       else
            {throw new EmptyQueueException();}

        
    }

}
