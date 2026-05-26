package lab6;

public class Babbo implements Runnable{

    private Negozio n;
    
    public Babbo(Negozio n){
        this.n = n;
    }

    @Override
    public void run(){

        try {
            while(true){ 
                System.out.println("Babbo dorme.");
                n.Nanna();
                if(n.tutteLeRenneTornate()){
                    n.Slitta();
                    Thread.sleep(5000);
                    System.out.println("Babbo torna dal viaggio con le renne.");
                }
                else if(n.elfiInAttesa()){
                    n.Aiuta();
                    Thread.sleep(3000);
                    System.out.println("Babbo ha finito di aiutare gli elfi.");
                }
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
        
    }
}