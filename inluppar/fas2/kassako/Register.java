
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
        if (queue.length() > 1)
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
        try{
        return queue.first().isDone();
        }
        catch (EmptyQueueException e){return false;}
        
    }

    public void step()
    {
      
        if (isOpen()){

            //  if (currentCustomerIsDone())
            //  {
            //      removeCurrentCustomer();
                    
            //  }

            if (hasCustomer())
                {
                    queue.first().serve();
                }

           
            
        }
        
    }
    
    public void addToQueue(Customer c)
    {
       queue.enqueue(c);
    }

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

    public int getQueueLength()
    {
        return queue.length();
    }

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
    /*
    public String toString()
    {
        if(isOpen() && hasCustomer()){
            String s = "";  // create a String
            if(this.queue.length() > 0){
                
                s = this.queue.first().toString();
                int i = this.queue.length()-1;
                while(i > 0){
                    s += "@";
                    i--;
                }
            }
            return s;
        }else{
            return "X [ ]";
        }





            
       
       
        
    }
    */
   
    
    
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
       

      
       

        int l = r.getQueueLength();
        System.out.println(l);

        r.step();
        r.step();
        r.step();
        r.step();

        System.out.println(r.getQueueLength());

        
    }
    
    
    
    
}
