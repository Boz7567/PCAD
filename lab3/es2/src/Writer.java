public class Writer implements Runnable{
    private final RWexclusive rw;

    public Writer(RWexclusive rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        rw.write();
    }
}
