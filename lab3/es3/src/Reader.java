public class Reader implements Runnable{
    private final RW rw;

    public Reader(RW rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        System.out.println(rw.read());
    }
}
