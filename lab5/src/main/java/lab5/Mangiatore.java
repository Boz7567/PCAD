package lab5;

import java.util.concurrent.Semaphore;

public class Mangiatore implements Runnable{
    private final int id;
    private final Semaphore scatola;
    private final Semaphore empty;
    
    public Mangiatore(int id, Semaphore scatola, Semaphore empty){
        this.id = id;
        this.scatola = scatola;
        this.empty = empty;
    }

    @Override
    public void run(){
        try{
            for(int i = 0; i < 10;) {
                scatola.acquire();
                System.out.println("Mangiatore " + id + " ha mangiato un cioccolatino! (" + ++i + "/10)");
                if(scatola.availablePermits() == 0){
                    empty.tryAcquire();
                    empty.release();
                }
                Thread.sleep(1000);
            }

            System.out.println("Mangiatore " + id + " ha finito");
        }catch(Exception e){
            System.err.println(e.getMessage());
        }
    }
}
