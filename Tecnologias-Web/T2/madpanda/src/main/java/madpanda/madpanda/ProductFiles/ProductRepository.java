package madpanda.madpanda.ProductFiles;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import java.util.List;
import java.util.Optional;

public interface ProductRepository extends CrudRepository<Product, Long> {
    List<Product> findByName(String name);

    Optional<Product> findById(@Param("id") Long id);

    @Query(value = "FROM Product WHERE name LIKE %:name%")
    List<Product> searchProduct(@Param("name") String name);

}