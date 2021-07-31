package madpanda.madpanda;

import madpanda.madpanda.ProductFiles.ListProduct;
import madpanda.madpanda.ProductFiles.Product;
import madpanda.madpanda.ProductFiles.ProductRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;

import java.util.List;

@Controller
public class IndexController {

    @Autowired
    private ProductRepository repository;

    private static final Logger log = LoggerFactory.getLogger(ListProduct.class);

    @GetMapping("/index")
    public String homeObjects(Model model)
    {
        List<Product> HomeList = (List<Product>) repository.findAll();

        log.info("Products found with findAll():");
        log.info("-------------------------------");
        for (Product Product : repository.findAll()) {
            log.info(Product.toString());
        }
        log.info("");

        model.addAttribute("HomeList", HomeList);
        return "/index";
    }
}
