#include <stdio.h>
// 父类
struct Shape {
    void (*draw)(void);
    void (*erase)(void);
    void (*move)(void);
    int  (*getColor)(void);
    void (*setColor)(int);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子类
struct Circle {
    struct Shape shape;
    const char *name;
};

static void circle_draw(void)
{
    printf("circle draw\n");
}

static void circle_erase(void)
{
    printf("circle erase\n");
}

static void circle_move(void)
{
    printf("circle move\n");
}

static struct Circle   c = {
    .shape = {
        .draw  = circle_draw,
        .erase = circle_erase,
        .move  = circle_move
    },
    .name = "Circle"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子类
struct Square {
    struct Shape shape;
    const char *name;
};

static void square_draw(void)
{
    printf("square draw\n");
}

static void square_erase(void)
{
    printf("square erase\n");
}

static void square_move(void)
{
    printf("square move\n");
}

static struct Square   s = {
    .shape = {
        .draw  = square_draw,
        .erase = square_erase,
        .move  = square_move
    },
    .name = "Square"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// 子类
struct Triangle {
    struct Shape shape;
    const char *name;
};

static void triangle_draw(void)
{
    printf("triangle draw\n");
}

static void triangle_erase(void)
{
    printf("triangle erase\n");
}

static void triangle_move(void)
{
    printf("triangle move\n");
}

static struct Triangle t = {
    .shape = {
        .draw  = triangle_draw,
        .erase = triangle_erase,
        .move  = triangle_move
    },
    .name = "Triangle"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void doStuff(struct Shape *s)
{
    s->erase();
    s->draw();
    s->move();
}

int main(void)
{
    doStuff((struct Shape *)&c);
    doStuff((struct Shape *)&s);
    doStuff((struct Shape *)&t);
    return 0;
}

