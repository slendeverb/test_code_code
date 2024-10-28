<%@ page language="java" contentType="text/html" pageEncoding="utf-8" %>
<%
    int num = 7 + (int) (Math.random() * 13);
    if (num <= 13) {
        out.print("<h1>Hello</h1><br>");
    } else {
        out.print("<h1>hello</h1><br>");
    }
%>

<html lang="en">
    <head>
        <meta charset="UTF-8">
    </head>

    <body>
        
    </body>
</html>