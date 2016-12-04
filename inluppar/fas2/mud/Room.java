import java.util.ArrayList;
    
public class Room{
    private boolean open;
    private String roomDescription;
    private String nameOfRoom;
    //  private Sfinx sfinx;
    private Room north;
    private Room east;
    private Room south;
    private Room west;
    private boolean isClassRoom;
    //  public Teacher teacher;
    
    public ArrayList<Utils> utils;
    private ArrayList<Student> students;

   

    public Room(String roomDescription, String nameOfRoom, ArrayList<Utils> utils){
        this.open = false;
        this.isClassRoom = false;
        //  this.teacher = null;
        this.roomDescription = roomDescription;
        this.nameOfRoom = nameOfRoom;
        this.utils = utils;
        // this.sfinx = null;
    }

    /*
    public void setSfinx(Sfinx sfinx){
        this.sfinx = sfinx;
    }
    */
    
    public void addUtils(Utils u){
        utils.add(u);
    }

    
    public void addStudent (Student s){
        students.add(s);
    }

    public Utils getItem(String name){
        for (Utils util: utils){
            String s = util.getName();
            if (s.equals(name)){
                return util;
            }
        }

        System.out.println(name + " is not here.");
        return null;
    }

   

    
    
}
