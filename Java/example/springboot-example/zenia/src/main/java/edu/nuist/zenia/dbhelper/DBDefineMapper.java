package edu.nuist.zenia.dbhelper;

import java.text.MessageFormat;
import java.util.Random;
import java.util.UUID;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

public class DBDefineMapper {
    public static final String delTableField = "ALTER TABLE {0} DROP COLUMN {1};";
    public static final String modifyTableField = "ALTER TABLE {0} MODIFY COLUMN {1} {2};";
    public static final String addTableField = "ALTER TABLE {0} ADD COLUMN {1} {2} {3} ;";

    public static final String queryFieldAndSort = "SELECT DISTINCT {0} FROM {1} ORDER BY {0};" ;

    public static final String queryAll = "SELECT * FROM {0} order by id desc;";
    public static final String delRecord = "DELETE FROM {0} WHERE id = {1};";
    public static final String queryRecord = "SELECT * FROM {0} WHERE id = {1};";

    public String getDelRecord(String table, String id){
        return MessageFormat.format(delRecord, table, id); 
    }

    public String queryRecord(String table, String id){
        return MessageFormat.format(queryRecord, table, id);
    }

    public String getViewAll(String table){
        return MessageFormat.format(queryAll, table);
    }

    public final String mapAutoComplete(String table, String field){
        return MessageFormat.format(queryFieldAndSort, field, table);
    }

    public String mapAddTableField(String tid , String field, int type, int isNull){
        return MessageFormat.format(addTableField, tid, field, MYSQL_FIELD_TYPE_DEFINES[type], isNull == 0 ? " NOT NULL" : " NULL");
    }
        

    public String mapDelTable(String tid){
        return "DROP TABLE " + tid + ";";
    }

    public String mapDelTableField(String tid, String fid){
        return MessageFormat.format(delTableField, tid, fid);
    }

    public String mapModifyTableField(String tid, String fid, int type, int isNull){
        String sql = MessageFormat.format(modifyTableField, tid, fid, MYSQL_FIELD_TYPE_DEFINES[type], isNull == 0 ? " NOT NULL" : " NULL");
        return sql;
    }

    public String mapCreateTable(String guid, JSONArray jsonArray) {
        String sql  = "";
        for(int i=0; i<jsonArray.size(); i++){
            JSONObject o = jsonArray.getJSONObject(i);
            String def = "," + fieldDef(o);
            
            if(i == jsonArray.size() - 1){
                def += ", PRIMARY KEY (id)";
            }
            sql += def ;
        }
        return MessageFormat.format(CREATE_TABLE, guid, sql);
    }

    public static final String CREATE_TABLE = "CREATE TABLE {0} (  id BIGINT NOT NULL AUTO_INCREMENT {1});";
    
    public String fieldDef(JSONObject o){
        String type = MYSQL_FIELD_TYPE_DEFINES [ o.getInteger("type") ];
        String fieldName = getUUID();
        String def = fieldName + " " + type;
        if (o.getInteger("null") == 1) {
            def += " " + NOT_NULL;
        }
        o.put("guid", fieldName);
        return def;
    }

    public static String getUUID(){
        return (char)(new Random().nextInt(26) + 'a') + UUID.randomUUID().toString().substring(0, 7);
    }

    public String getUpdateRecord(String guid, String rid, JSONObject data, JSONObject tableDefine){
        String sql = "UPDATE " + guid + " SET ";
        JSONArray fields = tableDefine.getJSONArray("fields");
        for(int i=0; i<fields.size(); i++){
            JSONObject field = fields.getJSONObject(i);
            if( data.getString(field.getString("guid")) != null ){
                int type = Integer.valueOf( field.getString("type") );
                if( type == TIMESTAMP){
                    continue;
                }

               // sql += field.getString("guid") + ",";
                if( type == LONG_TEXT || type == TEXT || type == DATETIME){
                    sql += field.getString("guid") + "='" + data.getString(field.getString("guid")) + "',";
                }else if( type == BOOLEAN){
                    sql += field.getString("guid") + "=" + data.getIntValue(field.getString("guid")) + ",";
                }else if( type == INTEGER){
                    sql += field.getString("guid") + "=" + data.getInteger(field.getString("guid")) + ",";
                }else{
                    sql += field.getString("guid") + "=" + data.getDouble(field.getString("guid")) + ",";
                }
            }
        }

        sql = sql.substring(0, sql.length() - 1) + " WHERE id=" + rid;

        return sql;
    }

    public String mapInsert(String guid, JSONObject data, JSONObject tableDefine){
        String sql = "INSERT INTO " + guid + " (";
        String values = " VALUES (";
        
        JSONArray fields = tableDefine.getJSONArray("fields");
        for(int i=0; i<fields.size(); i++){
            JSONObject field = fields.getJSONObject(i);
            if( data.getString(field.getString("guid")) != null ){
                int type = Integer.valueOf( field.getString("type") );
                if( type == TIMESTAMP){
                    continue;
                }

                sql += field.getString("guid") + ",";
                if( type == LONG_TEXT || type == TEXT || type == DATETIME){
                    values += "'" + data.getString(field.getString("guid")) + "',";
                }else if( type == BOOLEAN){
                    values += data.getIntValue(field.getString("guid")) + ",";
                }else if( type == INTEGER){
                    values += data.getInteger(field.getString("guid")) + ",";
                }else{
                    values += data.getDouble(field.getString("guid")) + ",";
                }
            }
            
        }
        sql = sql.substring(0, sql.length() - 1) + ")";
        values = values.substring(0, values.length() - 1) + ")";

        return sql + values;
    }


    public String batchInsertAttach(String table, String rid, JSONArray attachs){
        String sql = "INSERT INTO attachment (table_id, attach_rid, attach_guid, attach_file_name) VALUES ";
        for(int i=0; i<attachs.size(); i++){
            JSONObject attach = attachs.getJSONObject(i);
            sql += "('" +table + "', " + rid + ",'" + attach.getString("innerId") + "','" + attach.getString("originName") + "'),";
        }
        sql = sql.substring(0, sql.length() - 1);
        return sql;
    }

    public String getAttachment(String table, String rid){
        return "SELECT * FROM attachment WHERE table_id='" + table + "' AND attach_rid=" + rid;
    }

    public String delAttachment(String rid){
        return "DELETE FROM attachment WHERE id=" + rid;
    }


    public static final int LONG_TEXT = 0;
    public static final int TEXT = 1;
    public static final int INTEGER = 2;
    public static final int DOUBLE = 3;
    public static final int PRICE = 4;
    public static final int DATETIME = 5;
    public static final int BOOLEAN = 6;
    public static final int TIMESTAMP = 7;

    public static final String NOT_NULL = "NOT NULL";

    public final String[] MYSQL_FIELD_TYPE_DEFINES = {
        "LONGTEXT",
        "VARCHAR(255)",
        "INT",
        "DOUBLE",
        "DECIMAL(10,2)",
        "DATETIME",
        "TINYINT",
        "TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    };
}
