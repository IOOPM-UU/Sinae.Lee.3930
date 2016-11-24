public class Person{
    private str name;
    private Room room;
    
    public class Teacher extends Person{
        private Course course;
        private Room room;
        private Question question;
    }

    public class Student extends Person{
        private Book exchange;
        private Course enrolled;
        private Course cleaned;
        private str answer;
    }

    public Person(str name, Room room){
        this.name = name;
        this.room = room;
    }

    public Teacher(str name, Room room, Course course, Question question){
        super(name, room);
        this.course = course;
        this.question = question;
        
    }

    public Student(str name, Room room, Book exchange, Course enrolled, Course cleaned, str answer){
        super(name, room);
        this.exchange = exchange;
        this.enrolled = enrolled;
        this.cleaned = cleaned;
        this.answer = answer;
    }
    
}
