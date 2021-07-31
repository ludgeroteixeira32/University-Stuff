package madpanda.madpanda;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class Mapping {
    
    @GetMapping("/index2")
    public String getIndex2(){return "index2";}

    @GetMapping("/login")
    public String getLogin(){return "login";}    
    
    @GetMapping("/add-client")
    public String getNewclient(){return "new-client";}

    @GetMapping("/product")
    public String getProduct(){return "product";}  

    @GetMapping("/advanced-search")
    public String getAdvancedsearch(){return "advanced_search";}

    @GetMapping("/search")
    public String getSearch(){return "search";}

    @GetMapping("/add-product")
    public String getNewproduct(){return "new-product";}



}
