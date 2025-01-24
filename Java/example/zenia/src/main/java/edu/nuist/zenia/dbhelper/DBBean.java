package edu.nuist.zenia.dbhelper;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import lombok.Data;

@Data
public class DBBean {
    private long id;
    private String tableName;

    public DBBean() {
    }

    public List<DBBean> covert(List<Map<String, String>> rows){
        List<DBBean> beans = new ArrayList<>();
        for (Map<String, String> row : rows) {
            beans.add(getBean(row));
        }
        return beans;
    }

    public DBBean getBean(Map<String, String> row){
        return null;
    }

    public DBComdBean getInsertSQL(){
        return null;
    }

    public DBComdBean getDelSQL(){
        return null;
    }

    public DBComdBean getUpdateSQL(){
        return null;
    }

    public DBComdBean getSelectSQL(){
        return null;
    }
}
