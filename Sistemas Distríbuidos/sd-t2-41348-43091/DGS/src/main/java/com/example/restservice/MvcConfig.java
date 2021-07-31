package com.example.restservice;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class MvcConfig implements WebMvcConfigurer {

	public void addViewControllers(ViewControllerRegistry registry) {
		registry.addViewController("/distribute-vaccines.html").setViewName("distribute-vaccines");
		registry.addViewController("/list-vaccinated.html").setViewName("list-vaccinated");
	}

}