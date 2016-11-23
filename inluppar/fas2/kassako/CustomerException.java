/**
 * If <tt>serve</tt> method is performed on an zero of goods, then a 
 * <tt>CustomerException</tt> will be thrown.
 */

public class CustomerException extends RuntimeException
{
    public CustomerException()
    {
        super();
    }

    public CustomerException(String msg)
    {
        super(msg);
    }
}
