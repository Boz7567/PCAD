package lab5.es1;

import java.util.concurrent.Semaphore;

public class Pool {
    private static final int N_CLIENTS = 100;
    private static final int N_ROOMS   = 4;
    private static final int N_LOCKERS = 2;
    public static void main(String[] args) {
        try{
            Semaphore rooms = new Semaphore(N_ROOMS);
            Semaphore lockers = new Semaphore(N_LOCKERS);

            Thread threads[] = new Thread[N_CLIENTS];


            for(int i = 0; i<N_CLIENTS; i++){
                threads[i] = new Thread(new ClientSafe(i, rooms, lockers));
            }

            for(Thread t : threads){
                t.start();
            }

            for(Thread t : threads){
                t.join();
            }
        }
        catch(Exception e){
            System.err.println(e.getMessage());
        }
    }
}