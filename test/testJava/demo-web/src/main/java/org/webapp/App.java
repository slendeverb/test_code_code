package org.webapp;

import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class App extends HttpServlet {
    public static void main(String[] args) {
        
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        DateFormat dtFormat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String currentTime=dtFormat.format(new Date());

        req.setAttribute("currentTime", currentTime);
        req.getRequestDispatcher("/index.jsp").forward(req, resp);
    }
}
