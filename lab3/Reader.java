public class Reader implements Runnable {
    private RWbasic risorsa;

    public Reader(RWbasic risorsa) {
        this.risorsa = risorsa;
    }

    @Override
    public void run() {
        try { 
            Thread.sleep(5); 
        } catch (InterruptedException e) {}
        
        int val = risorsa.read();
        System.out.println("Letto: " + val);
    }
}
