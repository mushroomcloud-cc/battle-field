# -*- coding:utf-8 -*-
import timeit
import python.darknet as dn

# dn.set_gpu(0)
net = dn.load_net(str.encode("./cfg/yolov3.cfg"),
                  str.encode("./yolov3.weights"), 0)
meta = dn.load_meta(str.encode("./cfg/coco.data"))

start = timeit.default_timer()
r = dn.detect(net, meta, str.encode("./data/dog.jpg"))
stop = timeit.default_timer()

print('time: ', stop - start)  
print(r)
