package edu.nuist.zenia;

import javax.annotation.PostConstruct;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import edu.nuist.zenia.dbhelper.DBHelper;

@Component
public class ContextClosedHandler {
    @Autowired
    private DBHelper dbHelper;

    @PostConstruct
    public void registerShutdownHook() {
        Thread shutdownThread = new Thread(() -> {
            // 在这里编写关闭前需要执行的代码
            dbHelper.shutdown();
        });
        Runtime.getRuntime().addShutdownHook(shutdownThread);
    }
}