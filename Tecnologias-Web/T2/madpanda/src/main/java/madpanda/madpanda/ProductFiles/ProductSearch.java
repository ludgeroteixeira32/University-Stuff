package madpanda.madpanda.ProductFiles;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

@Controller
public class ProductSearch {
    @Autowired
    private ProductRepository repository;
    private static final Logger log = LoggerFactory.getLogger(DelProduct.class);

    @PostMapping("/search-product")
    public String searchProduct(@RequestParam(name="name") String name, Model model){
        log.info(name+"");
        List<Product> product = repository.searchProduct(name);
        model.addAttribute("product", product);


        return "/index2";
    }


}
