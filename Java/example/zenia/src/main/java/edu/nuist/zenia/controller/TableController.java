package edu.nuist.zenia.controller;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.io.InputStreamResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

import edu.nuist.zenia.dbhelper.DBComdBean;
import edu.nuist.zenia.dbhelper.DBDefineMapper;
import edu.nuist.zenia.dbhelper.DBHelper;
import edu.nuist.zenia.util.FileUtil;

@RestController
public class TableController {
    @Value("${root.db}")
    private String dbRoot;

    @Value("${root.cache}")
    private String cache;
    
    @Value("${root.define}")
    private String define;

    @Value("${root.view}")
    private String view;

    public static final String TABLE_DEFINE_MODEL = "table_define_{0}.json";

    @RequestMapping("/table/saveCache")
    public void table(
        @RequestParam String jsonStr
    ) { 
        JSONObject json = JSON.parseObject(jsonStr);
        String guid = json.getString("guid");
        if( guid == null||"".equals(guid) ) guid = DBDefineMapper.getUUID();
        String fileName = TABLE_DEFINE_MODEL.replace("{0}", guid );
        json.put("guid", guid);
        FileUtil.writeStringToFile(json.toJSONString(), dbRoot + "/" + cache + "/" + fileName);
    }


    @RequestMapping("/table/delCache")
    public void delCache(
        @RequestParam String guid
    ) { 
        String fileName = TABLE_DEFINE_MODEL.replace("{0}", guid );
        new File(dbRoot + "/" + cache + "/" + fileName).delete();
    }

    @RequestMapping("/table/getCache")
    public List<JSONObject> getCache(
        HttpServletRequest request
    ) {
        Object obj = request.getSession().getAttribute(PageRouter.USER_CACHE);
        if(obj == null) {
            return  new ArrayList<>();
        }
        List<JSONObject> defines = new ArrayList<>();
        for(String file : new File(dbRoot  + "/" + cache).list()) {
            if(file.startsWith("table_define_")) {
                defines.add(JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + cache + "/" + file))) ;
            }
        }
        return defines;
    }

    @RequestMapping("/table/getTableDefine/{isCache}")
    public JSONObject getCacheByGuid(
        HttpServletRequest request,
        @PathVariable String isCache,
        @RequestParam String guid
    ) {
        
        String fileName = TABLE_DEFINE_MODEL.replace("{0}", guid );
        String path = dbRoot + "/" + cache + "/" + fileName;
        if(isCache.equals("table")) {
            path = dbRoot + "/" + define + "/" + fileName;
        }
        //System.out.println(path);
        return JSON.parseObject(FileUtil.getFileContent(path));
    }

    @Autowired
    private DBHelper dbHelper;

    @RequestMapping("/table/import")
    public void importTable(
        HttpServletRequest request,
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ) {
        Object obj = request.getSession().getAttribute(PageRouter.USER_CACHE);
        if(obj == null) {
            return;
        }

        JSONObject json = JSON.parseObject(jsonStr);
        String guid = json.getString("guid");
        JSONArray fields = json.getJSONArray("fields");

        String sql = new DBDefineMapper().mapCreateTable(guid, fields);
        DBComdBean bean = new DBComdBean();
        bean.setSql(sql);
        bean.setQuery(false);
        bean.setDbBean(null);
        bean.setTaskid(taskid);
        dbHelper.execTask(bean);

        new File(dbRoot + "/" + cache + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, guid)).delete();
        FileUtil.writeStringToFile(json.toJSONString(), dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, guid));
    }

    @RequestMapping("/table/getRst")
    public JSONObject exportTable(
        @RequestParam String taskid
    ) {
        return dbHelper.getCache(taskid);
    }

    @RequestMapping("/table/getTableList")
    public JSONArray getTableList(
        
    ) {
        String path = dbRoot + "/" + define;
        JSONArray tables = new JSONArray();
        for(String table : new File(path).list()) {
            if(table.startsWith("table_define_")) {
                JSONObject t =  JSON.parseObject(FileUtil.getFileContent(path + "/" + table));
                JSONObject rst = new JSONObject();
                rst.put("guid", t.getString("guid"));
                rst.put("tableName", t.getString("tableName"));
                tables.add(rst);
            }
        }

        return tables;
    }

    @RequestMapping("/table/delTableField")
    public void delTableField(
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String fid = json.getString("fid");
        String tid = json.getString("tid");
        dbHelper.delTableField(taskid, tid, fid);

        JSONObject table = JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid)));
        for(int i=0; i<table.getJSONArray("fields").size(); i++){
            JSONObject field = table.getJSONArray("fields").getJSONObject(i);
            if(fid.equals(field.getString("guid"))){
                table.getJSONArray("fields").remove(i);
                break;
            }
        }
        FileUtil.writeStringToFile(table.toJSONString(), dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid));
    }

    @SuppressWarnings("null")
    @RequestMapping("/table/updateTableField")
    public void updateTableField(
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String fid = json.getString("fid");
        String tid = json.getString("tid");
        String fname = json.getString("fname");
        String ftype = json.getString("ftype");
        int isNull = json.getIntValue("isnull");
        int ledgy = json.getIntValue("ledgy");
        

        JSONObject table = JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid)));
        JSONObject field = null;
        for(int i=0; i<table.getJSONArray("fields").size(); i++){
            field = table.getJSONArray("fields").getJSONObject(i);
            if(field.getString("guid").equals(fid)){
                break;
            }
        }

        if(field != null && (!field.getString("type").equals(ftype) || field.getIntValue("null") != isNull)){
            dbHelper.modifyTableField(taskid, tid, fid, Integer.parseInt(ftype), isNull);
        }else{
            dbHelper.nopExec(taskid);
        };

        field.put("name", fname);
        field.put("type", ftype);
        field.put("null", isNull);
        field.put("ledgy", ledgy);

        System.out.println("................" + taskid);
        FileUtil.writeStringToFile(table.toJSONString(), dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid));
    }

    @RequestMapping("/table/delTable")
    public void delTable(
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String tid = json.getString("guid");
        dbHelper.delTable(taskid, tid);
        new File(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid)).delete();
    }

    @RequestMapping("/table/modName")
    public void modTableName(
        @RequestParam String guid,
        @RequestParam String name
    ){
        JSONObject table = JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, guid)));
        table.put("tableName", name);
        FileUtil.writeStringToFile(table.toJSONString(), dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, guid));
    }

    @RequestMapping("/table/addTableField")
    public void addField(
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String tid = json.getString("tid");
        String fname = json.getString("fname");
        String ftype = json.getString("ftype");

        JSONObject table = JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid)));
        JSONObject field = new JSONObject();
        field.put("guid", DBDefineMapper.getUUID());
        field.put("name", fname);
        field.put("type", ftype);
        field.put("null", json.getIntValue("isnull"));
        field.put("ledgy", json.getString("ledgy"));
        table.getJSONArray("fields").add(field);

        FileUtil.writeStringToFile(table.toJSONString(), dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, tid));
        dbHelper.addTableField(taskid, tid, field.getString("guid"), Integer.parseInt(ftype), json.getIntValue("isnull"));
    }


    @RequestMapping("/table/getDBConnect")
    public String getDBConnect(
        
    ){
        if( !dbHelper.connectStatus()  ){
            return "fail";
        }
        return "success";
    }

    @RequestMapping("/autocomplete")
    public void autocomplete(
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String tid = json.getString("tid");
        String fid = json.getString("fid");

        
        dbHelper.autocomplete(taskid, tid, fid);
    }

    @RequestMapping("/insert/{table}" )
    public void insert(
        @PathVariable String table,
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);

        String tStr = dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, table);
        //System.out.println(tStr);
        dbHelper.insert(taskid, table, json, JSON.parseObject(FileUtil.getFileContent(tStr)));
        dbHelper.clearCache(taskid);
    }

    public static final String TABLE_VIEW_MODEL = "table_view_{0}.json";

    @RequestMapping("/table/getDefaultView/{table}")
    public JSONArray getDefaultView(
        @RequestParam String taskid,
        @PathVariable String table
    ){
        String tStr = dbRoot + "/" + view + "/" + MessageFormat.format(TABLE_VIEW_MODEL, table);
        String sql = new DBDefineMapper().getViewAll(table);

        JSONArray fieldDefine = null;
        if( new File(tStr).exists() ){
            JSONArray views  =  JSON.parseArray(FileUtil.getFileContent(tStr));
            for(int i=0; i<views.size(); i++){
                JSONObject o = views.getJSONObject(i);
                if(o.getBooleanValue("default")){
                    sql = o.getString("sql");
                    fieldDefine = o.getJSONArray("fieldDefine");
                    break;
                }
            }
        }

        dbHelper.execTask(new DBComdBean(taskid, sql, true, null));

        if( fieldDefine == null ){
            fieldDefine = JSON.parseObject(FileUtil.getFileContent(dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, table))).getJSONArray("fields");
        }
        return fieldDefine; 
    }


    @RequestMapping("/table/delRecord/{table}/{id}")    
    public void delRecord(
        @PathVariable String table,
        @PathVariable String id,
        @RequestParam String taskid
    ){
        String sql = new DBDefineMapper().getDelRecord(table, id);
        dbHelper.execTask(new DBComdBean(taskid, sql, false, null));
    }

    @RequestMapping("/table/getRecode/{table}/{id}")
    public void getRecord(
        @PathVariable String table,
        @PathVariable String id,
        @RequestParam String taskid
    ){
        String sql = new DBDefineMapper().queryRecord(table, id);
        dbHelper.execTask(new DBComdBean(taskid, sql, true, null));
        return;
    }

    @RequestMapping("/update/recorde/{table}/{id}")
    public void updateRecord(
        @PathVariable String table,
        @PathVariable String id,
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONObject json = JSON.parseObject(jsonStr);
        String tStr = dbRoot + "/" + define + "/" + MessageFormat.format(TABLE_DEFINE_MODEL, table);
        String sql = new DBDefineMapper().getUpdateRecord(table, id, json, JSON.parseObject(FileUtil.getFileContent(tStr)));
        dbHelper.execTask(new DBComdBean(taskid, sql, false, null));
    }

    @RequestMapping("/table/saveAttachment/{table}/{rid}")
    public void saveAttachment(
        @PathVariable String table,
        @PathVariable String rid,
        @RequestParam String taskid,
        @RequestParam String jsonStr
    ){
        JSONArray json = JSON.parseObject(jsonStr).getJSONArray("ids");

        String sql = new DBDefineMapper().batchInsertAttach(table, rid, json);
        System.out.println(sql);
        dbHelper.execTask(new DBComdBean(taskid, sql, false, null));
    }

    @RequestMapping("/table/getAttachment/{table}/{rid}")
    public void getAttachment(
        @PathVariable String table,
        @PathVariable String rid,
        @RequestParam String taskid
    ){
        String sql = new DBDefineMapper().getAttachment(table, rid);
        dbHelper.execTask(new DBComdBean(taskid, sql, true, null));
    }

    @Value("${root.file}")
    private String filedir;

    @RequestMapping("/table/download/{rid}")
    public ResponseEntity<InputStreamResource> down(
        @PathVariable String rid
    )throws IOException { 

        Path filePath = Paths.get( dbRoot + "/" + filedir + "/" + rid);
        // 获取文件输入流
        InputStream inputStream = Files.newInputStream(filePath);

        // 设置响应头
        HttpHeaders headers = new HttpHeaders();
        
        // 返回响应实体
        return ResponseEntity.ok()
                .headers(headers)
                .contentType(MediaType.APPLICATION_OCTET_STREAM)
                .body(new InputStreamResource(inputStream));
    }

    @RequestMapping("/table/delAttachment/{guid}/{rid}")
    public void delAttachment(
        @RequestParam String taskid,
        @PathVariable String rid,
        @PathVariable String guid
    ){ 
        new File(dbRoot + "/" + filedir + "/" + guid).delete();

        String sql = new DBDefineMapper().delAttachment(rid);
        dbHelper.execTask(new DBComdBean(taskid, sql, false, null));
    }
}
