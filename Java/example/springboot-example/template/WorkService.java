package edu.nuist.ceea.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.DigestUtils;

 
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

import java.util.List;

import javax.transaction.Transactional;

@Service
public class WorkService {
    @Autowired
    private WorkReps reps;

    public Work save (Work mm){
        return reps.save(mm);
    }

    public List<Work> findWorksByCidAndMidAndUid(long cid, long mid, long uid){
        return reps.findWorksByCidAndMidAndUid(cid, mid, uid);
    }

    public List<Work> findWorksByCidAndUid(long cid, long uid){
        return reps.findWorksByCidAndUid(cid,uid);
    }

    public Work findLastWorkCidAndMidAndUid(long cid, long mid, long uid){
        return reps.findLastWorkCidAndMidAndUid(cid, mid, uid);
    }

    public Work findById (long id){
        return reps.findById(id);
    }

    public void updateStatus(long wid, int status){
        reps.updateStatus(wid, status);
    }

    public void updateWm(long wid, long wmid){
        reps.updateWm(wid, wmid);
    }

    public void updateWe(long wid, long weId){
        reps.updateWe(wid, weId);
    }

    public List<Object> findByCid(long cid, int page, int size){
        return reps.findByCid(cid, page, size);
    }

    public List<Object> findByCid(long cid, String uname, int page, int size){
        return reps.findByCid(cid, uname, page, size);
    }

    public List<Object> findByCidAndMid(long cid, long mid, int page, int size){
        return reps.findByCidAndMid(cid, mid, page, size);
    }

    public List<Object> findByCidAndMid(long cid, long mid, String uname, int page, int size){
        return reps.findByCidAndMid(cid, mid,  uname, page, size);
    }
}
