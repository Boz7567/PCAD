public class MainMiky {
    public static void main(String[] args) throws InterruptedException {

        RWbasic risorsa = new RW();

        int numWriters = 50;
        int numReaders = 50;

        Thread[] writers = new Thread[numWriters];
        Thread[] readers = new Thread[numReaders];

        for (int i = 0; i < numWriters; i++) {
            writers[i] = new Thread(new Writer(risorsa), "Writer-" + i);
        }

        for (int i = 0; i < numReaders; i++) {
            readers[i] = new Thread(new Reader(risorsa), "Reader-" + i);
        }

        for (int i = 0; i < numWriters; i++) {
            writers[i].start();
        }

        for (int i = 0; i < numReaders; i++) {
            readers[i].start();
        }

        for (int i = 0; i < numWriters; i++) {
            writers[i].join();
        }

        for (int i = 0; i < numReaders; i++) {
            readers[i].join();
        }


        int valoreFinale = risorsa.read();
        System.out.println("Valore finale di data: " + valoreFinale);
        System.out.println("Valore atteso (senza errori): " + numWriters);
    }
}
