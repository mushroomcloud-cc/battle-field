package me.liangdi.iot.mqtt;

import io.moquette.broker.security.IAuthorizatorPolicy;
import io.moquette.broker.subscriptions.Topic;
import lombok.extern.slf4j.Slf4j;

/**
 * @author liangdi
 */
@Slf4j
public class IotAuthorizatorPolicy implements IAuthorizatorPolicy {
    @Override
    public boolean canWrite(Topic topic, String user, String client) {
        log.info("canWrite:{},{}",topic,user);
        return true;
    }

    @Override
    public boolean canRead(Topic topic, String user, String client) {
        log.info("canRead:{},{}",topic,user);
        return true;
    }
}
