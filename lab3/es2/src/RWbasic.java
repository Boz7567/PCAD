public class RWbasic{
    private int data;
    
    public RWbasic(){
        data = 0;
    }

    public int read(){
        return data;
    }

    public void write(){
            int tmp = data;
            try{
                Thread.sleep(1);
            }
            catch (InterruptedException e){
                e.printStackTrace();
            }
            tmp++;
            data = tmp;
    }
}