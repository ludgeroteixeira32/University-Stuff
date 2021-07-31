import java.io.*;
import java.util.Scanner;

public class Corrector {

    public static void main(String[] args) {
        HashTable<String> dicionario = new LinearHashTable<>();
        dicionario.acessarTabela(1400000);
        System.out.println("------------------------Corretor Ortográfico---------------------------");
        //Dicionário - > Lê as palavras 1 a 1 e insere na Hashtable
        try {
            File file = new File("wordlist-big-20201212.txt");
            if (file.exists()){
            }
            BufferedReader LeitorDicionario = new BufferedReader(new FileReader(file));

            String palavraDicionario;
            while ((palavraDicionario = LeitorDicionario.readLine()) != null){
                dicionario.insere(palavraDicionario);


            }
            LeitorDicionario.close();

        } catch (FileNotFoundException e) {
            System.out.println("Não foi detectado um dicionário.");
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }



        try {
            File file2 = new File("text.txt");
            BufferedReader LeitorTexto = new BufferedReader(new FileReader(file2));     // Lê o input do ficheiro (text.txt)

            String linha;
            int NumeroDaLinha = 0;
            while ((linha = LeitorTexto.readLine()) != null) {
                NumeroDaLinha++;
                Scanner all = new Scanner(linha);
                while (all.hasNext()) {
                    String palavra = all.next();
                    StringBuffer opcoes;
                    String[] alfabeto = {"a", "b", "c", "d", "e", "f", "g", "h", "i",
                            "j", "k", "l", "m", "n", "o", "p",
                            "q", "r", "s", "t", "u", "v", "w",
                            "x", "y", "z", "ç", "á", "à", "â",
                            "é", "è", "ê", "í", "Í", "î", "ó",
                            "N", "O", "P", "Q", "R", "T", "U",
                            "V", "X", "Z", "Y", "W", "ò", "ô",
                            "ú", "ù", "E", "A", "B", "C", "D",
                            "F", "G", "H", "I", "J", "K", "L" , "-"};

                    if (dicionario.procurar(palavra) == null) {
                        for (int i = 0; i < alfabeto.length; i++) {
                            for (int x = 0; x <= palavra.length(); x++) {        // inserir uma letra
                                opcoes = new StringBuffer(palavra);
                                opcoes.insert(x, alfabeto[i]);

                                if (dicionario.procurar(opcoes.toString()) != null) {
                                    System.out.println(" |linha:" + NumeroDaLinha + " palavra: " + linha + "   sugestão --> " + opcoes);

                                }
                            }
                        }
                        for (int x = 0; x < palavra.length(); x++) {
                            opcoes = new StringBuffer(palavra);
                            opcoes.deleteCharAt(x);                              // remover uma letra

                            if (dicionario.procurar(opcoes.toString()) != null) {
                                System.out.println(" |linha:" + NumeroDaLinha +  " palavra: " + linha + "  sugestão --> " + opcoes);

                            }
                        }
                        for (int x = 0; x < palavra.length(); x++) {
                            for (int y = 0; y < palavra.length(); y++) {
                                opcoes = new StringBuffer(trocar(palavra, x, y));      // trocar duas letras consecutivas

                                if (dicionario.procurar(opcoes.toString()) != null) {
                                    System.out.println(" |linha:" + NumeroDaLinha +  " palavra: " + linha + "  sugestão --> " + opcoes);

                                }
                            }
                        }

                    }
                }
                all.close();
            }
            LeitorTexto.close();

        } catch (FileNotFoundException e) {
            System.out.println("Não foi detectado nenhum ficheiro de texto.");
        } catch (java.io.IOException e) {

        }


    }

    // método trocar
    //
    static String trocar(String str, int value1, int value2) {
        char[] novaPalavra = str.toCharArray();
        char valortemporario = novaPalavra[value1];
        novaPalavra[value1] = novaPalavra[value2];
        novaPalavra[value2] = valortemporario;
        return String.valueOf(novaPalavra);
    }
}
