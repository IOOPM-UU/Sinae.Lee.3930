public class Person{
    private String name;
    private Room current;

    public Person(String name){
        this.name = name;
    }

    public String getName(){
        return name;
    }

    public Room getRoom(){
        return current;
    }

    /**
     * Moves the person to a new room
     */
    
    public void goToRoom(Room room){
        current = room;
    }

    public String toString(){
        return ("Name: " + getName());
    }
}
