package edu.nuist.zenia.dbhelper;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import com.alibaba.fastjson.JSONObject;

import cn.hutool.json.JSONArray;



@Component
public class DBHelper {
    @Value("${db.url}")
    private String url;

    @Value("${db.username}")
    private String username;

    @Value("${db.password}")
    private String password;
    
    @Value("${db.threadnum}")
    int threadNum;

    private List<DBThread> dbThreadList = new ArrayList<>();
    private HashMap<String, Object> cache = new HashMap<>();

    private Object lock = new Object();

    public void insert(String taskid, String table, JSONObject data, JSONObject tableDefine){
        String sql = new DBDefineMapper().mapInsert(table, data, tableDefine);
        //System.out.println("sql: " + sql);
        DBComdBean bean = new DBComdBean(taskid, sql, false, null);
        execTask(bean);
    }

    public JSONArray autocomplete(String taskid, String table, String field){
        if( cache.containsKey(taskid) ){
            return (JSONArray)cache.get(taskid);
        }
        String sql = new DBDefineMapper().mapAutoComplete(table, field);
        DBComdBean bean = new DBComdBean(taskid, sql, true, null);
        execTask(bean);
        return null;
    }

    public String getKey(String cmd){
        return cmd;
    }

    public void nopExec(String taskid){
        this.cache.put(taskid, "success");
    }

    public void addTableField(String taskid, String tid, String guid, int ftype, int isNull){
        String sql = new DBDefineMapper().mapAddTableField(tid, guid, ftype, isNull);
        DBComdBean bean = new DBComdBean(taskid, sql, false, null);
        execTask(bean);
    }

    public void delTable(String taskid, String tid){
        String sql = new DBDefineMapper().mapDelTable(tid);
        DBComdBean bean = new DBComdBean(taskid, sql, false, null);
        execTask(bean);
    }

    public void delTableField(String taskid, String tid, String fid){
        String sql = new DBDefineMapper().mapDelTableField(tid, fid);
        DBComdBean bean = new DBComdBean(taskid, sql, false, null);
        execTask(bean);
    }

    public void modifyTableField(String taskid, String tid, String fid, int ftype, int isNull){
        String sql = new DBDefineMapper().mapModifyTableField(tid, fid, ftype, isNull);
        System.out.println("sql: " + sql);
        DBComdBean bean = new DBComdBean(taskid, sql, false, null);
        execTask(bean);
    }

    @SuppressWarnings("null")
    public void execTask(DBComdBean bean){
        DBThread dbThread = null;
        for(DBThread thread : dbThreadList){
            if(!thread.isStatus()){
                dbThread = thread;
                break;
            }
        }
        System.out.println("ss................" + bean.getTaskid());
        dbThread.prepare(bean.getSql(), bean.isQuery(), bean.getTaskid());
        new Thread(dbThread).start();
    }

    public JSONObject getCache(String taskid){
        JSONObject rst = new JSONObject();
        for(String key : cache.keySet()){
            System.out.println("key: " + key);
            if(key.startsWith(taskid)){
                rst.put("rst", cache.get(key));
                return rst;
            }
        }

        return null;
    }


    public void clearCache(String taskid){
        for(String key : cache.keySet()){
            if(key.startsWith(taskid)){
                cache.remove(key);
            }
        }
    }

    @PreDestroy
    public void shutdown() {
        for (DBThread dbThread : dbThreadList) {
            dbThread.shutdown();
        }
        System.out.println("数据库链接缓冲池已经关闭...");
    }

    @PostConstruct
    public void init() {
        Connection connection = connect();
        if( connection != null){
            System.out.println("数据库连接成功！................");
            for(int i = 0; i < threadNum; i++){
                connection = connect();
                if(connection != null){
                    DBThread dbThread = new DBThread(i, connection, lock, cache);
                    dbThreadList.add(dbThread);
                }
            }
            DBComdBean db = new DBComdBean();
            db.setDbBean(null);
            db.setQuery(false);
            db.setTaskid("");
            db.setSql(AttachmentBean.CREATE_TABLE);
            execTask(db);
        }else{
            System.out.println("数据库连接失败！...............");
        }
        System.out.println("DBHelper init................");
    }
   
    public boolean connectStatus(){
            try {
                Connection connection = connect();
                if(connection != null){
                    connection.close();
                    return true;
                }else{
                    return false;
                }
            }catch (SQLException e) {
                e.printStackTrace();
                return false;
            }
        }

    public Connection connect() {
        Connection connection = null;
        try {
            // 加载数据库驱动
            Class.forName("com.mysql.cj.jdbc.Driver");
            // 建立数据库连接
            connection = DriverManager.getConnection(url, username, password);

            // 测试连接是否成功
            if (connection != null) {
                return connection;
            } else {
                return null;
            }
        } catch (ClassNotFoundException e) {
            System.out.println("找不到数据库驱动类！");
            e.printStackTrace();
            return null;
        } catch (SQLException e) {
            System.out.println("数据库连接失败！");
            e.printStackTrace();
            return null;
        } 
    }

   
}