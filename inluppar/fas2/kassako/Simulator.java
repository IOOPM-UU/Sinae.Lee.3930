public class Simulator{

    public static void main(String[] args) throws InterruptedException{

        int steps = 10;
        int amountOfRegisters = 10;
        int intensity = 1;
        int maxGroceries = 50;
        int thresholdForNewRegister = 50;
        
        Simulation s = new Simulation(amountOfRegisters, intensity, maxGroceries, thresholdForNewRegister); // TODO: Add parameters!
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
