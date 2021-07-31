/**
 * Represents a group of people
 */
public class BusData{
  private int horas;
  private int minutos;
  private int pessoas;

  public BusData(int h, int m, int p){
    horas = h;
    minutos = m;
    pessoas = p;
  }

  public int getHoras() {
    return horas;
  }

  public int getMinutos() {
    return minutos;
  }

  public int getPessoas() {
    return pessoas;
  }

  public void setPessoas(int pessoas) {
    this.pessoas = pessoas;
  }

  public String toString(){
    return (  " "+ horas+":"+minutos+" Grupo de "+pessoas+" pessoas ");
  }


}
