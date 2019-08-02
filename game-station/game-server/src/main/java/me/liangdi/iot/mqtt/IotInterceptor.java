package me.liangdi.iot.mqtt;

import io.moquette.interception.AbstractInterceptHandler;
import io.moquette.interception.messages.InterceptConnectMessage;
import lombok.extern.slf4j.Slf4j;

/**
 * @author liangdi
 */
@Slf4j
public class IotInterceptor extends AbstractInterceptHandler {
    @Override
    public String getID() {
        return "IotInterceptor";
    }

    @Override
    public void onConnect(InterceptConnectMessage msg) {
        super.onConnect(msg);
        log.info("client:{} connected",msg.getClientID());
    }
}
