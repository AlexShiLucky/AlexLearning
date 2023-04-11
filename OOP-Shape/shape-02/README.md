- shape_t是父类，shape_vtbl_t是父类的虚表，需每个子类各自实现；
  
  ```c
  /* 父类接口声明 */
  typedef struct _shape_vtbl shape_vtbl_t;
  /* 父类声明 */
  typedef struct _shape shape_t;
  
  /* 父类结构定义 */
  struct _shape {
      int type;
      const char *name;
      const shape_vtbl_t *vtbl;       /* 虚接口,所有子类必须实现 */
  };
  
  /* 父类接口定义 */
  struct _shape_vtbl {
      /* 计算几何体的面积 */
      float (*area)(shape_t const * const);
      /* 计算几何体的周长 */
      float (*perimeter)(shape_t const * const);
      /* 画出图形 */
      void (*draw)(shape_t const * const);
      /* 销毁形状 */
      void (*distory)(shape_t * const);
  };
  ```

- circle_t是圆类，继承父类shape_t，将父类定义成子类结构的第一个元素来继承父类，将子类类型定义在c文件中实现对外异常子类；
  
  ```c
  /* 对外隐藏子类定义 */
  typedef struct _circle circle_t;
  
  /* 子类:圆 */
  struct _circle {
      /* 将父类定义在子类的第一个元素,来继承父类 */
      shape_t super;
      /* 子类特有属性 */
      float diameter;
  };
  ```

- rectangle_t是矩形类，继承父类shape_t，将父类定义成子类结构的第一个元素来继承父类，将子类类型定义在c文件中实现对外异常子类；
  
  ```c
  /* 对外隐藏子类定义 */
  typedef struct _rectangle rectangle_t;
  
  /* 子类:矩形 */
  struct _rectangle {
      /* 将父类定义在子类的第一个元素,来继承父类 */
      shape_t super;
      /* 子类特有属性 */
      float width;
      float height;
  };
  ```

- triangle_t是三角类，继承父类shape_t，将父类定义成子类结构的第一个元素来继承父类，将子类类型定义在c文件中实现对外异常子类；
  
  ```c
  /* 对外隐藏子类定义 */
  typedef struct _triangle triangle_t;
  
  /* 子类:三角形 */
  struct _triangle {
      /* 将父类定义在子类的第一个元素,来继承父类 */
      shape_t super;
      /* 子类特有属性 */
      float a;
      float b;
      float c;
  };
  ```

- 子类实现父类的虚表，以圆类为例
  
  ```c
  static float circle_area(shape_t const * const super);
  static float circle_perimeter(shape_t const * const super);
  static void circle_draw(shape_t const * const super);
  static void circle_distory(shape_t * const super);
  
  /* 对父类虚接口的实现 */
  static const shape_vtbl_t g_circle_vtbl = {
      .area = &circle_area,
      .perimeter = &circle_perimeter,
      .draw = &circle_draw,
      .distory = &circle_distory
  };
  
  static float circle_area(shape_t const * const super)
  {
      circle_t *self = (circle_t *)super;
      float radius = self->diameter / 2;
  
      return (DEF_PI * radius * radius);
  }
  
  static float circle_perimeter(shape_t const * const super)
  {
      circle_t *self = (circle_t *)super;
  
      return (DEF_PI*self->diameter);
  }
  
  static void circle_draw(shape_t const * const super)
  {
      circle_t *self = (circle_t *)super;
  
      printf("I'm Circle, diameter:%.3f\n", self->diameter);
  }
  
  static void circle_distory(shape_t * const super)
  {
      circle_t *self = (circle_t *)super;
  
      printf("Distory %s\n", super->name);
      free(self);    /* 释放子类数据 */
  }
  ```

- 子类在创建时，除了初始化自有属性还需初始化父类的属性和虚表，以圆类为例；
  
  ```c
  shape_t* circle_create(float diameter)
  {
      shape_t *super = NULL;
      circle_t *self = NULL;
  
      self = (circle_t *)malloc(sizeof(circle_t));
      if (!self) {
          printf("It's not enough memory.\n");
          return NULL;
      }
  
      super = SHAPE(self);    // #define SHAPE(object)   ((shape_t *)(object))
      shape_init(super, &g_circle_vtbl, SHAPE_Circle, "circle");
  
      self->diameter = diameter;
      printf("Create %s OK.\n", super->name);
  
      return super;
  }
  ```

- 父类提供下层(子类)调用的API，子类通过调用父类提供的初始化方法来初始化父类；
  
  ```c
  void shape_init(shape_t * const self, shape_vtbl_t const *vtbl, int type, const char *name)
  {
      self->type = type;
      self->name = name;
      self->vtbl  = vtbl;
  }
  ```

- 父类提供上层调用的API，间接调用子类实现的虚表；
  
  ```c
  float shape_area(shape_t const * const self)
  {
      const shape_vtbl_t *vtbl = self->vtbl;
  
      return vtbl->area(self);
  }
  
  float shape_perimeter(shape_t const * const self)
  {
      const shape_vtbl_t *vtbl = self->vtbl;
  
      return vtbl->perimeter(self);
  }
  
  void shape_draw(shape_t const * const self)
  {
      const shape_vtbl_t *vtbl = self->vtbl;
  
      return vtbl->draw(self);
  }
  
  void shape_distory(shape_t * const self)
  {
      const shape_vtbl_t *vtbl = self->vtbl;
  
      vtbl->distory(self);
  }
  ```
