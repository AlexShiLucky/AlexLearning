#include <stdio.h>

struct _music_file_ops;

#define FILL(x)     MT_##x, #x

typedef enum _music_type {
    MT_mp3  = 0,
    MT_wma  = 1,
    MT_flac = 2,
    MT_Unknown
} music_type_t;

typedef struct _music {
    char *name;
    enum _music_type type;
    char *ext;
} music_t;

typedef struct _music_file {
    struct _music *hfile;
    struct _music_file_ops *ops;
} music_file_t;

typedef struct _music_file_ops
{
    void (*read_file)(music_file_t *pMusicFile);
    void (*play)(music_file_t *pMusicFile);
    void (*stop)(music_file_t *pMusicFile);
    void (*back)(music_file_t *pMusicFile);
    void (*front)(music_file_t *pMusicFile);
    void (*down)(music_file_t *pMusicFile);
    void (*up)(music_file_t *pMusicFile);
} music_file_ops_t;

void read_file(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("read %s.%s\n", hfile->name, hfile->ext);
}

void play(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("play %s.%s\n", hfile->name, hfile->ext);
}

void stop(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("stop %s.%s\n", hfile->name, hfile->ext);
}

void back(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("back %s.%s\n", hfile->name, hfile->ext);
}

void front(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("front %s.%s\n", hfile->name, hfile->ext);
}

void down(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("down %s.%s\n", hfile->name, hfile->ext);
}

void up(music_file_t *pMusicFile)
{
    music_t *hfile = pMusicFile->hfile;

    printf("up %s.%s\n", hfile->name, hfile->ext);
}

static music_file_ops_t music_file_ops = {
    .read_file = read_file,
    .play = play,
    .stop = stop,
    .back = back,
    .front = front,
    .down = down,
    .up = up
};

static music_file_t music_A = {
    .hfile = &(music_t){ "A", FILL(mp3) },
    .ops = &music_file_ops
};

static music_file_t music_B = {
    .hfile = &(music_t){ "B", FILL(wma) },
    .ops = &music_file_ops
};

static music_file_t music_C = {
    .hfile = &(music_t){ "C", FILL(flac) },
    .ops = &music_file_ops
};

#define MUSIC_READ(x)     (x.ops->read_file(&x))
#define MUSIC_PLAY(x)     (x.ops->play(&x))
#define MUSIC_STOP(x)     (x.ops->stop(&x))
#define MUSIC_BACK(x)     (x.ops->back(&x))
#define MUSIC_FRONT(x)    (x.ops->front(&x))
#define MUSIC_DOWN(x)     (x.ops->down(&x))
#define MUSIC_UP(x)       (x.ops->up(&x))

int main(void)
{
    MUSIC_READ(music_A);
    MUSIC_READ(music_B);
    MUSIC_READ(music_C);

    MUSIC_PLAY(music_A);
    MUSIC_PLAY(music_B);
    MUSIC_PLAY(music_C);

    MUSIC_STOP(music_A);
    MUSIC_STOP(music_B);
    MUSIC_STOP(music_C);

    return 0;
}
