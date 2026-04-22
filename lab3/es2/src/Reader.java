public class Reader implements Runnable{
    private final RWexclusive rw;

    public Reader(RWexclusive rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        System.out.println(rw.read());
    }
}
