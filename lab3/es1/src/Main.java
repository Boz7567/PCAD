public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        RWbasic rw = new RWbasic();
        Thread arr[] = new Thread[100];
        for (int i = 0; i < 50; i++) {
            String aux = String.valueOf(i);
            arr[i] = new Thread(new Writer(rw), "Writer: " + aux);
        }

        for(int i = 50; i<100; i++){
            String aux = String.valueOf(i);
            arr[i] = new Thread(new Reader(rw), "Reader: " + aux);
        }

        for(var t : arr){
            t.start();
        }

        for(var t : arr){
            t.join();
        }

        System.out.println("Final data value: " + rw.read());
    }
}
