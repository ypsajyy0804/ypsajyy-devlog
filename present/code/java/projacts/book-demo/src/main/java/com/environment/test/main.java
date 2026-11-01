package com.environment.test;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

@SpringBootApplication
public class main {
    public static void main(String[] args) {
        SpringApplication.run(main.class, args);
        System.out.println("启动成功");
    }

//    @Bean
//    CommandLineRunner dbCheck(DataSource ds) {
//        return args -> {
//            try (Connection c = ds.getConnection();
//                 Statement st = c.createStatement();
//                 ResultSet rs = st.executeQuery("SELECT @@port, DATABASE(), VERSION()")) {
//                rs.next();
//                System.out.println("probe: port=" + rs.getInt(1)
//                        + " db=" + rs.getString(2)
//                        + " version=" + rs.getString(3));
//            }
//        };
//    }
}