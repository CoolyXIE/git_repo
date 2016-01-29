# -*- coding: utf-8 -*-
import datetime

class MyClass(object):
    def __init__(self):
        self.create_at = datetime.datetime.now()

    def __str__(self):
        return "my create at {0}".format(self.create_at)


import new
obj = MyClass()
obj.hello = "Hello" #动态添加成员对象
say = lambda self:self.create_at
obj.say = new.instancemethod(lambda self:self.create_at, obj, MyClass)
print obj.say()
