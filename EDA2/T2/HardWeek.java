import java.util.*;
import java.util.ArrayList;

class HardWeek {

    private final ArrayList<ArrayList<Integer>> adj;
    private final int[] cost;
    private final Queue<Integer> wait;

    //Constructor
    public HardWeek(int numberOfTask) {
        this.adj = new ArrayList<>(numberOfTask);
        this.cost = new int[numberOfTask];
        this.wait = new LinkedList<>();

        //Storing space for the number of tasks
        for (int i = 0; i < numberOfTask; i++) {
            adj.add(new ArrayList<>());
        }
    }

    //Counting how many joints has each node
    public void insertPrecedences(int t1, int t2) {
        adj.get(t1).add(t2);
        cost[t2]+= 1;
    }

    //Checking if ended or not
    public boolean end(int[] cost){
        for (int i=0; i < cost.length; i++ ){
            if (cost[i]!=-1){
                return false;
            }
        }
        return true;
    }

    public void start(int limit) {
        int ntask = 0;
        int nhardWeek = 0;
        int taskMax = 0;
        while (!end(cost)){
            //Check the tasks that can be done and set its value to -1
            for (int i = 0; i < cost.length; i++) {
                if (cost[i] == 0) {
                    wait.add(i);
                    cost[i] = -1;
                }
            }

            //Count the tasks that are on the queue and check if its the max number of tasks that can be done on one week
            ntask = wait.size();
            if (ntask > limit){
                nhardWeek += 1;
            }
            if (ntask > taskMax){
                taskMax = ntask;
            }

            //Check the node on the head of the queue and subtract 1 on the number of joints of the next nodes that are related to the one on the head
            while (wait.size() != 0) {
            
                for (int j = 0; j < adj.get(wait.peek()).size(); j++) {
                    int noCost = adj.get(wait.peek()).get(j);
                    cost[noCost]+=-1;
                }
                wait.remove();
            }
        }
        System.out.println(taskMax + " " + nhardWeek);
    }
}


