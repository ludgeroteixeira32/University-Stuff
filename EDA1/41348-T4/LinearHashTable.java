public class LinearHashTable<AnyType> extends HashTable<AnyType> {


 //o metodo hashCode() retorna um valor inteiro, gerado pelo algoritmo de hashing.
// Este esquema de inserção na hashtable, vai iterar linearmente até encontar uma entrada vazia quando a inserção de um hash value causa uma colisão.
    @Override
    protected int acesso(AnyType s) {
        int has = s.hashCode() % tamanho;

        if (has < 0) {
            has *= -1;
        }

        while (true) {
            if (space[has] == null) {
                return has;
            } else if (space[has].element.equals(s) && space[has].existe) {
                return has;
            }
            if (has + 1 == tamanho) {
                has = 0;
            } else {
                has++;
            }
        }

    }

}
