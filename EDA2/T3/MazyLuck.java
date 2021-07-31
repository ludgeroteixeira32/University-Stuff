class MazyLuck {

    private final int corridor[][];
    private int numberOfRooms, numberOfCorridors, entrance, exit;

    public MazyLuck(int[][] corridor, int numberOfRooms, int numberOfCorridors, int entrance, int exit) {
        this.numberOfRooms = numberOfRooms;
        this.numberOfCorridors = numberOfCorridors;
        this.corridor = corridor;
        this.entrance = entrance;
        this.exit = exit;
    }

    public int Algorithm(){

        //Cria um array para o gold possivel para cada ponto e coloca o seu valor ao maximo possivel para fazer cada comparacao
        int[] gold = new int[numberOfRooms];
        for (int i = 0; i < numberOfRooms; i++){
            gold[i] = 5000001;
        }

        //Troca a ordem do ponto de entrada para o index 0 e troca a ordem do ponto de saida para o ultimo index
        int save[]=corridor[0];
        corridor[0]=corridor[entrance];
        corridor[entrance]=save;

        if(exit==0){
            exit=entrance;
        }

        save=corridor[numberOfRooms-1];
        corridor[numberOfRooms-1]=corridor[exit];
        corridor[exit]=save;

        exit=numberOfRooms-1;
        entrance=0;
        gold[entrance] = 0;

        //Verifica se o gold que esta guardado naquele corredor vai ser menor ao efetuar a soma do proximo corredor se sim guarda-o
        for (int i = 0; i < numberOfRooms - 1; i++){
            for (int j = 0; j < numberOfCorridors; j++){
                if (gold[corridor[j][0]] != 5000001 && gold[corridor[j][0]] + corridor[j][2] < gold[corridor[j][1]]){
                    gold[corridor[j][1]] = gold[corridor[j][0]] + corridor[j][2];
                }
            }
        }

        //Verifica se extiste algum loop negativo de gold o que possibilita sempre a perda do mesmo
        for (int i = 0; i < numberOfCorridors; i++){
            int x = corridor[i][0];
            int y = corridor[i][1];
            int pay = corridor[i][2];
            if (gold[x] != 5000001 && gold[x] + pay < gold[y]){
                return -1;
            }
        }
        return gold[exit];
    }
}
