import java.util.Random;

public class Question{
    private Course course;
    private String[] answer;
    private int index;
    private String question;

    public Question(Course course, String question, String[] answer, int index){
        this.question = question;
        this.answer = answer;
        this.index = index;
    }

    
}
