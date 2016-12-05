public class Student extends Person{
    public Course finishedCourse;
    public Course currentCourse;
    public Book book;

    public Student(String name, Course finished, Course current, Book book){
        super(name);
        this.finishedCourse = finished;
        this.currentCourse = current;
        this.book = book;
    }

    public Course getFinishedCourse(){
        return finishedCourse;
    }

    public Course getCurrentCourse(){
        return currentCourse;
    }

    public void setFinishedCourse(Course finished){
        this.finishedCourse = finished;
    }

    public void setCurrentCourse(Course current){
        this.currentCourse = current;
    }

    
}
