import java.util.Iterator;

public class Agenda {

    private ABPTree<Contacto> Tree; //declarar a ABP

    public Agenda() {
        Tree = new ABPTree<>(); // inicializa a ABP
    }

    //insere o id e um contacto num nó raiz.
    //na pior das hipotes O(N), em geral O(h), em que h é a altura da árvore // h = log(N)
    public void adicionar(String id, int numb1) {
        Tree.insert(new Contacto(id, numb1));
    }

    //procura o nó iterando a árvore, de seguida remove o mesmo, atribui o "novoId" a esse nó e volta a iseri-lo
    public void editar(String id, String newID){
        Contacto edit = pesquisarId(id);
        Tree.remove(edit);
        edit.setName(newID);
        Tree.insert(edit);
    }

     //itera/percorre a árvore ate encontra o contacto com o id correspondente
     //se não houver um num2 associado ao contacto entao num2 = newNum, caso não se verifique entao num1=newNum
    public void editar(String id, int newNum){
        if(pesquisarId(id).getNumber2()== 0){
            pesquisarId(id).setNumber2(newNum);
        }else
            pesquisarId(id).setNumber1(newNum);
    }

    //itera/percorre a árvore ate encontra o contacto com o id correspondente
    //se numPretenido=1, o num1 = newNumber
    //se numPretendido=2, o num2= newNumber
    public void editar(String id, int newNum , int numPretenido){

        if (numPretenido==1){
            pesquisarId(id).setNumber1(newNum);
        }else if(numPretenido==2){
            pesquisarId(id).setNumber2(newNum);
        }

    }

    //chama o pesquisarNumero, itera a árvore até encontrar um contacto com o num correspondente, de seguida remove esse nó, e faz insert de um novo contacto
    //com o id = newId
    //na pior das hipotes O(N), em geral O(h), em que h é a altura da árvore  // h = log(N)
    public void editar(int num, String newID){
        Contacto edit = pesquisarNumero(num);
        Tree.remove(edit);
        edit.setName(newID);
        Tree.insert(edit);
    }

    //chama o pesquisarNumero(int num), econtra o objeto e de altera-o o 1º numero caso num1=num, caso contrario adiciona/altera um 2º ao contacto
    public void editar(int num, int newNum){
        Contacto edit = pesquisarNumero(num);

        if(edit.number1==num){
            edit.setNumber1(newNum);
        }else edit.setNumber2(newNum);
    }

    //percorre a árvore áte encontar um contacto em que o "id" seja igual a um nome dum contacto, se o mesmo se verificar, retorna o Contacto.
    //na pior das hipotes O(N), em geral O(h), em que h é a altura da árvore // h = log(N)
    private Contacto pesquisarId(String id){
        Iterator iterator = Tree.iterator();
        while (iterator.hasNext()) {
          Contacto procura = (Contacto) iterator.next();

            if (procura.getName().equals(id)) {
                return procura;
            }
        }

        return null;
    }

    //percorre a árvore áte encontar um contacto em que o "num" seja igual a ao num1 ou num2, se o mesmo se verificar, retorna o contacto.
    //na pior das hipotes O(N), em geral O(h), em que h é a altura da árvore // h = log(N)
    public Contacto pesquisarNumero(int num){
        Iterator iterator = Tree.iterator();
        while (iterator.hasNext()) {
          Contacto procura = (Contacto) iterator.next();
            if (procura.getNumber1() == num || procura.getNumber2() == num) {
                return procura;
            }
        }
        return null;
    }


    //percorre a árvore toda até encontrar o nome que se pretende eliminar e de seguida esse nó é removido.
    //na pior das hipotes O(N), em geral O(h), em que h é a altura da árvore // h = log(N)
    public void remover(String id) {
        Contacto procura = Tree.getRoot();
        Iterator iterator = Tree.iterator();

        while (iterator.hasNext()) {
            if (procura.getName().equals(id)) {
                Tree.remove(procura);
                return;
            }
            procura = (Contacto) iterator.next();
        }
    }

    //itera/percorre a árvore até encontrar encontrar um contacto em que num = num1 ou num = num2, de seguida remove o contacto e aponta para o próximo contacto
    //N * O(h), em que h é a altura da árvore // h = log(N)
    public void remover(int num) {
        Contacto procura = Tree.getRoot();
        Iterator iterator = Tree.iterator();
        while (iterator.hasNext()) {
            if (procura.getNumber1() == num || procura.getNumber2() == num) {
                Tree.remove(procura);
                return;
            }
            procura = (Contacto) iterator.next();
        }
    }

    //imprime a agenda
    //O(N) em que N é o número de elementos da árvore
    public void listar() {
        Tree.print();
    }

    //percorre a árvore até encontrar até encontrar um nó que corresponda as condiçoes ( mun=number1 ou num=number2)
    //de seguida imprime o nome do contacto associado ao numero, caso não encontre, no fim de iterar a lista toda imprime "Desconhecido!"
    //O(N), em que N é o numero de elementos da árvore
    public void chamador(int num) {
      Iterator iterator = Tree.iterator();
     while (iterator.hasNext()){
         Contacto procura = (Contacto) iterator.next();
         if(procura!=null && (procura.getNumber1() == num || procura.getNumber2() == num)){
             System.out.println(procura.getName());
             return;
         }
     }
     System.out.println("DESCONHECIDO");
    }

    //Class Contacto
    public static class Contacto implements Comparable<Contacto> {

        private String name;
        private int number1;
        private int number2;


        public Contacto(String name, int number1, int number2) {
            this.name = name;
            this.number1 = number1;
            this.number2 = number2;
        }

        public Contacto(String name, int number1) {
            this.name = name;
            this.number1 = number1;
            this.number2 = 0;
        }

        public String getName() {
            return name;
        }

        public int getNumber1() {
            return number1;
        }

        public int getNumber2() {
            return number2;
        }

        public void setName(String name) {
            this.name = name;
        }

        public void setNumber1(int number1) {
            this.number1 = number1;
        }

        public void setNumber2(int number2) {
            this.number2 = number2;
        }

        public String toString() {
            if (number2 == 0) {
                return name + " " + number1;
            } else {
                return name + " " + number1 + " " + number2;
            }
        }
        // Compara o nome dos contactos
        public int compareTo(Contacto o) {
            return this.name.compareTo(o.getName());
        }
    }
    // main class
    public static void main(String[] args) {
      Agenda agenda = new Agenda();

     System.out.println("----------------Agenda---------------------");
     agenda.adicionar("Ludgero", 9153506);
     agenda.adicionar("Marta", 99999);
     agenda.adicionar("Gertrudes", 11111);
     agenda.adicionar("Fernando Pessoa",010101010);               // adiciona contactos a Agenda
     agenda.adicionar("Anita",3333333);
     agenda.adicionar("José",22);
     agenda.listar();
     System.out.println("----------------Agenda Atualizada----------");
     agenda.remover("Ludgero"); // remove o contacto Ludgero pelo Id
     agenda.remover(22);
     agenda.listar();

     agenda.editar(3333333,691234); // substitui número do contacto
     agenda.editar("Marta",1); // altera o número do contacto Marta
     agenda.editar("Gertrudes",696969,2); // adiciona um 2º número ao contacto
     agenda.editar("Fernando Pessoa","Heterónimo"); // altera o ID do contacto
     agenda.remover(22);// remove o contacto José pelo número
     agenda.chamador(11111); // chamador
     agenda.chamador(787878787);// chamador desconhecido
     agenda.listar();
     System.out.println();

    }
}
