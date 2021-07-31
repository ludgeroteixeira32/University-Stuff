package madpanda.madpanda.OrderFiles;
import madpanda.madpanda.ProductFiles.Product;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name="orders")
public class Order {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;
    private String username;

    @OneToMany(mappedBy = "order")
    private List<Product> cart;

    public Order(Long id, String username, List<Product> cart) {
        this.id = id;
        this.username = username;
        this.cart = cart;
    }

    public Order() {
        this.cart= new ArrayList<>();
    }

    @Override
    public String toString() {
        return "Order{" +
                "id=" + id +
                ", username='" + username + '\'' +
                ", cart=" + cart +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public List<Product> getCart() {
        return cart;
    }

    public void setCart(List<Product> cart) {
        this.cart = cart;
    }
}
