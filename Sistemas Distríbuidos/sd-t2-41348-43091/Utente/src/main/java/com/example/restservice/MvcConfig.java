package com.example.restservice;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class MvcConfig implements WebMvcConfigurer {

	public void addViewControllers(ViewControllerRegistry registry) {
		registry.addViewController("/index.html").setViewName("index.html");
		registry.addViewController("/options.html").setViewName("options.html");
		registry.addViewController("/centers.html").setViewName("centers.html");
		registry.addViewController("/agendamento.html").setViewName("agendamento.html");
		registry.addViewController("/agendamentoconcluido.html").setViewName("agendamentoconcluido.html");

	}

}