package me.liangdi.iot.gamestation;

import me.liangdi.iot.mqtt.IotServer;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

/**
 * @author liangdi
 */
@SpringBootApplication
public class GameStationApplication {

    public static void main(String[] args) {
        SpringApplication.run(GameStationApplication.class, args);
    }


}
