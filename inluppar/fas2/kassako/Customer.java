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
    //metod registrera en av varor -minska på groceries
    public int serve()
    {
        for (int i=0; i < groceries; ++i)
            {
                --groceries;
            }

        return groceries;
        
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
    
}
