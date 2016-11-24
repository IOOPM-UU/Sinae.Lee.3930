

public class Object{
    private boolean pickup;  //pickup == true då avataren kan plocka upp den. 
    private boolean taken; //taken == true då object är i ryggsäcken..
    private int kilo;

    public class Diplom extends Object{
        private boolean exam;
        // pickup är false 
    }
    
    public class DoorKey extends Object{
        private boolean used; // true och försvinner nyckeln om man öppnat en dörr
    }

    public class Book extends Object{
        private Course course;
        private str titel;
        private str author;
        private int year;
    }
    
    public class PostIt extends Object{
        private str cheatSheet;
    }

    public Object(boolean pickup, boolean taken, int kilo){
        this.pickup = pickup;
        this.taken = taken;
        this.kilo = kilo;
    }

    public Diplom(){
        this.exam = true;
        super(false, false, 1);
    }

    public DoorKey(boolean used){
        this.used = used;
        super(true, false, 1);
    }

    public Book(int kilo, Course course, str titel, str author, int year){
        this.course = course;
        this.titel = titel;
        this.author = author;
        this.year = year;
        super(true, false, kilo);
    }

    public PostIt(str cheatSheet){
        this.cheatSheet = cheatSheet;
        super(true, false, 0);
    }
    
    public boolean getObjectPickup(){
        return this.pickup;
    }



    public int getObjectKilo(){
        return this.kilo;
    }
   
        
   
}
