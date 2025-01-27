package edu.nuist.metelog.entity;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class LocationService {
    @Autowired
    private LocationReps locationReps;

    public Location save(Location location){
        return locationReps.save(location);
    }

    public Location findById(long id){
        return locationReps.findById(id);
    }

    public void deleteById(long id){
        locationReps.deleteById(id);
    }

    public List<Location> findAll(){
        return locationReps.findAll();
    }
}
