public class QuadHashTable<AnyType> extends HashTable<AnyType> {

  // aceso quadrático
 //o metodo hashCode() retorna um valor inteiro, gerado pelo algoritmo de hashing
// Este esquema de inserção na hastable, olha sempre para i^2 entrada numa interação de i, se o valor hash que se está a tentar introduzir causa uma colisão.
    @Override
    protected int acesso(AnyType s) {
        int has = s.hashCode() % tamanho;
        int inicialHas = has;

        if (has < 0) {
            inicialHas*=-1;
            has *= -1;
        }

        int i = 1;

        while (true) {
            if (space[has] == null) {
                return has;
            } else if (space[has].element.equals(s) && space[has].existe) {
                return has;
            }
            if (inicialHas + (i * i) >= tamanho) {
                has = inicialHas+(i*i);
                has=has%tamanho;

            } else {
                i++;
            }
        }


    }

}
