package vacinacao;

import java.util.List;

/*
 * Remote Interface for the service
 */
public interface Vacinacao extends java.rmi.Remote {

   	public List<String> Consulta_Centros() throws java.rmi.RemoteException, Exception;

   	public int Consulta_Fila_de_Espera(String centro) throws java.rmi.RemoteException, Exception;
   	
   	public int Inscricao(String centro, String nome, String genero, String idade) throws java.rmi.RemoteException, Exception;
   	
	public int Registo(int codigox, String vacina, String data) throws java.rmi.RemoteException, Exception;
	
	public void Reportar(int codigoc) throws java.rmi.RemoteException, Exception;
	
	public int NumEfeitosSecundarios(String vacina) throws java.rmi.RemoteException, Exception;
	
	public int NumVacinados(String vacina) throws java.rmi.RemoteException, Exception;
}

