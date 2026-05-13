public class Cioccolatini{
    public static void main(String[] args) {
        int P = 5;
        ScatolaCioccolatini scatola = new ScatolaCioccolatini(P);

        // Creazione processi
        Pasticciere p = new Pasticciere(scatola);
        Mangiatore m1 = new Mangiatore(1, scatola);
        Mangiatore m2 = new Mangiatore(2, scatola);
        Mangiatore m3 = new Mangiatore(3, scatola);

        // Avvio thread
        p.start();
        m1.start();
        m2.start();
        m3.start();
    }
}
