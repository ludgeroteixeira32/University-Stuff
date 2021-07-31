package com.example.restservice;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class MvcConfig implements WebMvcConfigurer {

	public void addViewControllers(ViewControllerRegistry registry) {
		registry.addViewController("/register-login.html").setViewName("register-login");
		registry.addViewController("/register-vaccine.html").setViewName("register-vaccine");
		registry.addViewController("/routine.html").setViewName("routine");
		registry.addViewController("/send-list.html").setViewName("send-list.html");
	}

}