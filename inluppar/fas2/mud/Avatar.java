import java.util.LinkedList;

public class Avatar{
    private int hp;   // börjar från 60 hp
    private LinkedList<Object> backpack;
    private int liter;   //max 10 liter
    private Course unfinished[];
    private Course finished[];
    private Room current; //current location

    private Avatar(){
        hp = 60;
        this.backpack = new LinkedList<Object>();
        liter = 0;
        unfinished[] = null;
        finished[] = null;  // change to 6
        current = null;
    }

    public int getHp(){
        return this.hp;
    }

    public void getBackPack(){
        for(int i = 0; i < 10; ++i){
            Object current = backpack[i];
            // System.out.println(i+1 +". " + current)
        }
        
    }

    public boolean pickUp(Object o){

        if (o.getObjectPickup == true){
            int check = liter + o.getObjectKilo;

            if (check > 10){
                System.out.println("Your backpack is full");
                return false;
            }

            if (check <= 10){
                this.backpack.add(o);
                liter += o.getObjectKilo;
                return true;
            }
                
        }

        else{System.out.println("You can't pick it up"); return false;}
    }
    
}
