package edu.nuist.metelog.utils;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import edu.nuist.metelog.entity.Location;
import edu.nuist.metelog.entity.LocationService;
import edu.nuist.metelog.entity.Weath;
import edu.nuist.metelog.entity.WeathService;

@Component
public class Timer { 
    @Autowired
    private WeathService weathService;

    @Autowired
    private LocationService locationService;

    @Scheduled(fixedRate = 3600000) // 每5秒执行一次
    public void executeTask() {
        List<Location> locations = locationService.findAll();
        WeathHelper weathHelper = new WeathHelper();

        for (Location location : locations) {
            String info = weathHelper.get(location.getLat(), location.getLon());
            Weath weath = new Weath();
            weath.setInfo(info);
            weath.setLid(location.getId());
            weathService.save(weath);
        }
    }
}
