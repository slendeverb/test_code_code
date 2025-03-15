package edu.nuist.metelog.entity;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface WeathReps extends JpaRepository<Weath,Long> {
    @SuppressWarnings({ "unchecked", "null" })
    public Weath save(Weath i);

    
}
