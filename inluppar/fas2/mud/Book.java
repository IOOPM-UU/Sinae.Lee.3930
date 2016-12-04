public class Book extends Utils{
        private String author;
        private int year;

    public Book(String title, String author, int year, int liter){
            super(title, liter);
            this.author = author;
            this.year = year;
        }

    
    public String toString(){
        return (getName() + ", " + this.author + ", " + this.year + ", " + getLiter());
    }

        public static void main(String[] args){
            Book b1 = new Book("hello", "Jan", 1981, 2);

            System.out.println(b1.toString());
           

        }
}

        
