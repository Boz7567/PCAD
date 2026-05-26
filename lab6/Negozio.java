package lab6;

import java.util.concurrent.Semaphore;

public class Negozio{
    public static final int N_RENNE = 9;
    public static final int N_ELFI = 5;
    public static final int MAX_ELFI = 3;

    private int count_renne;
    private int count_elfi;

    private Semaphore mutex = new Semaphore(1);
    private Semaphore babbSem = new Semaphore(0);
    private Semaphore elfiSem = new Semaphore(0);
    private Semaphore renneSem = new Semaphore(0);
    private Semaphore maxElfiSem = new Semaphore(MAX_ELFI);

    // FIX Bug 1: metodi sincronizzati per leggere i contatori in modo sicuro
    public synchronized boolean tutteLeRenneTornate() {
        return count_renne == N_RENNE;
    }

    public synchronized boolean elfiInAttesa() {
        return count_elfi == MAX_ELFI;
    }

    //babbo
    public void Nanna() throws InterruptedException{
        babbSem.acquire();
    }

    public void Slitta() throws InterruptedException{
        System.out.println("Babbo fa il giro con la slitta.");
        mutex.acquire();
        count_renne = 0;
        mutex.release();
        for (int i=0; i<N_RENNE; i++){
            renneSem.release();
        }
    }

    public void Aiuta() throws InterruptedException{
        System.out.println("Babbo aiuta gli elfi");
        for(int i=0; i<MAX_ELFI; i++){
            elfiSem.release();
        }
    }

    //renne
    public void FineVacanza(int id) throws InterruptedException{
        mutex.acquire();
        count_renne++;
        System.out.println("Renna "+id+" tornata dalle vacanze. ("+count_renne+"/"+N_RENNE+")");
        if(count_renne == N_RENNE){
            System.out.println("ultima renna tornata.");
            babbSem.release();
        }
        mutex.release();
        renneSem.acquire();
        System.out.println("Renna "+id+" in viaggio con babbo.");
    }

    //elfi
    public void ChiedoAiuto(int id) throws InterruptedException{
        maxElfiSem.acquire();
        mutex.acquire();
        count_elfi++;
        System.out.println("Elfo "+id+" chiede aiuto. ("+count_elfi+"/"+MAX_ELFI+")");
        if(count_elfi == MAX_ELFI){
            System.out.println("terzo elfo sveglia babbo.");
            babbSem.release();
        }
        mutex.release();
        elfiSem.acquire();
        System.out.println("Elfo "+id+" riceve aiuto da babbo.");
        mutex.acquire();
        count_elfi--;
        maxElfiSem.release();
        mutex.release();
    }
}