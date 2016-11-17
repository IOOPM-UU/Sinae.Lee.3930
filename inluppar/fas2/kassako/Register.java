
public class Register
{
    private boolean open;
    public Queue<Customer> queue;

    //constructor
    public Register()
    {
        open = false;  //close
        queue = new Queue<Customer>();
    }

    // method
    public void open()
    {
        this.open = true;
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
        try{
        if (isOpen() && hasCustomer())
            {
                queue.first().serve();
            }
        }
        catch (CustomerException e){};
    }
    
    public void addToQueue(Customer c)
    {
       queue.enqueue(c);
    }

    public Customer removeCurrentCustomer() throws EmptyQueueException
    {
        if (queue.length() != 0)
            {
                return queue.dequeue();
            }

        else
            {
                this.open = false;
                throw new EmptyQueueException();
            }
    }

    public int getQueueLength()
    {
        return queue.length();
    }

    
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

        System.out.println(s);
        return s;
        
    }
   
    
    
    public static void main(String[] args)
    {
        Customer c1 = new Customer(2, 5);
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9);
        Customer c4 = new Customer (0, 10);

        Register r = new Register();
        Register r1 = new Register();
        Register r2 = new Register();
        r.addToQueue(c1);
        r.addToQueue(c2);
        r.addToQueue(c3);
        r.addToQueue(c4);

        boolean yesOrNo =  r.hasCustomer();
        if (yesOrNo == true)
            {
                System.out.println("det finns customer");
            }
        else {System.out.println("ingen customer");}
            
        
        
        int g = c1.getGroceries();
        System.out.println("antal hos c1:" + g);

        

        int g1 = c2.getGroceries();
        System.out.println("antal hos c2:" + g1);

         
        r.removeCurrentCustomer();
        r.removeCurrentCustomer();
        r.removeCurrentCustomer();

        

        int g3 = r.queue.first().getGroceries();

        System.out.println("antal hos c1:" + g3);
        
        

        int len = r.getQueueLength();
        System.out.println("Length:" + len);


        r.addToQueue(c1);
        r.addToQueue(c2);
        r.addToQueue(c3);
        r.addToQueue(c4);
        r.step();
        r.step();
        r.step();
        r.step();
        r.step();
        r.step();
	
        int groc = r.queue.first().getGroceries();
        System.out.println("Groceries: " + groc);
        
        r.removeCurrentCustomer();        

        int leng = r.getQueueLength();
        System.out.println("Length:" + leng);

        r.toString();
        r1.toString();
        r2.toString();
        
        
        
       
    }
    
    
    
    
}
