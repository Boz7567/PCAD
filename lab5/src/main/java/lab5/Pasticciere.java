package lab5;

import java.util.concurrent.Semaphore;

public class Pasticciere implements Runnable{
    private static final int P = 5;
    private final Semaphore scatola;
    private final Semaphore empty;

    public Pasticciere(Semaphore scatola, Semaphore empty){
        this.scatola = scatola;
        this.empty = empty;
    }

    @Override
    public void run() {
        try{
            while(true){
                empty.acquire();
                scatola.release(P);
                System.out.println("Pasticciere ha riempito la scatola!");
            }
        }
        catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }
    }
}
