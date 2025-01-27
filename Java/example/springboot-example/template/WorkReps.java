package edu.nuist.ceea.entity;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;

import javax.transaction.Transactional;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;


@Repository
public interface WorkReps extends JpaRepository<Work,Long> {
    Work save (Work mm);
    Work findById( long id);

    @Query(value = "select * from work where c_id=?1 and m_id=?2 and stud_id=?3 order by version desc", nativeQuery = true)
    List<Work> findWorksByCidAndMidAndUid(long cid, long mid, long uid);

    @Query(value = "select * from work where c_id=?1 and m_id=?2 and stud_id=?3 order by version desc limit 0, 1", nativeQuery = true)
    Work findLastWorkCidAndMidAndUid(long cid, long mid, long uid);

    @Query(value = "select * from work where c_id=?1 and stud_id=?2 order by version desc limit 0, 1", nativeQuery = true)
    List<Work>  findWorksByCidAndUid(long cid,  long uid);

    @Transactional
    @Modifying
    @Query(value = "update work set status=?2 where id=?1 ", nativeQuery = true)
    void updateStatus(long wid, int status);

    @Transactional
    @Modifying
    @Query(value = "update work set wm_id=?2 where id=?1 ", nativeQuery = true)
    void updateWm(long wid, long wmid);

     @Transactional
    @Modifying
    @Query(value = "update work set we_id=?2 where id=?1 ", nativeQuery = true)
    void updateWe(long wid, long weid);


    @Query(value = "select max(w.id) from work w, user u where w.c_id=?1 and u.id=w.stud_id group by w.m_id, w.stud_id order by w.m_id, u.username limit ?2, ?3", nativeQuery = true)
    List<Object> findByCid(long cid, int page, int size);

    @Query(value = "select max(w.id) from work w, user u where w.c_id=?1 and u.id=w.stud_id and u.username like concat('%' ,?2,'%' ) group by w.m_id, w.stud_id order by w.m_id, u.username limit ?3, ?4", nativeQuery = true)
    List<Object> findByCid(long cid, String uname, int page, int size);

    @Query(value = "select max(w.id) from work w, user u where w.m_id=?2 and w.c_id=?1 and u.id=w.stud_id group by w.m_id, w.stud_id order by w.m_id, u.username limit ?3, ?4", nativeQuery = true)
    List<Object> findByCidAndMid(long cid, long mid, int page, int size);

    @Query(value = "select max(w.id) from work w, user u where w.m_id=?2 and w.c_id=?1 and u.id=w.stud_id and u.username like concat('%' ,?3,'%' ) group by w.m_id, w.stud_id order by w.m_id, u.username limit ?4, ?5", nativeQuery = true)
    List<Object> findByCidAndMid(long cid, long mid, String uname, int page, int size);
}
