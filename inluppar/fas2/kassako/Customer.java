/** 
 * The Customer program implements an appication that 
 * create a customer with number of goods and
 * time-step that the customer came in the system
 * and reduce the number of goods. 
 *
 * @author Sinae Lee
 * @author Marie Paulsson
 * @version 1.0
 * @since  2016-11-20
 */

public class Customer{
    
    private int bornTime;    
    public int groceries;
    
    public Customer (int bornTime, int groceries){
        
        this.bornTime = bornTime;
        this.groceries = groceries;
    }

/**
 * This method is used to get number of goods.
 * 
 * @return int This returns current number of goods.
 */

    public int getGroceries(){
       
        return groceries;
    }

/**
 * This method is used to get the time-step that a customer came in the system.
 *
 * @return int the time-step.
 */
    public int getBornTime(){
       
        return bornTime;
    }

/**
 * This method is used to get the boolean value that 
 * indicates if customer has 0 goods.
 *
 * @return boolean true or false.
 */    
    public boolean isDone(){
        
        if (groceries == 0){
                return true;
            }

        else{
                return false;
            }
    }
    
 /**
  * This method is used to reduce number of goods with interval -1.
  */
    public void serve(){
       
        if(groceries > 0){
                --groceries;
            }
        
    }

/**
 * This method is used to represent number of goods.
 *
 * @return a string that "textually represents" number of goods.
 */    
   @Override
   public String toString(){
       
        return "[" + groceries + "]";
    }
   

}  
