public class Writer implements Runnable{
    private final RWext rw;

    public Writer(RWext rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        rw.write();
    }
}
