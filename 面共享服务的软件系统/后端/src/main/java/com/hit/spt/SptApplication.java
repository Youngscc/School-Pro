package com.hit.spt;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurationSupport;

@SpringBootApplication
public class SptApplication extends WebMvcConfigurationSupport {

    public static void main(String[] args) {
        SpringApplication.run(SptApplication.class, args);
    }

}
