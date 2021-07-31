package vacinacao;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

/*
 * SERVER CLASS
 */
public class VacinacaoServer {

	/*
	 * Main Method
	 */
    public static void main(String args[]) throws IOException 
    {
    	// read properties
    	Properties props = new Properties();
    	props.load(new FileInputStream ("resources/config.properties"));

    	try 
    	{
    		Vacinacao obj = new VacinacaoImpl(props);
	    
    		java.rmi.registry.Registry registry = java.rmi.registry.LocateRegistry.getRegistry(Integer.parseInt(props.getProperty("regPort")));

    		// bind, args: service name and remote object
    		registry.rebind("vacinacao", obj);
    		
    		System.out.println("\n Servidor pronto para receber clientes.");
    	} 
    	catch (Exception ex) 
    	{
    		ex.printStackTrace();
    	}
    }
}
