public class RWexclusive extends RWbasic{

    public RWexclusive(){
        super();
    }

    @Override
    // synchronized
    public int read(){
        return super.read();
    }

    @Override
    public void write(){
        synchronized (this) {
            super.write();
        }
    }
}
