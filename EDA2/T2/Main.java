import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static void main(String[] args) throws IOException {
        int numberOfTask;
        int numberOfPrecedences;
        int limit;
        String input;
        String[] inputOrganized;
        String[] details;

        BufferedReader ler = new BufferedReader(new InputStreamReader(System.in));
        input = ler.readLine();
        inputOrganized = input.split(" ");

        numberOfTask = Integer.parseInt(inputOrganized[0]);
        numberOfPrecedences = Integer.parseInt(inputOrganized[1]);
        limit = Integer.parseInt(inputOrganized[2]);

        HardWeek hardWeek= new HardWeek(numberOfTask);

        for (int x = 0; x < numberOfPrecedences; x++) {
            input = ler.readLine();
            details = input.split(" ");
            hardWeek.insertPrecedences(Integer.parseInt(details[0]), Integer.parseInt(details[1]));//inserção de ligações
        }
        hardWeek.start(limit);
    }
}
