import java.util.Random;

public class Simulation {
    private Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;
    private Random random;
    
    private int servedCustomers;
    private int maxWaitTime;
    private float averageWaitTime;
    
	
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
    
    
    private void calculateServedCustomers(Queue<Customer> doneCustomers){
        this.servedCustomers = doneCustomers.length();
        System.out.println("Served customers: " + this.servedCustomers);
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
    
private void calculateMaxWaitTime(Queue<Customer> doneCustomers){
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
    System.out.println("Total served customers is: " + servedCustomers);
}
    
    
	
    private void calculateAverageWaitTime(Queue<Customer> doneCustomers){
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
	
        /*for (Customer c : doneCustomers){
          int waitedTime = this.time - c.getBornTime();
          totalWaitTime += waitedTime;
          
          }*/
	
        this.averageWaitTime = totalWaitTime / servedCustomers;
        System.out.println("Total wait time: " + totalWaitTime + ", Served customers: " + servedCustomers + ", Average time: " + this.averageWaitTime);
    }
	
    
    private void measureStatistics(Queue<Customer> doneCustomers){
        calculateServedCustomers(doneCustomers);
        calculateMaxWaitTime(doneCustomers);
        calculateAverageWaitTime(doneCustomers);
	
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
        ++time;
        store.step();
        Queue<Customer> doneCustomers = store.getDoneCustomers();
        if(random.nextInt(100) < intensity) {
            store.newCustomer(new Customer(time, 1 + random.nextInt(maxGroceries)));
        }
	
        int averageQueueLenght = store.getAverageQueueLength();
        int registersClosed = store.getAmountOfClosedRegisters();
        if (registersClosed != 0 && averageQueueLenght > thresholdForNewRegister){
            store.openNewRegister();
        }
        if(doneCustomers.length() != 0){
            measureStatistics(doneCustomers);
        }

        toString();
        
    }
    

    
    public String toString() {

        int numberOfCustomersServed = getServedCustomers();
        System.out.println("Number of customers served: " + numberOfCustomersServed);

        int maxWaitTime = getMaxWaitTime();
        System.out.println("Max wait-time: " + maxWaitTime);

        float averageWaitTime = getAverageWaitTime();
        System.out.println("Average wait-time: " + averageWaitTime);

        return store.toString();
    }

  
    public static void main(String[] args)
    {
        Simulation simulation = new Simulation(4, 60, 5, 4);
	
        simulation.store.getTotalCustomers(); // 0 customers
	
        Customer c1 = new Customer(0, 5);
        Customer c2 = new Customer (5, 7);
        simulation.store.newCustomer(c1);
        simulation.store.newCustomer(c2);
        simulation.store.getTotalCustomers(); // 2 customers (c1 & c2)
	
	
        simulation.step(); // Queue är empty? gå till measureStatistics sen till calculateMaxWaitTime sen i Queue.java dequeue
        simulation.store.getTotalCustomers();
	
        simulation.step();
        simulation.store.getTotalCustomers();
	
        simulation.step();
        simulation.store.getTotalCustomers();
	
        // simulation.step();
        //simulation.store.getTotalCustomers();
	
        // simulation.step();
        //        simulation.store.getTotalCustomers();
	
        // simulation.step();
        // simulation.step();
        //simulation.step();
        //simulation.step();
        //simulation.step();
        // simulation.step();
        // simulation.step();
        //simulation.step();
        //simulation.step();
        // simulation.step();
        // simulation.step();


        simulation.toString();
       
	
    }
}
