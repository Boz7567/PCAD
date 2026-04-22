public class Reader implements Runnable{
    private final RWbasic rw;

    public Reader(RWbasic rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        System.out.println(rw.read());
    }
}
