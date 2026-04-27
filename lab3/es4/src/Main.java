// per provare ad assicurarmi che ogni valore sia letto da almeno un lettore 
// utilizzo un numero estremamente grande di reader, perchè se uso lo stesso numero, più lettori leggono lo stesso valore
// e i reader terminano prima di aver scritto tutti i valori
// provando diversi numeri di reader, mi sono reso conto che con 450 reader e 50 writer il rischio che il programma 
// non termini è minimizzato


public class Main {
    final static int arrSize = 500;
    public static void main(String[] args) throws Exception {
        System.out.println("This is es4");
        RWext rw = new RWext();
        Thread arr[] = new Thread[arrSize];
        for (int i = 0; i < 50; i++) {
            String aux = String.valueOf(i);
            arr[i] = new Thread(new Writer(rw), "Writer: " + aux);
        }

        for(int i = 50; i<arrSize; i++){
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
