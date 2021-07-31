import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {

        int numberOfRooms, numberOfCorridors, payment, entrance = 0, exit = 0,k = 0, l = 0;
        int corridor[][];
        String input;
        String[] inputOrganized;
        String[] details;

        BufferedReader ler = new BufferedReader(new InputStreamReader(System.in));
        input = ler.readLine();
        inputOrganized = input.split(" ");

        numberOfRooms = Integer.parseInt(inputOrganized[0]);
        numberOfCorridors = Integer.parseInt(inputOrganized[1]);


        //Cria a matriz com o espaço necessario para o input
        corridor = new int[numberOfCorridors][];
        payment = 0;

        for (int x = 0; x < numberOfCorridors; x++) {
            input = ler.readLine();
            details = input.split(" ");

            //Verifica se o caminho inserido vai ter um valor negativo ou posito
            if (details[2].equals("C")) {
                payment = Integer.parseInt(details[3]) * -1;
            } else if (details[2].equals("B")) {
                payment = Integer.parseInt(details[3]);
            }
            corridor[x] = new int[]{Integer.parseInt(details[0]), Integer.parseInt(details[1]), payment};

            //Guarda o primeiro valor do index em que se encontra a entrada e a saida
            if (Integer.parseInt(details[0])==0 && k!=1){
                entrance=x;
                k=1;
            }else if (Integer.parseInt(details[1])==numberOfRooms-1 && l!=1){
                exit=x;
                l=1;
            }
        }

        MazyLuck mazyluck = new MazyLuck(corridor, numberOfRooms, numberOfCorridors, entrance, exit);

        //Verifica se o Dirk pode perder dinheiro ou nao
        if (mazyluck.Algorithm() < 0){
            System.out.println("yes");
        } else {
            System.out.println("no");
        }
    }
}
