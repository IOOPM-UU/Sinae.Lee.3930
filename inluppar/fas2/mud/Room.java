public class Room{
    private boolean open;
    private str roomDescription;
    private str nameOfRoom;
    private Room north;
    private Room east;
    private Room south;
    private Room west;

    public LinkedList<Object> utils;
    private LinkedList<Student> students;

    public class Classroom extends Room{
        private Teacher teacher;
    }

    public Room(str roomDescription, str nameOfRoom, Room north, Room east, Room south, Room west, LinkedList<Object> utils, LinkedList<Student> students){
        this.open = false;
        this.roomDescription = roomDescription;
        this.nameOfRoom = nameOfRoom;
        this.north = north;
        this.east = east;
        this.south = south;
        this.west = west;
        this.utils = utils;
        this.students = students;

    }

    public Classroom(str roomDescription, str nameOfRoom, Room north, Room east, Room south, Room west, LinkedList<Object> utils, LinkedList<Student> students, Teacher teacher){
        super(roomDescription, nameOfRoom, north, east, south, west, utils, students);
        this.teacher = teacher;
        
    }
    
    
}
