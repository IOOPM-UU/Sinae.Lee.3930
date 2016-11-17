public class Store{
    private Register registers[];
    
    public Store(int amountOfRegisters){
        if (amountOfRegisters > 0){
            this.registers = new Register[amountOfRegisters];
            for(int i = 0; i < amountOfRegisters; ++i){
                this.registers[i] = new Register();
            }
            this.registers[0].open();
        }
    }
    
    //methods
    
    public int getAmountOfOpenRegisters(){
        int totalOpenRegisters = 0;
        for (Register r : this.registers){
            if(r.isOpen()){
                ++totalOpenRegisters;
            }
        }
        return totalOpenRegisters;
    }
    
    public int getAmountOfRegisters(){
        int totalRegisters = 0;
        for (Register r : this.registers){
            ++totalRegisters;
        }
        return totalRegisters;
    }
    
    public int getAmountOfClosedRegisters(){
        return (getAmountOfRegisters() - getAmountOfOpenRegisters());
    }
    
    public int getAverageQueueLength(){
        int totalCustomers = 0;
        // int openRegisters = 0; //just to check
        int amountOfOpenRegisters = getAmountOfOpenRegisters();
	
        for (Register r : this.registers){
            if (r.isOpen()){
                totalCustomers += r.queue.length();
                //++openRegisters;
            }
        }
		
        // System.out.println("amount of open registers: " + amountOfOpenRegisters + " and you got: " + openRegisters);
		
        return totalCustomers/amountOfOpenRegisters;
    }
    
    public void newCustomer(Customer c){
        int i = 0;
        int shortest = this.registers[i].queue.length();
        int totalRegisters = getAmountOfRegisters();
	
        for(int j = 1; j < totalRegisters; ++j){
            if(this.registers[j].isOpen()){
                if(this.registers[j].queue.length() < shortest){
                    shortest = this.registers[j].queue.length();
                    i = j;
                    
                }
            }
        }
        //System.out.println("Register " + i + " has the shortest queue. Lenght: "+ shortest);
        this.registers[i].addToQueue(c);
    }
    
    public void step(){
        try
            {
                for(Register r: this.registers){
                    if(r.isOpen()){
                        r.step();
                        int groc = r.queue.first().getGroceries();
                    }

                 
                }

                getDoneCustomers();
                toString();
            }
        
        catch (EmptyQueueException e) {};
    }
	
    public void openNewRegister(){
        int amountOfRegisters = getAmountOfRegisters();
		
        for(int i = 0; i < amountOfRegisters; ++i){
            if(!this.registers[i].isOpen()){
                this.registers[i].open();
                break;
            }
        }
    }
	
    public Queue<Customer> getDoneCustomers(){
        Queue<Customer> doneCustomers = new Queue<Customer>();
        for(Register r : this.registers){
            if(r.isOpen() && r.currentCustomerIsDone()){
                doneCustomers.enqueue(r.removeCurrentCustomer());
            }
        }
        return doneCustomers;
    } 


    public int getTotalCustomers(){
        int totCustomers = 0;
        for(Register r : this.registers){
            totCustomers += r.queue.length();
        }
        System.out.println("Total customers is: " + totCustomers);
        return totCustomers;
    }

    public String toString()
    {
        String s = "\n";
        for (Register r : this.registers)
            {
                s = s + r.toString();
            }

        // System.out.println(s);
        return s;
    }
    
    public static void main(String[] args)
    {
        Customer c1 = new Customer(2, 5); // kassa 0
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9); // kassa 1
        Customer c4 = new Customer (0, 10); // kassa 2
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
        butik.step();
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

        // butik.toString();
    }
    
}
