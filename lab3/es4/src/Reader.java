public class Reader implements Runnable{
    private final RWext rw;

    public Reader(RWext rw){
        this.rw = rw;
    }

    @Override
    public void run(){
        System.out.println(rw.read());
    }
}
