package madpanda.madpanda.OrderFiles;

import madpanda.madpanda.ProductFiles.Product;
import madpanda.madpanda.ProductFiles.ProductRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.util.List;

@Controller
public class ListOrder {
    private static final Logger log = LoggerFactory.getLogger(madpanda.madpanda.ProductFiles.ListProduct.class);

    @Autowired
    private OrderRepository repository;

    @GetMapping("/list-order")
    public String listProduct(Model model)
    {
        Object principal = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String username;
        if(principal instanceof UserDetails){
            username =((UserDetails)principal).getUsername();
        }else{
            username= principal.toString();
        }

        List<Order> orderlist = (List<Order>) repository.findAllByUsername(username);

        log.info("Orders found with findAll():");
        log.info("-------------------------------");
        for (Order Order : orderlist) {
            log.info(Order.toString());
        }
        log.info("");

        model.addAttribute("OrderList", orderlist);
        return "list-order-view";
    }
}