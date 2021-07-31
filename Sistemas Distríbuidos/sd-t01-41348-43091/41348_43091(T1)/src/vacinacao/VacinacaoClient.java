package vacinacao;
 
import java.io.FileInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.List;
import java.util.Properties;

/*
 * CLIENT CLASS
 */
public class VacinacaoClient 
{
	private String regHost;
	private String regPort;
	private Vacinacao obj;

	/*
	 * Client Constructor
	 */
	public VacinacaoClient(Properties props) throws RemoteException, MalformedURLException, NotBoundException 
	{
		this.regHost = props.getProperty("regHost");
		this.regPort = props.getProperty("regPort");
		this.obj = createObject();
	}
	 
	/*
	 * Main Method
	 */
	public static void main(String[] args) throws IOException 
	{	
		boolean sair = false;
    	int lidos = 0;
        byte[] b = new byte[256];
        
        // get properties
		Properties props = new Properties();
    	props.load(new FileInputStream ("resources/config.properties"));
    	
		try 
		{
			// create client
			VacinacaoClient cl = new VacinacaoClient(props);
			
			while (!sair) 
    	    {  
				// show menu to the client
    	    	cl.printMenu();
    	    	
                // do option
                sair = cl.executeOption(cl.readInput(lidos, b), lidos, b);
    	    }
		} 
		catch (Exception e) 
		{
	            e.printStackTrace();
	    }
	}
    
    /*
     * Print all menu options
     */
    public void printMenu()
    {
    	System.out.print("\n\n ---------- MENU ---------- \n"
                + " consultar centros        - consultar centros de vacinacao\n\n"
                + " consultar fila           - consultar fila de espera de um centro\n\n"
                + " inscricao                - inscrição para vacinação num dos centros\n\n"
                + " registo                  - registar a realização de vacinação\n\n"
                + " reportar                 - reportar existência de efeitos secundários para um cidadão\n\n"
                + " listar                   - listar nº total de vacinados e nº de casos com efeitos secundários por tipo de vacina.\n\n"
                + " sair                     - sair do sistema\n\n	> ");
    }
    
    /*
     * Object that gets associate to the proxy for the remote object
     */
    public Vacinacao createObject() throws RemoteException, NotBoundException, MalformedURLException
    {
    	return (Vacinacao) java.rmi.Naming.lookup("rmi://"+ regHost +":"+regPort +"/vacinacao");
    }
    
    /*
     * Execute option chosen
     */
    public boolean executeOption(String op, int lidos, byte b[]) throws RemoteException, Exception
    {
    	if (op.equals("sair")) 
            return true;
    	
        else if (op.equals("consultar centros")) 
        	consultarCentros();
    	
        else if (op.equals("consultar fila")) 
        	consultarFiladeEspera(lidos, b);
    	
        else if (op.equals("inscricao")) 
        	inscricao(lidos, b);
    	
        else if (op.equals("registo")) 
        	registo(lidos, b);
    	
        else if (op.equals("reportar")) 
        	reportar(lidos, b);
    	
        else if (op.equals("listar")) 
        	listar(lidos, b);
        else 
        	 System.out.println("\n Opcao Invalida");   
    	
    	return false;
    }
    
    /*
     * Read client input
     */
    public String readInput(int lidos, byte b[]) throws IOException
    {
        lidos = System.in.read(b, 0, 256);
        return new String(b, 0, lidos - 1);
    }
    
    /*
     * Option: consultarCentros
     */
    public void consultarCentros() throws RemoteException, Exception
    {
    	List<String> v = obj.Consulta_Centros();
	    System.out.println("\n Centros de Vacinacao:");

	    for (int i=0; i<v.size();i++) 
	    	System.out.println("\n	> "+v.get(i));
    }
    
    /*
     * Option: consultarFiladeEspera
     */
    public void consultarFiladeEspera(int lidos, byte b[]) throws RemoteException, Exception
    {
    	System.out.print("\n Centro: ");
     	int v = obj.Consulta_Fila_de_Espera(readInput(lidos, b));
     	
 	    System.out.println("\n Numero de pessoas na fila de espera: "+ v);
    }
    
    /*
     * Option: inscricao
     */
    public void inscricao(int lidos, byte b[]) throws RemoteException, Exception
    {
    	 System.out.print("\n Centro: ");
         String centro = readInput(lidos, b);

         System.out.print("\n Nome: ");
         String nome = readInput(lidos, b);
         
         System.out.print("\n Genero: ");
         String genero = readInput(lidos, b);
         
         System.out.print("\n Idade: ");
         String idade = readInput(lidos, b);
     	
     	int codigox = obj.Inscricao(centro,nome,genero,idade);
 	    System.out.println("\n O seu pedido foi realizado com sucesso.\n O seu codigo de inscricao: "+ codigox);
    }
    
    /*
     * Option: registo
     */
    public void registo(int lidos, byte b[]) throws RemoteException, Exception
    {
    	System.out.print("\n Codigo X: ");
        String c = readInput(lidos, b);
        
        System.out.print("\n Tipo de Vacina: ");
        String vacina = readInput(lidos, b);
        
        System.out.print("\n Data (dia/mes/ano): ");
        String data = readInput(lidos, b);
    	
    	int codigoc= obj.Registo(Integer.parseInt(c),vacina,data) ;
	    System.out.println("\n O seu pedido foi realizado com sucesso.\nO seu codigo de vacinacao: "+ codigoc);
    }
    
    /*
     * Option: reportar
     */
    public void reportar(int lidos, byte b[]) throws RemoteException, Exception
    {
    	 System.out.print("\n Codigo C: ");
         String c = readInput(lidos, b);
     	
     	obj.Reportar(Integer.parseInt(c)) ;
 	    System.out.println("\n O seu pedido foi realizado com sucesso.");
    }
    
    /*
     * Option: listar
     */
    public void listar(int lidos, byte b[]) throws RemoteException, Exception
    {
    	System.out.print("\n Tipo de Vacina: ");
        String vacina = readInput(lidos, b);
    	
    	int numEfeitosSecundarios = obj.NumEfeitosSecundarios(vacina);
    	int numVacinados = obj.NumVacinados(vacina);
    	
	    System.out.println("\n O numero total de vacinados foi "+numVacinados+".\n "+numEfeitosSecundarios+" pessoas tiveram efeitos secundarios.");
    }
}
