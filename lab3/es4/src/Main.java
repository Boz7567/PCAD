// per provare ad assicurarmi che ogni valore sia letto da almeno un lettore 
// utilizzo un numero estremamente grande di reader, perchè se uso lo stesso numero, più lettori leggono lo stesso valore
// e i reader terminano prima di aver scritto tutti i valori


public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("This is es4");
        RWext rw = new RWext();
        Thread arr[] = new Thread[500];
        for (int i = 0; i < 50; i++) {
            String aux = String.valueOf(i);
            arr[i] = new Thread(new Writer(rw), "Writer: " + aux);
        }

        for(int i = 50; i<500; i++){
            String aux = String.valueOf(i);
            arr[i] = new Thread(new Reader(rw), "Reader: " + aux);
        }

        for(var t : arr){
            t.start();
        }

        for(var t : arr){
            t.join();
        }

        System.out.println("Final value: " + rw.read());
    }
}
