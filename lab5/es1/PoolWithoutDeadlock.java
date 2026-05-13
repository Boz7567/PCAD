import java.util.concurrent.Semaphore;

public class PoolWithoutDeadlock {
    private static int NumberClosets= 1; //numero armadietti
    private static int NumberLockers= 1; //numero spogliatoi
    
    private static Semaphore Lockers= new Semaphore(NumberLockers);
    private static Semaphore Closets= new Semaphore(NumberClosets);

    public static class Cliente extends Thread{
        private int id;
        
        public Cliente(int id){
           this.id=id;
        }
        public void run(){
            try {
                System.out.println("Cliente " + id + " tenta di prendere l'armadietto.");
                Closets.acquire();
                System.out.println("Cliente " + id + " tenta di prendere lo spogliatoio.");
                Lockers.acquire();
                System.out.println("Cliente " + id + " si sta cambiando...");
                Thread.sleep(100);
                Lockers.release();
                System.out.println("Cliente " + id + " si è cambiato e ha liberato lo spogliatoio");
                System.out.println("Cliente " + id + " sta nuotando");
                Thread.sleep(100);
                System.out.println("Cliente " + id + " vuole uscire, attende SPOGLIATOIO...");
                Lockers.acquire();
                System.out.println("Cliente " + id + " si sta rivestendo.");
                Thread.sleep(100);
                Lockers.release();
                Closets.release();
                System.out.println("Cliente " + id + " e' andato via.");
            } catch (InterruptedException e) {e.printStackTrace();}
        }
    }
    public static void main(String[] args) {
        int numeroClienti = 3;
        System.out.println("Simulazione Piscina (Versione Anti-Deadlock)");
        for (int i = 1; i <= numeroClienti; i++) {
            new Cliente(i).start();
        }
    }
}
