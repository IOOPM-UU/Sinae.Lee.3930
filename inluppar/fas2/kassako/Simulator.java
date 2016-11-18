public class Simulator{

    public static void main(String[] args) throws InterruptedException{

        int steps = 100;
        Customer q = new Customer(0, 3);
        
        Simulation s = new Simulation(3, 50, 5, 4); // TODO: Add parameters!

        s.store.newCustomer(q);
        for(int i = 0; i < steps; i++){
            System.out.print("\033[2J\033[;H");
            s.step();
            System.out.println(s);
            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}
