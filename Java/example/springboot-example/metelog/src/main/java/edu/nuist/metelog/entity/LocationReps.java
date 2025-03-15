package edu.nuist.metelog.entity;


import java.util.List;

import javax.transaction.Transactional;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface LocationReps  extends JpaRepository<Location,Long> {
    @SuppressWarnings({ "unchecked", "null" })
    public Location save(Location i);

    public Location findById(long id);

    @Transactional
    public void deleteById(long id);

    @SuppressWarnings("null")
    public List<Location> findAll();
}
