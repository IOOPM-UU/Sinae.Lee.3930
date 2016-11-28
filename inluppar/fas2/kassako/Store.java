public class Store
{
    private Register registers[];
    
    public Store(int amountOfRegisters)
    {
        if (amountOfRegisters > 0)
            {
                this.registers = new Register[amountOfRegisters];
                for(int i = 0; i < amountOfRegisters; ++i)
                    {
                        this.registers[i] = new Register();
                    }
                this.registers[0].open();
            }
    }
    
    /**
     * This method is used to calculate the sum of opened registers.
     * 
     * @return int - the sum of opened registers
     */
    public int getAmountOfOpenRegisters()
    {
        int totalOpenRegisters = 0;
        for (Register r : this.registers)
            {
                if(r.isOpen())
                    {
                        ++totalOpenRegisters;
                    }
            }
        return totalOpenRegisters;
    }

    /**
     * This method is used to calculate the sum of registers.
     * 
     * @return int - the sum of registers
     */
    public int getAmountOfRegisters()
    {
        int totalRegisters = 0;
        for (Register r : this.registers)
            {
                ++totalRegisters;
            }
        return totalRegisters;
    }

    /**
     * This method is used to calculate the sum of closed registers.
     *
     * @return int - the sum of closed registers
     */
    public int getAmountOfClosedRegisters()
    {
        return (getAmountOfRegisters() - getAmountOfOpenRegisters());
    }

    /**
     * This method is used to calculate the average queue length
     * 
     * @return int - the average queue length
     */
    public int getAverageQueueLength()
    {
        int totalCustomers = 0;
        int amountOfOpenRegisters = getAmountOfOpenRegisters();
	
        for (Register r : this.registers)
            {
                if (r.isOpen())
                    {
                        totalCustomers += r.getQueueLength();
                    }
            }
		
        return totalCustomers/amountOfOpenRegisters;
    }

    /**
     * This method is used to put a Customer into the shortes queue.
     *
     * @param c a Customer
     */
    
    public void newCustomer(Customer c)
    {
        int i = 0;
        int shortest = this.registers[i].getQueueLength();
        int totalRegisters = getAmountOfRegisters();
	
        for(int j = 1; j < totalRegisters; ++j)
            {
                if(this.registers[j].isOpen())
                    {
                        if(this.registers[j].getQueueLength() < shortest)
                            {
                                shortest = this.registers[j].getQueueLength();
                                i = j;
                    
                            }
                    }
            }
        
        this.registers[i].addToQueue(c);
    }

    /**
     * This method is used to reduce the queue of the registers.
     */
    
    public void step()
    {
        
        for(Register r: this.registers)
            {
                r.step();
            }
    }

    /**
     * This method is used to open a new register.
     */
    public void openNewRegister()
    {
        int amountOfRegisters = getAmountOfRegisters();
		
        for(int i = 0; i < amountOfRegisters; ++i)
            {
                if(!this.registers[i].isOpen())
                    {
                        this.registers[i].open();
                        break;
                    }
            }
    }

    /**
     * This method is used to put the customers that is done with paying into a queue.
     *
     * @return Queue a collection of finished Customers
     */
	
    public Queue<Customer> getDoneCustomers()
    {
        
        Queue<Customer> doneCustomers = new Queue<Customer>();
        
           
                for(Register r : this.registers)
                    {
                        if(r.isOpen() && r.currentCustomerIsDone())
                            {
                                doneCustomers.enqueue(r.removeCurrentCustomer());
                            }
                    }
                
        return doneCustomers;
    } 


    /**
     * This method is used to calculate the sum of customers that are in the queues.
     *
     * @return int - the sum of customers
     */
    public int getTotalCustomers()
    {
        int totCustomers = 0;
        for(Register r : this.registers)
            {
                totCustomers += r.queue.length();
            }
        
        return totCustomers;
    }

    /**
     * This method is used to represent the condition of store with breaking line.
     *
     * @return a string that textually represents the condition of store.
     */
    
    @Override
    public String toString()
    {
        String s = "";
        for (Register r : this.registers)
            {
                s = s + r.toString() + "\n";
            }
        
        return s;
    }

    /*
    public static void main(String[] args)
    {
        Customer c1 = new Customer(2, 5); 
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9); 
        Customer c4 = new Customer (0, 10);
        Customer c5 = new Customer(2, 5);
        Customer c6 = new Customer (5, 7);
        Customer c7 = new Customer (1, 9);
        Customer c8 = new Customer (0, 10);
        
        Store butik = new Store(5);
	
        butik.registers[1].open();
        butik.registers[3].open();
        
        butik.registers[0].addToQueue(c1);
        butik.registers[0].addToQueue(c2);
        butik.registers[1].addToQueue(c3);
        //butik.registers[1].addToQueue(c4);
        //butik.registers[2].addToQueue(c5);
        butik.registers[1].addToQueue(c6);
        butik.registers[3].addToQueue(c7);
        //butik.registers[2].addToQueue(c8);
	
        butik.newCustomer(c8);
	
        int openReg = butik.getAmountOfOpenRegisters();
        int snitt = butik.getAverageQueueLength();
        int totalRegisters = butik.getAmountOfRegisters();
	
        System.out.println("Median: " + snitt + "\nTotal registers: " + totalRegisters);
        System.out.println("Open registers: " + openReg);
	
        int closedReg = butik.getAmountOfClosedRegisters();
        System.out.println("Closed: " + closedReg);
	
        butik.openNewRegister();
        butik.newCustomer(c4);
        butik.step();
        butik.step();
        butik.getDoneCustomers();
        butik.step();
        butik.step();
        butik.step();
        butik.getDoneCustomers();
        butik.step();
        butik.step();
        butik.step();
        butik.step();
        // butik.step();
        // butik.step();
        //butik.step();
	
        closedReg = butik.getAmountOfClosedRegisters();
        System.out.println("Closed: " + closedReg);
	
        butik.registers[2].close();
	
        openReg = butik.getAmountOfOpenRegisters();
        // snitt = butik.getAverageQueueLength();
        //totalRegisters = butik.getAmountOfRegisters();
	
        System.out.println("Median: " + snitt + "\nTotal registers: " + totalRegisters);
        System.out.println("Open registers: " + openReg);
        }
    */
    
}
