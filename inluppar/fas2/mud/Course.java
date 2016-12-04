public class Course{
    public String name;
    private int hp;
    private Book book;
    //  private Question question;  // not yet implemented

    public Course(String name, Book book, int hp){
        this.name = name;
        this.book = book;
        this.hp = hp;
    }

    /*  
    public Question getQuestion(){
        return question;
    }
    */

    /*
    public void setQuestion(Question question){
        this.question = question;
    }
    */

    public String getCourseName(){
        return name;
    }

    public Book getBook(){
        return book;
    }

    public int getHp(){
        return hp;
    }

    public String toString(){
        return ("Course name: " + getCourseName() + ", Book: " + getBook().getName() + ", Hp: " + getHp());
    }


    public static void main(String[] args){
        Book b1 = new Book("Building Lego is easy peasy", "Marie Paulsson", 2016, 3);
        Course c1 = new Course("How to build Lego", b1, 20);

        System.out.println(c1.toString());
    }
}


