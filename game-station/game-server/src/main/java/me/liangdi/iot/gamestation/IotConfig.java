package me.liangdi.iot.gamestation;

import me.liangdi.iot.mqtt.IotServer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * @author liangdi
 */
@Configuration
public class IotConfig {

    @Bean
    public IotServer iotServer() {
        IotServer server = new IotServer();
        server.init();
        return server;
    }
}
