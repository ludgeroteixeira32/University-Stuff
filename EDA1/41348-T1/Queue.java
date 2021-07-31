public interface Queue<AnyType>{
    public void enqueue(AnyType o);
    public AnyType front();
    public AnyType dequeue();
    public int size();
    public boolean empty();
   } 