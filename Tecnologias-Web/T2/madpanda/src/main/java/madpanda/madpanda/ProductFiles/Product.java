package madpanda.madpanda.ProductFiles;

import madpanda.madpanda.OrderFiles.Order;

import javax.persistence.*;
import java.sql.Blob;

@Entity
public class Product {

    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;
    private String name;
    @Lob
    private String image;
    private String details;
    private Float price;

    @ManyToOne
    @JoinColumn(name="order_id")
    private Order order;

    protected Product() {}

    public Product(String name, String image, String details, Float price) {
        this.name = name;
        this.image = image;
        this.details = details;
        this.price = price;
    }

    @Override
    public String toString() {
        return "Product{" +
                "name='" + name + '\'' +
                ", image='" + image + '\'' +
                ", details='" + details + '\'' +
                ", price=" + price +
                '}';
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getImage() {
        return image;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }
}
