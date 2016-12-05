public class Teacher extends Person{
    public Course course;

    public Teacher(String name, Course course){
        super(name);
        this.course = course;
    }

    public void setCourse(Course course){
        this.course = course;
    }

    public Course getCourse(){
        return course;
    }

    public String toString(){
        return ("Name: " + getName() + ", Course: " + getCourse().getCourseName());
    }
    
    
}
