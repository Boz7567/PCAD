public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("This is es4");
        RWext rw = new RWext();
        int n = 100; // numero di reader
        Thread[] arr = new Thread[n * 3];
        for (int i = 0; i < n*2; i++) {
            arr[i] = new Thread(new Writer(rw), "Writer-" + i);
        }
        for (int i = 0; i < n; i++) {
            arr[n + i] = new Thread(new Reader(rw), "Reader-" + i);
        }
        for (Thread t : arr) t.start();
        for (Thread t : arr) t.join();
        System.out.println("Final data value: " + rw.read());
    }
}