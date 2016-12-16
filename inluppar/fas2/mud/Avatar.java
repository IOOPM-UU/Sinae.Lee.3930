import java.util.ArrayList;

public class Avatar extends Person{
    private int hp;  
    private String name;
    private ArrayList<Utils> backpack;;
    
    private ArrayList<Course> unfinishedCourses;
    private ArrayList<Course> finishedCourses;
    private Room current;

    private Avatar(String name, ArrayList<Course> takenCourses, Room room, Book book){
        this.name = name;
        hp = 60;
        backpack = new Backpack<Utils>();
        finishedCourses = takenCourses;
        unfinishedCourses = new ArrayList<Course>();
        this.room = current;
    }

    public void getBackPack(){
        for(int i = 0; i < 10; ++i){
            Utils current = backpack[i];
            // System.out.println(i+1 +". " + current)
        }
        
    }

    // pick up an util and adds it to the backpack
    public boolean pickUp(String name){
        Utils util = getRoom().
    }


    public void talkTo(String name){
        
    }
        
    
}
