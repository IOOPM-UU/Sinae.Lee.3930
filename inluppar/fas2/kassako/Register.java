
public class Register
{
    private boolean open;
    public Queue<Customer> queue;
    
    public Register()
    {
        open = false;  
        queue = new Queue<Customer>();
    }

    /**
     * This method is used to open a register.
     */
    public void open()
    {
        this.open = true;
    }

    /**
     * This method is used to close a register.
     */
    public void close()
    {
        this.open = false;
    }

    /**
     * This method is used to get a boolean value if a register is open.
     * 
     * @return true - if the register is open
     */
    public boolean isOpen()
    {
        return this.open;
    }

    /**
     * This method is used to get a boolean value if the register has a customer
     *
     * @return true - if there is/are customer(s)
     */
    public boolean hasCustomer()
    {
        if (queue.length() > 0)
            {
                return true;
            }

        else
            {
                return false;
            }
    }

    /**
     * This method is used to get a boolean value if the head of the queue have no goods.
     * 
     * @return true 
     * @exception EmptyQueueException if the queue is empty
     */

    public boolean currentCustomerIsDone() 
    {
        try{
        return queue.first().isDone();
        }
        catch (EmptyQueueException e){return false;}
        
    }

    /**
     * This method is used to reduce the queue if the register is open.
     */
    public void step()
    {
      
        if (isOpen())
            {


                if (hasCustomer())
                    {
                        queue.first().serve();
                    }

           
            
            }
        
    }

    /**
     * This method is used to add a customer into the queue.
     * 
     * @param c a Customer
     */
    
    public void addToQueue(Customer c)
    {
       queue.enqueue(c);
    }

        
    /**
     * This method is used to remove the head of the queue and return it.
     * 
     * @return Customer
     * @exception EmptyQueueException if the queue is empty and register is closed.
     */
    public Customer removeCurrentCustomer() throws EmptyQueueException
    {
        
        if (getQueueLength() != 0)
            {
                return queue.dequeue();
            }

        else
            {
                this.open = false;
                throw new EmptyQueueException();
            }
    }

    /**
     * This method is used to get the length of the queue.
     *
     * @return int - the length of the queue.
     */
    public int getQueueLength()
    {
        return queue.length();
    }

    /**
     * This method is used to represent the condition of registers.
     *
     * @return a string that textually represents the condition of registers.
     */
    @Override
    public String toString()
    {
        String s = "";  // create a String
        if (!isOpen() && !hasCustomer()) {s = s + " X ";}
            

        else {s = s + "   ";}

        if (!hasCustomer())
            {s= s + "[  ]";}

        else
            {
                s = s + queue.first().toString();

                for (int i = 1; i < queue.length(); ++i)
                    {s = s + "@";}

            }
        return s;
        
    }


}


