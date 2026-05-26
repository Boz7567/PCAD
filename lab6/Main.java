package lab6;

public class Main {

    public static void main(String[] args) {

        Negozio n = new Negozio();

        Thread babbo = new Thread(new Babbo(n));
        babbo.start();

        // renne
        for (int i = 1; i <= n.N_RENNE; i++) {

            Thread r = new Thread(new Renne(i, n));
            r.start();
        }

        // elfi
        for (int i = 1; i <= n.N_ELFI; i++) {

            Thread e = new Thread(new Elfi(i, n));
            e.start();
        }
    }
}