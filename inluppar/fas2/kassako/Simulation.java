import java.util.Random;

public class Simulation {
    public Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;
    private Random random;
    
    public int servedCustomers = 0;
    public int maxWaitTime = 0;
    public float averageWaitTime = 0;
    public int totalTime = 0;
    
	
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
    
    public int getServedCustomers(){
        return this.servedCustomers;
    }    
    public int getMaxWaitTime(){
        return this.maxWaitTime;
    }
    
    public float getAverageWaitTime(){
        return this.averageWaitTime;
    }
    
    
    public void calculateServedCustomers(Queue<Customer>doneCustomers)
    {
        this.servedCustomers += doneCustomers.length();
        //System.out.println("Served customers is " + this.servedCustomers);
    }
    

    
    // private void calculateMaxWaitTime(Queue<Customer> doneCustomers){
    //  Customer temp = doneCustomers.first();
    //  int servedCustomers = getServedCustomers();
    //  int served = 0; //just to check
	
    //  for(int i = 0; i < servedCustomers; ++i){
    //      int waitedTime = this.time - temp.getBornTime();
    //      System.out.print(waitedTime);
    //      if(this.maxWaitTime < waitedTime){
    //          System.out.println(" is bigger than " + maxWaitTime);
    //          this.maxWaitTime = waitedTime;
    //      }
    //      ++served;
    //      temp = temp.next;
    //  }
	
        /*for (Customer c : doneCustomers){
          int waitedTime = this.time - c.getBornTime();
          System.out.print(waitedTime);
          if(this.maxWaitTime < waitedTime){
          System.out.println(" is bigger than " + maxWaitTime);
          this.maxWaitTime = waitedTime;
          }
          ++served;
          }*/
    //  System.out.println("Total served customers is: " + servedCustomers + "but got: " + served);
    // }

    /*
private void calculateMaxWaitTime(Queue<Customer> doneCustomers){
    try{
    int servedCustomers = getServedCustomers();
    Customer temp = doneCustomers.dequeue();
    System.out.println("Customers served: " + servedCustomers);
    
    for(int i = 0; i < servedCustomers; ++i){
        int waitedTime = this.time - temp.getBornTime();
        System.out.print(waitedTime);
        if(this.maxWaitTime < waitedTime){
            System.out.println(" is bigger than " + maxWaitTime);
            this.maxWaitTime = waitedTime;
        }
        if(doneCustomers.length() == 0){
            break;
        }
        temp = doneCustomers.dequeue();
    }
    }
    catch (EmptyQueueException e){};
    System.out.println("Total served customers is: " + servedCustomers);
}
    
    
    /*	
    private void calculateAverageWaitTime(Queue<Customer> doneCustomers){
        try{
        int totalWaitTime = 0;
        int servedCustomers = getServedCustomers();
	
        Customer temp = doneCustomers.dequeue();
	
        for(int i = 0; i < servedCustomers; ++i){
            int waitedTime = this.time - temp.getBornTime();
            totalWaitTime += waitedTime;
            if(doneCustomers.length() == 0){
                break;
            }
            temp = doneCustomers.dequeue();
        }
       
        
	
        this.averageWaitTime = totalWaitTime / servedCustomers;
        System.out.println("Total wait time: " + totalWaitTime + ", Served customers: " + servedCustomers + ", Average time: " + this.averageWaitTime);
        }
        catch (EmptyQueueException e){};
    
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
            
        //calculateServedCustomers(doneCustomers);
        
        // calculateMaxWaitTime(doneCustomers);
        //calculateAverageWaitTime(doneCustomers);
	
        /*for (Customer c : doneCustomers){
          int waited = this.time - c.getBornTime();
          if (this.maxWaitTime < waited){
          this.maxWaitTime = waited;
          }
          
          this.averageWaitTime = (averageWaitTime * served + waited) / (served + 1);
          ++served;
          }*/
    }

    //  @SuppressWarnings("unchecked")
    public void step() {
        try{
        ++time;
        store.step();

        Queue<Customer> done = store.getDoneCustomers();
        measureStatistics(done);
        // System.out.println("Served customers: " + done.length());
        
        if(random.nextInt(100) < intensity) {
            store.newCustomer(new Customer(time, 1 + random.nextInt(maxGroceries)));
        }
	
        int averageQueueLenght = store.getAverageQueueLength();
        int registersClosed = store.getAmountOfClosedRegisters();
        if (registersClosed != 0 && averageQueueLenght > thresholdForNewRegister){
            store.openNewRegister();
        }
        
       
       
      
        
        }
        catch (EmptyQueueException e){};
        
    }
    

    @Override
    public String toString() {

        //int numberOfCustomersServed = getServedCustomers();
        //System.out.println("Number of customers served: " + numberOfCustomersServed);

        //int maxWaitTime = getMaxWaitTime();
        //System.out.println("Max wait-time: " + maxWaitTime);

        //float averageWaitTime = getAverageWaitTime();
        // System.out.println("Average wait-time: " + averageWaitTime);

       
        System.out.println("\nNumber of served customers: " + this.servedCustomers + "\n");
        System.out.println("\nAverage time: " + this.averageWaitTime + "\n");
        System.out.println("\nMax wait time: " + this.maxWaitTime + "\n");

        return this.store.toString();
       
    }

  
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
}
