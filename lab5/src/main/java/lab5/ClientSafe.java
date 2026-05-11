package lab5;

import java.util.concurrent.Semaphore;

public class ClientSafe implements Runnable{
    private final int id;
    private final Semaphore rooms;
    private final Semaphore lockers;
    
    public ClientSafe(int id, Semaphore rooms, Semaphore lockers){
        this.id = id;
        this.rooms = rooms;
        this.lockers = lockers;
    }

    // Modifica
    // Facendo in modo che il cliente prenda la chiave del locker prima di quella dello spogliatoio evitiamo deadlock
    @Override
    public void run(){
        try {
            lockers.acquire();
            System.out.println("Client " + id + " took a locker key\n");
            rooms.acquire();
            System.out.println("Client " + id + " took a room key\n");
            Thread.sleep(100); //Si cambia, Libera lo spogliatoio, mette i suoi vestiti nell'armadietto
            rooms.release();
            System.out.println("Client " + id + " released a room key\n");
            System.out.println("Client " + id + " starts swimming\n");
            Thread.sleep(300); //Nuota
            System.out.println("Client " + id + " finished swimming\n");
            rooms.acquire();
            System.out.println("Client " + id + " took a room key\n");
            Thread.sleep(100); //Recupera i vestiti nell'armadietto, si riveste, libera lo spogliatoio
            rooms.release();
            System.out.println("Client " + id + " released a room key\n");
            lockers.release();
            System.out.println("Client " + id + " released a locker key\n");
            System.out.println("Client " + id + " finished!\n");
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}
