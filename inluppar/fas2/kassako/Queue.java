

public class Queue
{
    private Node first;
    private Node last;
    private int length;

    private class Node
    {
        private Customer element;
        private Node next;

        public Node (Customer element, Node next)
        {
            this.element = element;
            this.next = next;
        }
    }

    public int length() {return length;}

    // empty queue. constructor
    public Queue()
    {
        first = last = null;
        length = 0;
    }
    
    // is this queue empty?
    public boolean isEmpty()
    {
        if (first == null)
            {
                return true;
            }

        else
            {
                return false;
            }
    }

    //public Customer getElement() {return element;}
    
    public void enqueue(Customer element)
    {
        Node temp = new Node(element, null);

        if (last != null)
            {
                last.next = temp;
                last = temp;
            }

        else
            {
                first = last = temp;
            }

        length++;

        System.out.println("adding: " + element);
    }

    
    // ta bort (och returnera) kunden som står först i kön
    //public Customer dequeue()
    // {
    //  if (isEmpty()) throw new NoSuchElementException ("The queue is empty");
    //   Customer element = first.element;
    //  first = first.next;
    //  length--;
        
        
    //}

    //public Customer first()
    // {
    //  if (first != null)
    //      {
    //          return first.getElement();
    //      }

    //  else
    //      {
    //          System.out.println("There is no first.");
    //      }
    // }
        
    public static void main(String [] args)
    {
        Customer c1 = new Customer (2, 5);
        Customer c2 = new Customer (5, 7);
        Customer c3 = new Customer (1, 9);
        Customer c4 = new Customer (0, 10);

        Queue q = new Queue();

        q.enqueue(c1);
        q.enqueue(c2);
        q.enqueue(c3);
        q.enqueue(c4);

       
        
        int size = q.length();
        System.out.println("length: " + size);
    }
    
    
   
}
