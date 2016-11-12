
public class Register
{
    boolean open;
    Queue<Customer> queue;

    //constructor
    public Register()
    {
        open = true;
        queue = new Queue<Customer>();
    }

    // method
    public void open()
    {
        this. open = true;
    }
    
    public void close()
    {
        this.open = false;
    }
    
    public boolean isOpen()
    {
        return this.open;
    }
    
    public boolean hasCustomer()
    {
        if (queue.length() != 0)
            {
                return true;
            }

        else
            {
                return false;
            }
    }

    public boolean currentCustomerIsDone()
    {
        return queue.first().isDone();
    }

    public void step()
    {
      queue.first().serve(); 
    }
    
    public void addToQueue(Customer c)
    {
       queue.enqueue(c);
    }

    public Customer removeCurrentCustomer()
    {
        return queue.dequeue();
    }

    public int getQueueLength()
    {
        return queue.length();
    }

    /*
    public static void main(String[] args)
    {
        Customer c1 = new Customer(2, 5);
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9);
        Customer c4 = new Customer (0, 10);

        Register r = new Register();

        r.addToQueue(c1);
        r.addToQueue(c2);
        r.addToQueue(c3);
        r.addToQueue(c4);
        r.step();
        

        r.removeCurrentCustomer();
       
        
        

        int len = r.getQueueLength();
        System.out.println("Length:" + len);
        
        
       
    }
    */
}
