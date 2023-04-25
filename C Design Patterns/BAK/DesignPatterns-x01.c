#include <stdio.h>

typedef struct _animal {
    void (*speak)(void);
} animal_t;

typedef struct _cat {
    struct _animal animal;
} cat_t;

typedef struct _dog {
    struct _animal animal;
} dog_t;

void cat_speak(void)
{
    printf("miaomiao\n");
}

void dog_speak(void)
{
    printf("wangwang\n");
}

static cat_t cat = {
    .animal = { cat_speak }
};

static dog_t dog = {
    .animal = { dog_speak }
};

void process(void)
{
    animal_t *animal;

    animal = (animal_t *)&cat;
    animal->speak();
    
    animal = (animal_t *)&dog;
    animal->speak();
}

int main(void)
{
    process();
    
    return 0;
}
