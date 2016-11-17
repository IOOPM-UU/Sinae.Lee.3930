//package kassako.customer;

public class Customer
{
    private int bornTime;    // tidssteget som kunden kom in i systemet
    private int groceries;  //antalet varor i kundkorg

    //constructor?
    public Customer (int bornTime, int groceries)
    {
        this.bornTime = bornTime;
        this.groceries = groceries;
    }

    // get number of groceries
    public int getGroceries()
    {
        return groceries;
    }

    public int getBornTime()
    {
        return bornTime;
    }

    //metod fråga om kunden är färdig
    public boolean isDone()
    {
        if (groceries == 0)
            {
                return true;
            }

        else
            {
                return false;
            }
    }

    // minska på groceries
    public void serve()
    {
        if(groceries == 0)
            {
                throw new CustomerException();
            }
        
        --groceries;
        
    }

    public String toString()
    {
        return "[" + groceries + "]";
    }


    
    
    public static void main (String[] args)
    {
        Customer c = new Customer(0, 3);

        c.serve();
        c.serve();
        c.serve();

         
        

        if(c.isDone())
            {
                System.out.println("The customer is done, just as expected!");
            }
        
        else
            {
                System.out.println("The customer is not done, but should be...");
        
            }

    }
   
}
