package lab6;

public class Renne implements Runnable{
    private int id;
    private Negozio n;

    public Renne(int id, Negozio n){
        this.id = id;
        this.n = n;
    }

    @Override
    public void run(){

        try{
            while(true){
                System.out.println("Renna "+id+" in vacanza.");
                long vacanza = 5000 + (long)(Math.random() * 10000);
                Thread.sleep(vacanza);
                n.FineVacanza(id);
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}

