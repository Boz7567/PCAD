public class Writer implements Runnable{
    private final RW rw;

    public Writer(RW rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        rw.write();
    }
}
