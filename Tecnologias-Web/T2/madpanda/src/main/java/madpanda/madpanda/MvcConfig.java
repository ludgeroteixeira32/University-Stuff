package madpanda.madpanda;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class MvcConfig implements WebMvcConfigurer {

	public void addViewControllers(ViewControllerRegistry registry) {
		registry.addViewController("/index").setViewName("index");
		registry.addViewController("/index2").setViewName("index2");
		registry.addViewController("/admin").setViewName("admin");
		registry.addViewController("/erro").setViewName("erro");
		registry.addViewController("/login").setViewName("login");
		registry.addViewController("/add-client").setViewName("add-client");
		registry.addViewController("/product").setViewName("product");
		registry.addViewController("/advanced-search").setViewName("advanced-search");
		registry.addViewController("/search").setViewName("search");
		registry.addViewController("/add-product").setViewName("add product");
		registry.addViewController("/list-product").setViewName("list product");
		registry.addViewController("/cart").setViewName("cart");
		registry.addViewController("/add-cart").setViewName("cart");
		registry.addViewController("/ordersuccess").setViewName("done");
		registry.addViewController("/list-order").setViewName("orderlist");
		//registry.addViewController("/").setViewName("");
	}
}