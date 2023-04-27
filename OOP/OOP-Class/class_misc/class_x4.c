#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 父类
struct _shape;
typedef struct _shape_ops
{
    /* 计算几何体的面积 */
    float (*area)(struct _shape *);
    /* 计算几何体的周长 */
    float (*perimeter)(struct _shape *);
    /* 销毁形状 */
    void (*distroy)(struct _shape *);
} shape_ops_t;

typedef struct _shape
{
    int   type;
    char *name;
    const struct _shape_ops *ops;       /* 虚接口,所有子类必须实现 */
} shape_t;

float shape_area(shape_t *s)            /* 求形状面积 */
{
    const shape_ops_t *ops = s->ops;
    return ops->area(s);
}

float shape_perimeter(shape_t *s)       /* 求周长 */
{
    const shape_ops_t *ops = s->ops;
    return ops->perimeter(s);
}

void shape_distroy(shape_t *s)
{
    const shape_ops_t *ops = s->ops;
    return ops->distroy(s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 子类:三角形 */
typedef struct _triangle
{
    struct _shape base;
    float side_a;
    float side_b;
    float side_c;
} triangle_t;

static float triangle_area(shape_t *s)         /* 三角形面积,用海伦公式 */
{
    triangle_t *t = (triangle_t *)s;
    float a = t->side_a;
    float b = t->side_b;
    float c = t->side_c;
    float p = (a + b + c) / 2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

static float triangle_perimeter(shape_t *s)    /* 三角形周长 */
{
    triangle_t *t = (triangle_t *)s;
    float a = t->side_a;
    float b = t->side_b;
    float c = t->side_c;
    return (a+b+c);
}

static void triangle_distroy(shape_t *s)
{
    printf("distroy %s\n", s->name);
    triangle_t *t = (triangle_t *)s;
    free(t);
}

static const shape_ops_t triangle_ops =       /* 对父类虚接口的实现 */
{
    triangle_area,
    triangle_perimeter,
    triangle_distroy
};

triangle_t* triangle_create(float a, float b, float c)      /* 创建三角形 */
{
    triangle_t *ret = (triangle_t *)malloc(sizeof (*ret));
    ret->base.name = "triangle";
    ret->base.ops  = &triangle_ops;
    ret->side_a = a;
    ret->side_b = b;
    ret->side_c = c;
    printf("create %s\n", ret->base.name);
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 子类:矩形 */
typedef struct _rectangle
{
    struct _shape base;
    float width;
    float height;
} rectangle_t;

static float rectangle_area(shape_t *s)        /* 矩形面积 */
{
    rectangle_t *r = (rectangle_t *)s;
    return (r->width * r->height);
}

static float rectangle_perimeter(shape_t *s)   /* 矩形周长 */
{
    rectangle_t *r = (rectangle_t *)s;
    return (r->width + r->height)*2;
}

static void rectangle_distroy(shape_t *s)
{
    printf("distroy %s\n", s->name);
    rectangle_t *r = (rectangle_t *)s;
    free(r);
}

static const shape_ops_t rectangle_ops =      /* 对父类虚接口的实现 */
{
    rectangle_area,
    rectangle_perimeter,
    rectangle_distroy
};

rectangle_t* rectangle_create(float width, float height)  /* 创建矩形 */
{
    rectangle_t *ret = (rectangle_t *)malloc(sizeof(*ret));
    ret->base.name = "rectangle";
    ret->base.ops  = &rectangle_ops;
    ret->height = height;
    ret->width  = width;
    printf("create %s\n", ret->base.name);
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 子类:圆 */
#define DEF_PI 3.1415926f
typedef struct _circle
{
    struct _shape base;
    float diameter;
} circle_t;

static float circle_area(shape_t *s)           /* 圆面积 */
{
    circle_t *c = (circle_t *)s;
    float radius = c->diameter / 2;
    return (DEF_PI * radius * radius);
}

static float circle_perimeter(shape_t *s)      /* 圆周长 */
{
    circle_t *c = (circle_t *)s;
    return (DEF_PI*c->diameter);
}

static void circle_distroy(shape_t *s)
{
    printf("distroy %s\n", s->name);
    circle_t *c = (circle_t *)s;
    free(c);
}

static const shape_ops_t circle_ops =         /* 对父类虚接口的实现 */
{
    circle_area,
    circle_perimeter,
    circle_distroy
};

circle_t* circle_create(float diameter) /* 创建圆 */
{
    circle_t *ret = (circle_t *)malloc(sizeof(*ret));
    ret->base.name = "circle";
    ret->base.ops  = &circle_ops;
    ret->diameter  = diameter;
    printf("create %s\n", ret->base.name);
    return ret;
}

int main(void)
{
    shape_t *s[6];
    s[0] = (shape_t *)triangle_create(5.0f, 5.0f, 4.0f);
    s[1] = (shape_t *)triangle_create(3.0f, 4.0f, 5.0f);
    s[2] = (shape_t *)rectangle_create(10.0f, 12.0f);
    s[3] = (shape_t *)rectangle_create(5.0f, 8.0f);
    s[4] = (shape_t *)circle_create(10.0f);
    s[5] = (shape_t *)circle_create(2.0f);

    int i = 0;
    for (i = 0; i < 6; i++)
    {
        float area = shape_area(s[i]);    
        float perimeter = shape_perimeter(s[i]);
        char* name = s[i]->name;
        printf("name:%s, area:%.2f, perimeter:%.2f\n", name, area, perimeter);

        shape_distroy(s[i]);
    }
    return 0;
}
