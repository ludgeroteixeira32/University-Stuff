package madpanda.madpanda.ProductFiles;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class DelProduct {

    @Autowired
    private ProductRepository repository;
    private static final Logger log = LoggerFactory.getLogger(DelProduct.class);

    @GetMapping("/del-product")
    public String removeProduct(@RequestParam(name="id") Long id, Model model){
        log.info(id+"");
      repository.deleteById(id);

      return "redirect:/list-product";
    }
}
