/**
 * If <tt>dequeue</tt> or <tt>first</tt> method is performed on an empty queue then 
 * <tt>EmptyQueueException</tt> will be thrown.
 */

public class EmptyQueueException extends RuntimeException
{
    public EmptyQueueException()
        { super(); }

    public EmptyQueueException(String msg)
        { super(msg); } 
}
