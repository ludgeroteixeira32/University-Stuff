package vacinacao;

import java.rmi.server.UnicastRemoteObject;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Properties;

/*
 * REMOTE OBJECT CLASS,
 * Implementation of the services operations.
 */
public class VacinacaoImpl extends UnicastRemoteObject implements Vacinacao, java.io.Serializable 
{
	private PostgresConnector pc;
	private int codeX;
	private int codeC;
	
    // VacinacaoImpl Constructor
    public VacinacaoImpl(Properties props) throws Exception 
    {
        super();
    	pc = new PostgresConnector(props.getProperty("regHost"), props.getProperty("DBName"), props.getProperty("DBUser"), props.getProperty("DBPassword"));
    	this.codeX = NextCodeX(pc);
        this.codeC = NextCodeC(pc);
    }

    /* Implementation of each method declared in the remote interface */

    /* 
     * Returns a vector with the names of the vaccination centers
     */
	public java.util.List<String> Consulta_Centros() throws java.rmi.RemoteException, Exception
	{
        // connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        java.util.LinkedList<String> centros = new java.util.LinkedList<>();

        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT NomeCentro FROM centros");

        	while (rs.next()) 
                    centros.add(rs.getString("NomeCentro"));
        	
        	rs.close();                
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
    
        return centros;
    }
	
	/*
	 *  Returns the number of the people waiting in a vaccination center
	 */
	public int Consulta_Fila_de_Espera(String centro) throws java.rmi.RemoteException, Exception
	{
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        int num = 0;

        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT COUNT(NomePessoa) AS total FROM fila_de_espera WHERE NomeCentro = '"+centro+"'");

        	while (rs.next()) 
        		num=rs.getInt("total");
        	
        	rs.close();                
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return num;
    }
	
	/*
	 *  Returns the code X and subscribes a person to a vaccination center
	 */
	public int Inscricao(String centro, String nome, String genero, String idade) throws java.rmi.RemoteException, Exception
	{			
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        codeX++;
        
        // execute update query	
        try 
        {
        	stmt.executeUpdate("INSERT INTO fila_de_espera VALUES ('" + centro + "', '" + nome + "', "+ idade +", '"+genero+"', "+codeX+");");
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return codeX;
    }
	
	/*
	 *  Returns the code C and registered a person as vaccinated
	 */
	public int Registo(int codigox, String vacina, String data) throws java.rmi.RemoteException, Exception
	{			
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        codeC++;
        
        // execute the update queries
        try 
        {
        	stmt.executeUpdate("DELETE FROM fila_de_espera WHERE CodigoX = "+codigox+";");
        	stmt.executeUpdate("INSERT INTO vacinados VALUES ('" + vacina + "', '" + data + "', 'Nao', "+codeC+");");
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return codeC;
    }
	
	/*
	 *  Reports a person with secondary effects
	 */
	public void Reportar(int codigoc) throws java.rmi.RemoteException, Exception
	{
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        
        // execute update query	
        try 
        {
        	stmt.executeUpdate("UPDATE vacinados SET EfeitosSecundarios = 'Sim' WHERE CodigoC = "+codigoc+";");
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
    }
	
	/*
	 *  Returns the number of people with secondary effects for a vaccine
	 */
	public int NumEfeitosSecundarios(String vacina) throws java.rmi.RemoteException, Exception
	{
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        int efeitosSecundarios = 0;
        
        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT COUNT(CodigoC) AS efeitosSecundarios FROM vacinados WHERE (EfeitosSecundarios = 'Sim' AND TipoVacina = '"+vacina+"');");

        	while (rs.next()) 
        		efeitosSecundarios=rs.getInt("efeitosSecundarios");
        
        	rs.close(); 
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return efeitosSecundarios;
    }
	
	/*
	 *  Returns the number of people that have taken a vaccine
	 */
	public int NumVacinados(String vacina) throws java.rmi.RemoteException, Exception
	{
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        int numVacinados = 0;
        
        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT COUNT(CodigoC) AS vacinados FROM vacinados WHERE TipoVacina = '"+vacina+"'"+";");

        	while (rs.next()) 
        		numVacinados=rs.getInt("vacinados");
        	
        	rs.close();    
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return numVacinados;
    }
	
	/*
	 *  Returns the next code X to be used
	 */
	public static int NextCodeX(PostgresConnector pc) throws Exception 
    {   
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        int codeX = 0;
        
        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT MAX(CodigoX) AS nextX FROM fila_de_espera;");

        	if (rs != null)
        		while (rs.next()) 
        			codeX=rs.getInt("nextX");
        	
        	rs.close();    
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return codeX;
    } 
	
	/*
	 *  Returns the next code X to be used
	 */
	public static int NextCodeC(PostgresConnector pc) throws Exception 
    {   
		// connection with the SGBD
        pc.connect();
        Statement stmt = pc.getStatement();
        int codeC = 0;
        
        // execute consult query	
        try 
        {
        	ResultSet rs = stmt.executeQuery("SELECT MAX(CodigoC) AS nextC FROM vacinados;");

        	if (rs != null)
        		while (rs.next()) 
        			codeC=rs.getInt("nextC");
        	
        	rs.close();    
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
            System.err.println("Problems retrieving data from db...");
        }

        // SGBD disconnection
        pc.disconnect();
        
        return codeC;
    } 
	
}

