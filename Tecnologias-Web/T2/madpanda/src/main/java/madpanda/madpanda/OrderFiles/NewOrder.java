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
import org.springframework.web.bind.annotation.RequestParam;

import java.security.SecureClassLoader;


@Controller
public class NewOrder {
    private static final Logger log = LoggerFactory.getLogger(madpanda.madpanda.ProductFiles.ListProduct.class);

    @Autowired
    private OrderRepository repository;

    @Autowired
    private ProductRepository repositoryp;

    Order order = new Order();


    @GetMapping("/add-cart")
    public String addCart(@RequestParam(name="id") Long id, Model model)
    {
        order.getCart().add(repositoryp.findById(id).get());
        model.addAttribute("ProductList", order.getCart());
        return "redirect:/list-cart";
    }

    @GetMapping("/list-cart")
    public String listProduct(Model model)
    {


        log.info("Orders found with findAll():");
        log.info("-------------------------------");
        for (Order Order : repository.findAll()) {
            log.info(Order.toString());
        }
        log.info("");

        model.addAttribute("ProductList", order.getCart());
        return "cart";
    }

    @GetMapping("/order-done")
    public String orderDone(Model model)
    {

        Object principal = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
        String username;
        if(principal instanceof UserDetails){
            username =((UserDetails)principal).getUsername();
        }else{
            username= principal.toString();
        }

        order.setUsername(username);

        repository.save(order);
        order = new Order();
        return "redirect:/list-cart";
    }
}