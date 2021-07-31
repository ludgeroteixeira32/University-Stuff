package madpanda.madpanda.ClientFiles;

import java.util.List;
import org.springframework.data.repository.CrudRepository;

public interface ClientRepository extends CrudRepository<Client, Long> {

	List<Client> findByUsername(String username);

	Client findById(long id);
	Client findOneByUsername(String username);
}
