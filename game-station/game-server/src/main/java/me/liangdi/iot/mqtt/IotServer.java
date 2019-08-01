package me.liangdi.iot.mqtt;

import io.moquette.broker.Server;
import io.moquette.broker.config.ClasspathResourceLoader;
import io.moquette.broker.config.IConfig;
import io.moquette.broker.config.IResourceLoader;
import io.moquette.broker.config.ResourceLoaderConfig;
import io.moquette.interception.InterceptHandler;
import lombok.extern.slf4j.Slf4j;

import java.io.IOException;
import java.util.Collections;
import java.util.List;

/**
 * @author liangdi
 */
@Slf4j
public class IotServer {

    final Server broker = new Server();


    public void init() {
        log.info("broker init");
        IResourceLoader classpathLoader = new ClasspathResourceLoader();
        final IConfig classPathConfig = new ResourceLoaderConfig(classpathLoader);
        List<? extends InterceptHandler> userHandlers = Collections.singletonList(new IotInterceptor());

        broker.startServer(classPathConfig,userHandlers,null,new IotAuthenticator(),new IotAuthorizatorPolicy());

    }
}
