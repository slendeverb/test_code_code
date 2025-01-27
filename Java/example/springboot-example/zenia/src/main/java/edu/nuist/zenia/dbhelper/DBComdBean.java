package edu.nuist.zenia.dbhelper;

import lombok.Data;

@Data
public class DBComdBean {
    private String sql;
    private boolean isQuery;
    private DBBean dbBean;
    private String taskid;

    public DBComdBean() {
    }

    public DBComdBean(String taskid, String sql, boolean isQuery, DBBean dbBean) {
        this.taskid = taskid;
        this.sql = sql;
        this.isQuery = isQuery;
        this.dbBean = dbBean;
    }

}
