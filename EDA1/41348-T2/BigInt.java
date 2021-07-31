public class BigInt implements AstroInt{

  private DoubleLinkedList<Integer> T ; // declaração da doublelinkelist
  private int tamanho; // tamanho da String
  private boolean sinal = false; // se true sinal = "-" , se false sinal = "+"

  //BigInt construtor
  public BigInt (String number){
    T = new DoubleLinkedList<>(); // inicialização da DLL
    this.tamanho = number.length();

    if(isInt(number)){
      if(number.charAt(0)== '-'){
        number = number.substring(1);
        sinal = true;

      }
      else{
        sinal = false;

      }
      for(int i =number.length()-1; i >= 0;i--){
        T.add(Character.getNumericValue(number.charAt(i)));
      }

    }
    else{
      System.out.println("Error: Introduza um numero inteiro");
    }
  }

  // função add
  @Override
  public AstroInt add(AstroInt x){
    BigInt auxiliar = new BigInt(x.toString());
    StringBuilder s = new StringBuilder();
      int resto = 0;
      int resultado;
      int max = 0;
      int numero1; int numero2;
      BigInt a = (BigInt) x ;

      if(this.tamanho>=a.tamanho){
         max = this.tamanho;

      }else{
         max = a.tamanho;
      }
      if(getSinal() == auxiliar.getSinal()){

        for(int i = 1; i<=max;i++){

          if(this.T.size()<i){

            numero1=0;
          }
          else{

            numero1 = this.T.get(i);
          }
          if(a.T.size()<i){

            numero2=0;
          }
          else{

            numero2 = a.T.get(i);
          }
          resultado = (numero1+numero2 + resto ) % 10;
          resto = (numero1+numero2+resto)/10;
          s.append(resultado);

        }
        if(resto>0){
          s.append(resto);

        }
        if(getSinal()){
          s.reverse();
          s.append('-');
          s.reverse();
        }


      }
    return new BigInt(s.toString());
  }

  //função sub
  @Override
  public AstroInt sub(AstroInt x){
    BigInt auxiliar = new BigInt(x.toString());
    StringBuilder s = new StringBuilder();
      int resto = 0;
      int resultado;
      int max = 0;
      int numero1; int numero2;
      BigInt a = (BigInt) x ;

      if(this.tamanho>=a.tamanho){
         max = this.tamanho;

      }else{
         max = a.tamanho;
      }
      if(getSinal() == auxiliar.getSinal()){

        for(int i = 1; i<=max;i++){

          if(this.T.size()<i){

            numero1=0;
          }
          else{

            numero1 = this.T.get(i);
          }
          if(a.T.size()<i){

            numero2=0;
          }
          else{

            numero2 = a.T.get(i);
          }
          resultado = (numero1+numero2 + resto ) % 10;
          resto = (numero1+numero2+resto)/10;
          s.append(resultado);

        }
        if(resto>0){
          s.append(resto);

        }
        if(getSinal()){
          s.reverse();
          s.append('-');
          s.reverse();
        }


      }
    return new BigInt(s.toString());

  }




  //função mult
  @Override
  public AstroInt mult(AstroInt x){
    return null;

  }


  //Função div
  @Override
  public AstroInt div(AstroInt x){
    return null;

  }

  //função mod
  @Override
  public AstroInt mod(AstroInt x){
    return null;

  }

  // função toString
  @Override
  public String toString(){
    StringBuilder b = new StringBuilder();
    if(sinal){
      b.append('-');
    }
    for(int i = 1; i<=T.size(); i++){
      b.append(T.get(i));
    }
    return b.toString();


  }

  //Retorna o valor de sinal
  public boolean getSinal(){
    return sinal;
  }

  // Retorna T
  public DoubleLinkedList<Integer> getnumero(){
    return T;
  }

  //Compara o tamanho das Strings
  public static int StringCompare(String a, String b){
    String e = a;
    String r = b;

    while(e.length()<r.length()) e = "0" + e;
    while(e.length()>r.length()) r = "0" + r;
    return e.compareTo(r);


  }

  // função para verificar se o input é um número
  public boolean isInt(String s){
    char[] c = s.toCharArray();
    boolean a = true;
    int i = 0;

    if (c[0]=='-'){
      ++i;
    }
    for(;i<c.length;i++){
      if(!Character.isDigit(c[i])){
      a = false;
      break;
      }
    }
    return a;
  }

  // função main para correr os inputs
  public static void main (String[] args){
    BigInt a = new BigInt("-1000000000");
    BigInt b = new BigInt("-9999999999999999999999999");
    System.out.println(a.add(b));
    System.out.println(a.sub(b));
    //System.out.println(a.mult(b));
    //System.out.println(a.div(b));
    //System.out.println(a.mod(b));
  }

}
