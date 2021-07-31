/**
 * Represents the Bus Stop
 */
public class BusStop{
  QueueArray<BusData> fila;
  private int npessoas = 0;
  public BusStop(int size){
    fila = new QueueArray<>(size);
  }

  // adiciona o grupo de pessoas que chegaram à fila.
  // caso já se encontrem pessoas na fila, o grupo de pessoas na fila acresce.
  public void chega_grupo(int h, int m, int n){
    npessoas += n;
    BusData grupo = new BusData(h, m, n);
    fila.enqueue(grupo);
    System.out.println(" Hora "+" "+h+":"+m+"  "+n+ " pessoas chegam, ficam "+ npessoas + "  na fila");
  }

  //adiciona-se o número de pessoas que está na fila à frente a "BusData", tendo em conta as vagas no bus.
  //Se as pessoas que estiverem a espera na fila forem menos ou igual às vagas no autocarro ficam 0 a espera e de seguida sutrai-se essas pessoas á fila.
  //Caso contrário entram só o número de pessoas equivalente ás vagas no bus,de seguida subtrai-se essas mesmas a fila.
  //contadordegrupos conta o numero de grupos que chegam a fila
  //contadorhoras é um somatorio de todas as horas a que os grupos chegam a fila.
  public void chegada_bus(int h, int m, int n){
    int contadordegrupos = 0;
    int contadordehoras = 0;
    System.out.println(" Chega o Bus -> " + h + ":" + m + " e existem " + n + " vagas no autocarro");
    while(fila.front()!= null && n>0 && fila.size()>0){
      contadordegrupos = contadordegrupos+1;
      contadordehoras += (h-fila.front().getHoras())*60 + m - fila.front().getMinutos();
      BusData grupo = fila.front();
      if(grupo.getPessoas()<=n){
        System.out.println(" hora " + fila.front().getHoras() +":" + fila.front().getMinutos()+ " Chegaram "+ fila.front().getPessoas()+ " ficam 0");
        fila.dequeue();
        n-= grupo.getPessoas();
      } else{
        System.out.println(" hora " + fila.front().getHoras() +":" + fila.front().getMinutos()+ " Chegaram "+ fila.front().getPessoas()+ " ficam "+ (grupo.getPessoas()-n));
        fila.front().setPessoas(grupo.getPessoas()-n);
        n = 0;
      }
    }
    System.out.println(" Tempo médio de espera : "  + contadordehoras/contadordegrupos + " minutos");
  }

  // main para correr os inputs
  public static void main(String[] args){
    BusStop b23=new BusStop(10);
    b23.chega_grupo( 14,14,3 );
    b23.chega_grupo( 14,18 ,2);
    System.out.println(b23.fila);
    b23.chegada_bus( 14,29,4 );
    b23.chegada_bus( 14,40,10 );
}
}
