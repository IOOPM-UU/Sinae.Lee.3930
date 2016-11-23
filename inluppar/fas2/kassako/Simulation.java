import java.util.Random;

public class Simulation {
    public Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;
    private Random random;
    
    private int servedCustomers = 0;
    private int maxWaitTime = 0;
    private float averageWaitTime = 0;
    private int totalTime = 0;
    
	
    public Simulation(int amountOfRegisters, int intensity,
                      int maxGroceries, int thresholdForNewRegister){
		
        if (amountOfRegisters < 1){
            throw new IllegalArgumentException("Have to have atleast 1 register");
        }
	
        if (intensity < 1 || intensity > 100){
            throw new IllegalArgumentException("Intensity should be in range 1-100");
        }
	
        if (maxGroceries < 1){
            throw new IllegalArgumentException("Max groceries need to be more than 0");
        }
	
        if (thresholdForNewRegister < 1){
            throw new IllegalArgumentException("Threshold need to be bigger than 0");
        }
		
        this.store = new Store(amountOfRegisters);
        this.time = 0;
        this.intensity = intensity;
        this.maxGroceries = maxGroceries;
        this.thresholdForNewRegister = thresholdForNewRegister;
        this.random = new Random();
	
        this.servedCustomers = 0;
        this.maxWaitTime = 0;
        this.averageWaitTime = 0;
    }

    /**
     * This method is used to return the sum of served customers.
     *
     * @return int the sum of served customers.
     */
    public int getServedCustomers(){
        return this.servedCustomers;
    }


    /**
     * This method is used to return the maxium waiting time.
     *
     * @return int the maximum waiting time
     */
    public int getMaxWaitTime(){
        return this.maxWaitTime;
    }

    /**
     * This method is used to return the average waiting time.
     *
     * @return float the average waiting time
     */
    public float getAverageWaitTime(){
        return this.averageWaitTime;
    }
    
    /**
     * This method is used to calculate the sum of served customers
     *
     * @param doneCustomers a collection of served customers
     */
    public void calculateServedCustomers(Queue<Customer>doneCustomers)
    {
        this.servedCustomers += doneCustomers.length();
    }
    
    /**
     * This method is used to calculate the statistics that indicates average waiting time.
     * 
     * @param doneCustomers a collection of served customers
     */
    public void measureStatistics(Queue<Customer> doneCustomers){
        
       
        
        if(!doneCustomers.isEmpty()){
            int len = doneCustomers.length();
           
            this.servedCustomers += len;
            while(len > 0){
                Customer c = doneCustomers.dequeue();
                int wait = this.time - c.getBornTime();
                this.totalTime += wait;
                if(this.maxWaitTime < wait){
                    this.maxWaitTime = wait;
                }
                len -- ;
            }
            this.averageWaitTime = (float)this.totalTime / this.servedCustomers;
        
           
        }
            
        
    }

    /**
     * This method is used to reduce 
     */

    public void step()
    {
        try
            {
                ++time;
                store.step();

                Queue<Customer> done = store.getDoneCustomers();
                measureStatistics(done);
                
                if(random.nextInt(100) < intensity)
                    {
                        store.newCustomer(new Customer(time, 1 + random.nextInt(maxGroceries)));
                    }
	
                int averageQueueLenght = store.getAverageQueueLength();
                int registersClosed = store.getAmountOfClosedRegisters();
                if (registersClosed != 0 && averageQueueLenght > thresholdForNewRegister)
                    {
                        store.openNewRegister();
                    }
        
            }

        catch (EmptyQueueException e){};
        
    }
    
    /**
     * This method is used to represent the condition of store and the statistics.
     *
     * @return a string that textually represents the condition and the statistics.
     */
    @Override
    public String toString()
    {
       
        System.out.println("\nNumber of served customers: " + this.servedCustomers + "\n");
        System.out.println("\nAverage time: " + this.averageWaitTime + "\n");
        System.out.println("\nMax wait time: " + this.maxWaitTime + "\n");
        
        return this.store.toString();
       
       
    }

    /*
    public static void main(String[] args)
    {
        Simulation simulation = new Simulation(4, 60, 5, 4);
       
	Customer c1 = new Customer(0, 5);
        Customer c2 = new Customer (5, 7);
        simulation.store.newCustomer(c1);
        simulation.store.newCustomer(c2);
        simulation.store.getTotalCustomers(); // 2 customers (c1 & c2)
	
	for(int i = 0; i<100; ++i)
            {
                simulation.step();
                try
                    {
                        Thread.sleep(1000);
                    }
                catch(InterruptedException e){}
            }
    }
    */
}
