public class Writer implements Runnable{
    private final RWbasic rw;

    public Writer(RWbasic rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        rw.write();
    }
}
