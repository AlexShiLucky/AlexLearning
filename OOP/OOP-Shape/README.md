- shape-01:子类包含父类，开放子类和父类所有数据；

- shape-02:子类包含父类，隐藏子类；

- shape-03:子类包含父类，开放子类，隐藏子类私有数据；

- shape-04:子类包含父类，开放子类和父类所有数据，子类实现的函数全部使用子类类型，父类虚表赋值时需类型强转;

- shape-05:子类包含父类，开放子类，隐藏子类私有数据，子类实现的函数全部使用子类类型，父类虚表赋值时需类型强转;

- shape-06:子类包含父类指针，父类包含子类指针，开放子类和父类所有数据；

- shape-07:子类包含父类指针，父类包含子类指针，隐藏子类；

- shape-08:子类包含父类指针，父类包含子类指针，开放子类，隐藏子类私有数据；

- shape-09:子类包含父类指针，父类包含子类指针，开放子类和父类所有数据，子类实现的函数全部使用子类类型，父类虚表赋值时需类型强转，父类调用虚表时需向虚表函数传递父类包含的子类指针;

- shape-10:子类包含父类指针，父类包含子类指针，开放子类，隐藏子类私有数据，子类实现的函数全部使用子类类型，父类虚表赋值时需类型强转，父类调用虚表时需向虚表函数传递父类包含的子类指针;