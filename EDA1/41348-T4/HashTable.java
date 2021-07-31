public abstract class HashTable<AnyType> {

    public int tamanho;
    public int usadas;

    public hashElement<AnyType>[] space;

    protected abstract int acesso(AnyType s);


    public HashTable() {
        this.space = new hashElement[11];
        this.tamanho = 11;
        this.usadas = 0;
    }

    public HashTable(int tamanho) {
        this.space = new hashElement[tamanho];
        this.tamanho = tamanho;
        this.usadas = 0;
    }

    // (o número de entradas preenchidas na tabela / o tamanho do array )
    public float LoadFactor() {
        return (float) usadas / (float) tamanho;
    }

    // retorna as entradas ocupadas na hashtable.
    public int ocupada() {
        return usadas;
    }


    public void acessarTabela(int dimensão) {
        this.space = new hashElement[dimensão];
        this.tamanho = dimensão;
        this.usadas = 0;
    }

    // esvazia a hashtable
    public void tornarVazia() {
        this.space = new hashElement[tamanho];
        this.usadas = 0;
    }

    // procurar um elemento na hashtable
    // se não houver nenhuma entrada na hashtable com esse elemento retorna null
    // caso isso não se verifique retorna o elemento
    public AnyType procurar(AnyType x) {
        int proc = acesso(x);
        if (space[proc] == null || !space[proc].existe) {
            return null;
        }
        return x;
    }

    // procura-se o elemento na hashtable
    // se houver uma posição na hashtable que contenha o elmento, o elemento contido nessa posição é removido
    public void remove(AnyType x) {
        int pos = acesso(x);
        if (space[pos].element.equals(x)) {
            space[pos].remove();
        }
    }

    //o factor de carga é uma medida do quão cheia esta uma hash table até que seja preciso aumentar a sua capacidade.
    //quando essa condição é exedida é preciso que a tabela seja "rehashed".
    // Antes de se inserir, verifica-se se a tabela tem que ser "rehashed", e apenas a seguir se insere numa entrada da hashtable.
    public void insere(AnyType x) {
        float carga = LoadFactor();
        if (carga > 0.6) {
            rehash();
        }
        int alocar = acesso(x);

        space[alocar] = new hashElement<>(x);
        usadas++;
    }

    // o tamanho da hashtable(array) duplica.
    // volta-se a introduzir os elemntos que já se encontravam na tabela
    public void rehash() {
        int novoTamanho = novoTamanho(tamanho * 2);

        hashElement old[] = space;
        space = new hashElement[novoTamanho];
        tamanho = novoTamanho;
        usadas = 0;

        for (hashElement<AnyType> i : old) {
            if (i != null) {
                insere(i.element);
            }
        }
    }

// função print (imprime o conteudo da hashtable)
    public void print() {
        for (int i = 0; i < tamanho; i++) {
            if (space[i] != null) {
                if (space[i].existe) {
                    System.out.println("" + i + " : " + space[i]);
                } else {
                    System.out.println("" + i + " : " + "removed");
                }
            } else {
                System.out.println("" + i + " : " + space[i]);
            }

        }
    }


    private int novoTamanho(int tamanhoAnterior) {
        tamanhoAnterior++;

        for (int i = 2; i < tamanhoAnterior; i++) {
            if (tamanhoAnterior % i == 0) {
                tamanhoAnterior++;
                i = 2;
            } else {
                continue;
            }
        }
        return tamanhoAnterior;
    }

    // classe dos hashElements
    protected class hashElement<AnyType> {
        public AnyType element;
        public boolean existe = false;

        public hashElement(AnyType element) {
            this.element = element;
            existe = true;
        }

        //o metodo remove atribui o valor boolean false á variavel "exist"
        //fazendo com que o hashElement deixe de existir
        public void remove() {
            existe = false;
        }

// função toString
        @Override
        public String toString() {
            return element.toString();
        }
    }
}
