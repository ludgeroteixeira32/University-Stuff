public class QueueArray<Anytype> implements Queue<Anytype> {
    private Anytype[] queue;
    int N;
    int ini = 0;
    int fim = 0;

    public QueueArray(int size){
      queue = (Anytype[]) new Object[size]; N = size;
     }

    public void enqueue(Anytype o) {
        if(this.size()+1 < N) {
            queue[fim] = o;
            fim = inc(fim);
        }else
            System.out.println("Full Queue!");

    }

    public int inc(int i){
        return (i+1) % N;
    }

    public Anytype front() {
        return queue[ini];
    }

    public Anytype dequeue(){
        if(!this.empty()) {
            Anytype x = queue[ini];
            queue[ini] = null;
            ini = inc(ini);
            return x;
        }else {
            System.out.println("Empty Queue!");
            return null;
        }
    }

    public int size() {
        return (N-ini+fim) % N;
    }

    public boolean empty() {
        return ini == fim;
    }

    public String toString(){
      if (empty()){
        return "[]";
      }

      String result = " [";

      for (int i = ini; i != fim; i = inc(i)){
        result += "" + queue[i]+";";
      }

      return result + "]";

    }


}
