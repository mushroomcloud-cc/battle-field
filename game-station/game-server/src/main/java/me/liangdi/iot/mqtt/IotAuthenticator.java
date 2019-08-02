package me.liangdi.iot.mqtt;

import io.moquette.broker.security.IAuthenticator;
import lombok.extern.slf4j.Slf4j;

/**
 * @author liangdi
 */
@Slf4j
public class IotAuthenticator implements IAuthenticator {
    @Override
    public boolean checkValid(String clientId, String username, byte[] password) {
        log.info("checkValid:{},{}",clientId,username);
        return true;
    }
}
