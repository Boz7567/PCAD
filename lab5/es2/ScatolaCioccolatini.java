

public class ScatolaCioccolatini {
    private int cioccolatini=0;
    private int capacity;;       //uso la variabile P per indicare la capienza della scatola       
    
    public ScatolaCioccolatini(int capacity){
        this.capacity=capacity;       
    }
    public synchronized void Riempi()throws InterruptedException{
        while(cioccolatini>0){
            System.out.println("Pasticciere: La ScatolaCioccolatini non è ancora vuota. Attendo...");
            wait();
        }
        cioccolatini=capacity;
        System.out.println("Pasticciere: ScatolaCioccolatini riempita con " + capacity + " cioccolatini.");
        notifyAll();
    }
    public synchronized void Prendi(int idMangiatore) throws InterruptedException{
        while(cioccolatini==0){
            System.out.println("Mangiatore " + idMangiatore + ": ScatolaCioccolatini vuota. Aspetto...");
            wait();
        }
        cioccolatini--;
        System.out.println("Mangiatore " + idMangiatore + ": Ho preso un cioccolatino. Rimasti: " + cioccolatini);
        if (cioccolatini == 0) {
            notifyAll(); 
        }

    }

}
