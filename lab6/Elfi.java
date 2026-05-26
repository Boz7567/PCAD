package lab6;

public class Elfi implements Runnable{
    private int id;
    private Negozio n;

    public Elfi(int id, Negozio n){
        this.id = id;
        this.n = n;
    }

    @Override
    public void run(){

        try{
            while(true){
                System.out.println("Elfo "+id+" lavora ai giocattoli.");
                Thread.sleep(1000);
                n.ChiedoAiuto(id);
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}

