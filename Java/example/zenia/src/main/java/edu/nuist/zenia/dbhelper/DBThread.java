package edu.nuist.zenia.dbhelper;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import lombok.Data;

@Data
public class DBThread implements Runnable {
    private int id;
    private Connection connection;
    private boolean status;
    private String command;
    private boolean isQuery;
    private HashMap<String, Object> cache = new HashMap<>();

    private String taskid;

    private Object lock = null;

    public DBThread(int id , Connection connection , Object lock, HashMap<String, Object> cache) {
        this.id = id;
        this.connection = connection;
        this.cache = cache;
        this.lock = lock;
        this.status = false;
    }

    public void prepare(String command, boolean isQuery, String taskid){
        this.status = true;
        this.command = command;
        this.isQuery = isQuery;
        this.taskid = taskid;
    }

    @Override
    public void run() {
        if( isQuery){
            List<Map<String, String>> rst = executeQueryToList(command);
            putQueryRstList(isQuery, rst);
        }else{
            int affectRows = executeCommand(command);
            putQueryRstList(isQuery, affectRows);
        }
        System.out.println("Thread " + id + " exec task finished.");
        this.status = false;
    }

    public void putQueryRstList(boolean isQuery, Object rst){
        synchronized(lock){
            this.taskid = isQuery ? this.taskid + "_query" : this.taskid + "_command";
            cache.put(this.taskid, rst);
        }
    }

    public List<Map<String, String>> executeQueryToList(String query) {
        List<Map<String, String>> resultList = new ArrayList<>();
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(query);
            int columnCount = resultSet.getMetaData().getColumnCount();
            while (resultSet.next()) {
                Map<String, String> rowMap = new HashMap<>();
                for (int i = 1; i <= columnCount; i++) {
                    // 获取每一列的数据
                    String columnName = resultSet.getMetaData().getColumnName(i);
                    String columnValue = resultSet.getString(i);
                    rowMap.put(columnName, columnValue);
                }
                resultList.add(rowMap);
            }
        } catch (SQLException e) {
            System.out.println("执行SQL查询失败！");
            e.printStackTrace();
        } finally {
            // 关闭数据库连接、Statement对象和ResultSet对象
            if (resultSet != null) {
                try {
                    resultSet.close();
                } catch (SQLException e) {
                    System.out.println("关闭ResultSet对象失败！");
                    e.printStackTrace();
                }
            }
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException e) {
                    System.out.println("关闭Statement对象失败！");
                    e.printStackTrace();
                }
            }
        }
        return resultList;
    }

    public int executeCommand(String command) {
        Statement statement = null;
        try {
            statement = connection.createStatement();
            int rowsAffected = statement.executeUpdate(command);
            return rowsAffected;
        } catch (SQLException e) {
            System.out.println("执行SQL命令失败！");
            e.printStackTrace();
            return -1;
        } finally {
            // 关闭数据库连接和Statement对象
            if (statement != null) {
                try {
                    statement.close();
                } catch (SQLException e) {
                    System.out.println("关闭Statement对象失败！");
                    e.printStackTrace();
                }
                return 0;
            }
        }
    }
    
    public void shutdown() {
        try {
            connection.close();
        } catch (SQLException e) {
            System.out.println("关闭数据库连接失败！");
            e.printStackTrace();
        }
    }
}
