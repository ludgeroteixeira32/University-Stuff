package madpanda.madpanda.OrderFiles;

import java.util.List;

import org.springframework.data.repository.CrudRepository;

public interface OrderRepository extends CrudRepository<Order, Long> {

    Order findById(long id);
    Order findOneByUsername(String username);
    List<Order> findAllByUsername(String username);
}
