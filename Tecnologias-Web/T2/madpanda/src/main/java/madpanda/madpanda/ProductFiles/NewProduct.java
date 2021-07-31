package madpanda.madpanda.ProductFiles;

import org.apache.tomcat.util.codec.binary.Base64;
import org.apache.tomcat.util.codec.binary.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;

@Controller
public class NewProduct {
    private static final Logger log = LoggerFactory.getLogger(NewProduct.class);

    @Autowired
    private ProductRepository repository;

    @PostMapping("/new-product")
    public String newProduct(
            @RequestParam(name="name", required=true, defaultValue="") String name,
            @RequestParam(name="image", required=true, defaultValue="") MultipartFile image,
            @RequestParam(name="details", required=true, defaultValue="") String details,
            @RequestParam(name="price", required=true, defaultValue="") Float price,
            Model model) throws IOException {

        StringBuilder sb = new StringBuilder();
        sb.append("data:image/png;base64,");
        sb.append(StringUtils.newStringUtf8(Base64.encodeBase64(image.getBytes(), false)));

        repository.save(new Product(name, sb.toString(), details, price));

        log.info("Products found with findAll():");
        log.info("-------------------------------");
        for (Product Product : repository.findAll()) {
            log.info(Product.toString());
        }
        log.info("");

        model.addAttribute("name", name);
        model.addAttribute("image", sb.toString());
        model.addAttribute("details", details);
        model.addAttribute("price", price);
        return "new-product-view";
    }
}
