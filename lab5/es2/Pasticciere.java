class Pasticciere extends Thread {
    private final ScatolaCioccolatini scatola;

    public Pasticciere(ScatolaCioccolatini s) { this.scatola = s; }

    @Override
    public void run() {
        try {
            for(int i=0; i<9; ++i) {
                scatola.Riempi();
                Thread.sleep(2000); // Tempo per preparare i cioccolatini
            }
        } catch (InterruptedException e) { e.printStackTrace(); }
    }
}

class Mangiatore extends Thread {
    private final int id;
    private final ScatolaCioccolatini scatola;

    public Mangiatore(int id, ScatolaCioccolatini s) {
        this.id = id;
        this.scatola = s;
    }
    @Override
    public void run() {
        try {
            for(int i=0; i<15; ++i) {
                scatola.Prendi(id);
                Thread.sleep(1000); // Tempo per mangiare
            }
        } catch (InterruptedException e) { e.printStackTrace(); }
    }
}
