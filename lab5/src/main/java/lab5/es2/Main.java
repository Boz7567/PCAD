package lab5.es2;

import java.util.concurrent.Semaphore;

public class Main{
    private static final int N_MANGIATORI = 3;
    private static Semaphore scatola;
    private static Semaphore empty;
    public static void main(String[] args) {
        try{
            scatola = new Semaphore(0);
            empty = new Semaphore(1);
            Thread[] mangiatori = new Thread[N_MANGIATORI];
            Thread temp = new Thread(new Pasticciere(scatola, empty));
            temp.start();
            for(int i = 0; i<N_MANGIATORI; i++){
                mangiatori[i] = new Thread(new Mangiatore(i, scatola, empty));
            }
            for(Thread t : mangiatori){
                t.start();
            }
            for(Thread t : mangiatori){
                t.join();
            }
            temp.interrupt();
            temp.join();
        }
        catch(Exception e){
            System.err.println(e.getMessage());
        }

    }
}