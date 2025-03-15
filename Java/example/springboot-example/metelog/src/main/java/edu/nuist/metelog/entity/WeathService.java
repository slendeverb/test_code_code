package edu.nuist.metelog.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class WeathService {
    @Autowired
    private WeathReps weathReps;
    public Weath save(Weath weath){
        return weathReps.save(weath);
    }
}
