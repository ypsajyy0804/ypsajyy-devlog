package com.environment.test;

import org.springframework.web.bind.annotation.*;

@RestController
public class HelloController {
    @GetMapping("/hi")
    public String hi() {
        return "hello";
    }
}