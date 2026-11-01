package com.environment.test;

import org.springframework.web.bind.annotation.*;
import org.springframework.http.ResponseEntity;
import java.util.ArrayList;
import java.util.List;

@RestController
public class BookController {
    static List<Book> books = new ArrayList<>();
    static long nextId = 1;

    @GetMapping("health")
    public ResponseEntity<String> health() {
        return ResponseEntity.notFound().build();
    }

    @PostMapping("/book")
    public String createBooks(@RequestParam String title, @RequestParam String author){
        Book book = new Book();
        book.setId(nextId++);
        book.setTitle(title);
        book.setAuthor(author);
        books.add(book);
        System.out.println("成功创建一本书籍，系统编号为：" + book.getId() + "\n");
        return book.getId() + "\n";
    }

    @GetMapping("/book")
    public List<Book> booksList() {
        return books;
    }

    @GetMapping("/book/{id}")
    public ResponseEntity<Book> seletId(@PathVariable Long id) {
        for (Book b : books) {
            if (b.getId().equals(id)) {
                return ResponseEntity.ok(b);
            }
        }
        return ResponseEntity.notFound().build();
    }

    @DeleteMapping("/book/{id}")
    public boolean deleteBooks(@PathVariable Long id) {
        List<Book> list = books;
        for(Book book: list){
            if(book.getId().equals(id)) {
                books.remove(book);
                System.out.println("删除成功");
                return true;
            }
        }
        System.out.println("删除失败");
        return false;
    }
}