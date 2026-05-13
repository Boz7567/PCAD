import java.util.concurrent.Semaphore;

public class PoolDeadlock {
    private final static int NumberClosets= 1; //numero armadietti
    private final static int NumberLockers= 1; //numero spogliatoi
    
    private final static Semaphore Lockers= new Semaphore(NumberLockers);
    private final static Semaphore Closets= new Semaphore(NumberClosets);

    public static class Cliente extends Thread{
        private final int id;
        
        public Cliente(int id){
           this.id=id;
        }

        @Override
        public void run(){
            try {
                System.out.println("Cliente " + id + " arrivato in piscina.");
                Lockers.acquire();
                System.out.println("Cliente " + id + " ha preso lo spogliatoio.");
                Closets.acquire();
                System.out.println("Cliente " + id + " ha preso l'armadietto.");
                System.out.println("Cliente " + id + " si sta cambiando...");
                Thread.sleep(100);
                Lockers.release();
                System.out.println("Cliente " + id + "si è cambiato e ha liberato lo spogliatoio");
                System.out.println("Cliente " + id + "sta nuotando");
                Thread.sleep(100);
                Lockers.acquire();
                System.out.println("Cliente " + id + " ha ripreso lo spogliatoio.");
                System.out.println("Cliente " + id + " si sta rivestendo.");
                Thread.sleep(100);
                Lockers.release();
                Closets.release();
                System.out.println("Cliente " + id + " e' andato via.");
            } catch (InterruptedException e) {e.printStackTrace();}
        }
    }
    public static void main(String[] args) {
        int numeroClienti = 2;
        for (int i = 1; i <= numeroClienti; i++) {
            new Cliente(i).start();
        }
    }
}
