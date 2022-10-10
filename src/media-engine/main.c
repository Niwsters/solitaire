#include "app.h"
#include "pipe.h"


#define PIPE_PATH  "./pipe-test"
int main()
{
    App *app = app_create();
    app_start(app);
    app_destroy(app);

    exit(0);
    return 0;
}
