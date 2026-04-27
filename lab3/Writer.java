public class Writer implements Runnable {
    private RWbasic risorsa;

    public Writer(RWbasic risorsa) {
        this.risorsa = risorsa;
    }

    @Override
    public void run() {
        // Facciamo 5 incrementi per thread per vedere il numero salire
        for (int i = 0; i < 5; i++) {
            risorsa.write();
        }
    }
}
