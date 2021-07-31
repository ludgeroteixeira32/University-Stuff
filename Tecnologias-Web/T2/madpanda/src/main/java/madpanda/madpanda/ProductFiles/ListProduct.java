package madpanda.madpanda.ProductFiles;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.util.List;

@Controller
public class ListProduct {
    private static final Logger log = LoggerFactory.getLogger(ListProduct.class);

    @Autowired
    private ProductRepository repository;

    @GetMapping("/list-product")
    public String listProduct(Model model)
    {
        List<Product> ProductList = (List<Product>) repository.findAll();

        log.info("Products found with findAll():");
        log.info("-------------------------------");
        for (Product Product : repository.findAll()) {
            log.info(Product.toString());
        }
        log.info("");

        model.addAttribute("ProductList", ProductList);
        return "list-product-view";
    }
}
