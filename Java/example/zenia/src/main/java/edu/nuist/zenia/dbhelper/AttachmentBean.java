package edu.nuist.zenia.dbhelper;

import lombok.Data;

@Data
public class AttachmentBean {

    private String tableId;
    private String attachRid;
    private String attachGuid;
    private String attachFileName;

    public static String CREATE_TABLE = "CREATE TABLE IF NOT EXISTS attachment ("
            + "id INT AUTO_INCREMENT PRIMARY KEY,"
            + "table_id VARCHAR(255) NOT NULL,"
            + "attach_rid VARCHAR(255) NOT NULL,"
            + "attach_guid VARCHAR(255) NOT NULL,"
            + "attach_file_name VARCHAR(255) NOT NULL"
            + ");";

    public static String INSERT = "INSERT INTO attachment (table_id, attach_rid, attach_guid, attach_file_name) VALUES ({0}, {1}, {2}, {3});";

    public static String SELECT = "SELECT * FROM attachment WHERE table_id = {0} AND attach_rid = {1};";
    public static String create(){
        return CREATE_TABLE;
    }
}
